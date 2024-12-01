//
// Created by 刘嘉俊 on 24-8-4.
//

#include "pca9685.h"

/******************************************************************
 * 函 数 名 称：PCA9685_GPIO_Init
 * 函 数 说 明：PCA9685的引脚初始化
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void PCA9685_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(PORT_PCA9685, PCA_9685_SCL_Pin|PCA_9685_SDA_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : PB5 PB6 */
    GPIO_InitStruct.Pin = PCA_9685_SCL_Pin|PCA_9685_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PORT_PCA9685, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PORT_PCA9685, PCA_9685_SCL_Pin|PCA_9685_SDA_Pin, GPIO_PIN_SET);

}

/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始时序
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void I2C_Start(void)
{
    PCA_SDA_OUT();

    PCA_SDA(1);
    Delay_us(5);
    PCA_SCL(1);
    Delay_us(5);

    PCA_SDA(0);
    Delay_us(5);
    PCA_SCL(0);
    Delay_us(5);

}
/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void I2C_Stop(void)
{
    PCA_SDA_OUT();
    PCA_SCL(0);
    PCA_SDA(0);

    PCA_SCL(1);
    Delay_us(5);
    PCA_SDA(1);
    Delay_us(5);

}

/******************************************************************
 * 函 数 名 称：IIC_Send_Ack
 * 函 数 说 明：主机发送应答或者非应答信号
 * 函 数 形 参：0发送应答  1发送非应答
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void I2C_Send_Ack(unsigned char ack)
{
    PCA_SDA_OUT();
    PCA_SCL(0);
    PCA_SDA(0);
    Delay_us(5);
    if(!ack) PCA_SDA(0);
    else     PCA_SDA(1);
    PCA_SCL(1);
    Delay_us(5);
    PCA_SCL(0);
    PCA_SDA(1);
}


/******************************************************************
 * 函 数 名 称：I2C_WaitAck
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：0有应答  1超时无应答
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char I2C_WaitAck(void)
{

    char ack = 0;
    unsigned char ack_flag = 10;
    PCA_SCL(0);
    PCA_SDA(1);
    PCA_SDA_IN();
    Delay_us(5);
    PCA_SCL(1);
    Delay_us(5);

    while( (PCA_SDA_GET()==1) && ( ack_flag ) )
    {
        ack_flag--;
        Delay_us(5);
    }

    if( ack_flag <= 0 )
    {
        I2C_Stop();
        return 1;
    }
    else
    {
        PCA_SCL(0);
        PCA_SDA_OUT();
    }
    return ack;
}

/******************************************************************
 * 函 数 名 称：Send_Byte
 * 函 数 说 明：写入一个字节
 * 函 数 形 参：dat要写人的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void PCA_Send_Byte(uint8_t dat)
{
    int i = 0;
    PCA_SDA_OUT();
    PCA_SCL(0);//拉低时钟开始数据传输

    for( i = 0; i < 8; i++ )
    {
        PCA_SDA( (dat & 0x80) >> 7 );
        Delay_us(1);
        PCA_SCL(1);
        Delay_us(5);
        PCA_SCL(0);
        Delay_us(5);
        dat<<=1;
    }
}

/******************************************************************
 * 函 数 名 称：Read_Byte
 * 函 数 说 明：IIC读时序
 * 函 数 形 参：无
 * 函 数 返 回：读到的数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char PCA_Read_Byte(void)
{
    unsigned char i,receive=0;
    PCA_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        PCA_SCL(0);
        Delay_us(5);
        PCA_SCL(1);
        Delay_us(5);
        receive<<=1;
        if( PCA_SDA_GET() )
        {
            receive|=1;
        }
        Delay_us(5);
    }
    PCA_SCL(0);
    return receive;
}

/******************************************************************
 * 函 数 名 称：PCA9685_Write
 * 函 数 说 明：向PCA9685写命令或数据
 * 函 数 形 参：addr写入的寄存器地址    data写入的命令或数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void PCA9685_Write(uint8_t addr,uint8_t data)
{
    I2C_Start();

    PCA_Send_Byte(PCA_Addr);
    I2C_WaitAck();

    PCA_Send_Byte(addr);
    I2C_WaitAck();

    PCA_Send_Byte(data);
    I2C_WaitAck();

    I2C_Stop();
}

/******************************************************************
 * 函 数 名 称：PCA9685_Read
 * 函 数 说 明：读取PCA9685数据
 * 函 数 形 参：addr读取的寄存器地址
 * 函 数 返 回：读取的数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
uint8_t PCA9685_Read(uint8_t addr)
{
    uint8_t data;

    I2C_Start();

    PCA_Send_Byte(PCA_Addr);
    I2C_WaitAck();

    PCA_Send_Byte(addr);
    I2C_WaitAck();

    I2C_Stop();

    Delay_us(10);


    I2C_Start();

    PCA_Send_Byte(PCA_Addr|0x01);
    I2C_WaitAck();

    data = PCA_Read_Byte();
    I2C_Send_Ack(1);
    I2C_Stop();

    return data;
}
/******************************************************************
 * 函 数 名 称：PCA9685_setPWM
 * 函 数 说 明：设置第num个PWM引脚，on默认为0，控制舵机旋转off角度
 * 函 数 形 参：num：设置第几个引脚输出，范围0~15
 *              on ：默认为0
 *              off：舵机旋转角度，范围：0~180
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off)
{
    I2C_Start();

    PCA_Send_Byte(PCA_Addr);
    I2C_WaitAck();

    PCA_Send_Byte(LED0_ON_L+4*num);
    I2C_WaitAck();

    PCA_Send_Byte(on&0xFF);
    I2C_WaitAck();

    PCA_Send_Byte(on>>8);
    I2C_WaitAck();

    PCA_Send_Byte(off&0xFF);
    I2C_WaitAck();

    PCA_Send_Byte(off>>8);
    I2C_WaitAck();

    I2C_Stop();

}



/******************************************************************
 * 函 数 名 称：PCA9685_setFreq
 * 函 数 说 明：设置PCA9685的输出频率
 * 函 数 形 参：freq
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：
floor语法：
FLOOR(number, significance)
    Number必需。要舍入的数值。
    Significance必需。要舍入到的倍数。
说明
    将参数 number 向下舍入（沿绝对值减小的方向）为最接近的 significance 的倍数。
    如果任一参数为非数值型，则 FLOOR 将返回错误值 #VALUE!。
    如果 number 的符号为正，且 significance 的符号为负，则 FLOOR 将返回错误值 #NUM!
示例
    公式                                说明                                                                结果
    FLOOR(3.7,2)                将 3.7 沿绝对值减小的方向向下舍入，使其等于最接近的 2 的倍数                2
    FLOOR(-2.5, -2)                将 -2.5 沿绝对值减小的方向向下舍入，使其等于最接近的 -2 的倍数                -2
******************************************************************/
void PCA9685_setFreq(float freq)
{
    uint8_t prescale,oldmode,newmode;

    double prescaleval;

//        freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).

//        PCA9685的内部时钟频率是25Mhz
//        公式: presale_Volue = round( 25000000/(4096 * update_rate) ) - 1
//        round = floor();  floor是数学函数，需要导入 math.h 文件
//        update_rate = freq;
    prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;
    prescale = floor(prescaleval+0.5f);

    //返回MODE1地址上的内容（保护其他内容）
    oldmode = PCA9685_Read(PCA_Model);

    //在MODE1中设置SLEEP位
    newmode = (oldmode&0x7F)|0x10;
    //将更改的MODE1的值写入MODE1地址,使芯片睡眠
    PCA9685_Write(PCA_Model,newmode);
    //写入我们计算的设置频率的值
    //PCA_Pre = presale 地址是0xFE，可以数据手册里查找到
    PCA9685_Write(PCA_Pre,prescale);
    //重新复位
    PCA9685_Write(PCA_Model,oldmode);
    //等待复位完成
    HAL_Delay(5);
    //设置MODE1寄存器开启自动递增
    PCA9685_Write(PCA_Model,oldmode|0xa1);
}

