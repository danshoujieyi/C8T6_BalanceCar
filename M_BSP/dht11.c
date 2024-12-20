//
// Created by 刘嘉俊 on 24-9-16.
//


#include "dht11.h"

extern float temperature;
extern float humidity;

// 初始化 DHT11 GPIO
void DHT11_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 开启GPIOB时钟
    RCU_DHT11; // 使能 GPIOB 时钟

    GPIO_InitStructure.Pin = GPIO_DHT11; // 设置引脚
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 设置为推挽输出
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 无上拉下拉
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 设置速度为高速

    // 初始化 GPIO
    HAL_GPIO_Init(PORT_DHT11, &GPIO_InitStructure);

    // 设置 DHT11 数据引脚为高电平
    DATA_GPIO_OUT(1);
}

/******************************************************************
 * 函 数 名 称：DHT11_GPIO_Mode_OUT
 * 函 数 说 明：配置DHT11的数据引脚为输出模式
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void DHT11_GPIO_Mode_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 设置GPIO引脚为输出模式
    GPIO_InitStructure.Pin = GPIO_DHT11; // 引脚设置
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出模式
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 无上拉或下拉
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 设置为高速

    // 调用HAL库函数初始化GPIO
    HAL_GPIO_Init(PORT_DHT11, &GPIO_InitStructure);
}


/******************************************************************
 * 函 数 名 称：DHT11_GPIO_Mode_IN
 * 函 数 说 明：配置DHT11的数据引脚为输入模式
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void DHT11_GPIO_Mode_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 设置GPIO引脚为上拉输入模式
    GPIO_InitStructure.Pin = GPIO_DHT11; // 引脚设置
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // 输入模式
    GPIO_InitStructure.Pull = GPIO_PULLUP; // 上拉电阻
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 设置为高速

    // 调用HAL库函数初始化GPIO
    HAL_GPIO_Init(PORT_DHT11, &GPIO_InitStructure);
}

/******************************************************************
 * 函 数 名 称：DHT11_Read_Data
 * 函 数 说 明：根据时序读取温湿度数据
 * 函 数 形 参：无
 * 函 数 返 回：0=数据校验失败  其他=温湿度未处理的数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned int DHT11_Read_Data(void)
{
    int i;
    long long val=0;
    int timeout=0;
    float small_point=0;
    unsigned char verify_num = 0;//验证值

    DATA_GPIO_OUT(0);//数据线输出低电平
    HAL_Delay(19);  // 起始信号保持时间19ms
    DATA_GPIO_OUT(1);//主机释放总线
    Delay_us( 20 );//拉高等待

    DHT11_GPIO_Mode_IN();//数据线转为输入模式
    //如果前面没有错误，则模块会发出低电平的应答信号，所以直接等待DHT11拉高，80us
    timeout = 5000;
    while( (! DATA_GPIO_IN ) && ( timeout >0 ) )timeout--;         //等待高电平的到来

    //模块当前处于拉高准备输出数据，所以直接等待DHT11拉低，80us
    timeout = 5000;//设置超时时间
    //DATA_GPIO_IN=0时,while条件不成立退出while 说明接收到响应信号
    //当timeout<=0时，while条件不成立退出while  说明超时
    while( DATA_GPIO_IN && ( timeout >0 ) )timeout-- ;         //等待低电平的到来

#define CHECK_TIME 28 //实测发现超过0值的高电平时间
    for(i=0;i<40;i++)//循环接收40位数据
    {
        timeout = 5000;
        while( ( !DATA_GPIO_IN ) && (timeout > 0) ) timeout--;         //等待低电平过去

        Delay_us(CHECK_TIME);//超过0值的高电平时间
        if ( DATA_GPIO_IN )//如果还是高电平，说明是1值
        {
            val=(val<<1)+1;
        }
        else //如果是低电平，说明是0值
        {
            val<<=1;
        }

        timeout = 5000;
        while( DATA_GPIO_IN && (timeout > 0) ) timeout-- ;         //如果还是高电平
    }

    DHT11_GPIO_Mode_OUT();//转为输出模式
    DATA_GPIO_OUT(1);//主机释放总线

    //           湿高8     + 湿低8      + 温高8     + 温低8
    verify_num = (val>>32) + (val>>24) + (val>>16) + (val>>8);
    //计算的校验和 与 接收的校验和 的差为0说明一致，不为0说明不一致
    verify_num = verify_num - (val&0xff);
    //进行校验
    if( verify_num  )
    {
//      校验错误
        return 0;
    }
    else //校验成功
    {
        //数据处理
        humidity = (val>>32)&0xff;//湿度前8位（小数点前数据）
        small_point = (val>>24)&0x00ff;//湿度后8位（小数点后数据）
        small_point = small_point * 0.1;//换算为小数点
        humidity = humidity + small_point;//小数前+小数后
//        printf("湿度：%.2f\r\n",humidity);

        temperature = (val>>16)&0x0000ff;//温度前8位（小数点前数据）
        small_point = (val>>8)&0x000000ff;//温度后8位（小数点后数据）
        small_point = small_point * 0.1;//换算为小数点
        temperature = temperature + small_point;//小数前+小数后
//        printf("温度：%.2f\r\n",temperature);

        return val>>8; //返回未处理的数据
    }
}

/******************************************************************
 * 函 数 名 称：Get_temperature
 * 函 数 说 明：获取温度数据
 * 函 数 形 参：无
 * 函 数 返 回：温度值
 * 作       者：LC
 * 备       注：使用前必须先调用 DHT11_Read_Data 读取有数据
******************************************************************/
float Get_temperature(void)
{
    return temperature;
}

/******************************************************************
 * 函 数 名 称：Get_humidity
 * 函 数 说 明：获取湿度数据
 * 函 数 形 参：无
 * 函 数 返 回：湿度值
 * 作       者：LC
 * 备       注：使用前必须先调用 DHT11_Read_Data 读取有数据
******************************************************************/
float Get_humidity(void)
{
    return humidity;
}