//
/******************************************************************
 * 函 数 名 称：setAngle
 * 函 数 说 明：设置角度
 * 函 数 形 参：num要设置的PWM引脚     angle设置的角度
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void setAngle(uint8_t num,uint8_t angle)
{
    uint32_t off = 0;

    off = (uint32_t)(158+angle*2.2);

    PCA9685_setPWM(num,0,off);
}

/******************************************************************
 * 函 数 名 称：PCA9685_Init
 * 函 数 说 明：PCA9685初始化，所有PWM输出频率配置与所有PWM引脚输出的舵机角度
 * 函 数 形 参：hz设置的初始频率  angle设置的初始角度
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void PCA9685_Init(float hz,uint8_t angle)
{
    uint32_t off = 0;

    PCA9685_GPIO_Init();

    //在MODE1地址上写0x00
    PCA9685_Write(PCA_Model,0x00);        //这一步很关键，如果没有这一步PCA9685就不会正常工作。

//        pwm.setPWMFreq(SERVO_FREQ)函数主要是设置PCA9685的输出频率，
//        PCA9685的16路PWM输出频率是一致的，所以是不能实现不同引脚不同频率的。
//        下面是setPWMFreq函数的内容，主要是根据频率计算PRE_SCALE的值。
    PCA9685_setFreq(hz);
    //计算角度
    off = (uint32_t)(145+angle*2.4);

    //控制16个舵机输出off角度
    PCA9685_setPWM(0,0,off);
    PCA9685_setPWM(1,0,off);
    PCA9685_setPWM(2,0,off);
    PCA9685_setPWM(3,0,off);
    PCA9685_setPWM(4,0,off);
    PCA9685_setPWM(5,0,off);
    PCA9685_setPWM(6,0,off);
    PCA9685_setPWM(7,0,off);
    PCA9685_setPWM(8,0,off);
    PCA9685_setPWM(9,0,off);
    PCA9685_setPWM(10,0,off);
    PCA9685_setPWM(11,0,off);
    PCA9685_setPWM(12,0,off);
    PCA9685_setPWM(13,0,off);
    PCA9685_setPWM(14,0,off);
    PCA9685_setPWM(15,0,off);

    HAL_Delay(100);

}
