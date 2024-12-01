#include "HCSR04.h"

extern unsigned char msHcCount;//ms计数
extern float distance;

///******************************************************************
// *  1ms
// * 函 数 名 称：bsp_ultrasonic
// * 函 数 说 明：超声波初始化
// * 函 数 形 参：无
// * 函 数 返 回：无
// * 作       者：LC
// * 备       注：TRIG引脚负责发送超声波脉冲串
//******************************************************************/
//void Ultrasonic_Init(void)
//{
//    // 使能GPIOA和定时器3的时钟
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_TIM1_CLK_ENABLE();
//
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//    // 配置TRIG引脚为推挽输出
//    GPIO_InitStruct.Pin = GPIO_TRIG;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(PORT_SR04, &GPIO_InitStruct);
//    HAL_GPIO_WritePin(PORT_SR04, GPIO_TRIG, GPIO_PIN_RESET);
//
//    // 配置ECHO引脚为上拉输入
//    GPIO_InitStruct.Pin = GPIO_ECHO;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    HAL_GPIO_Init(PORT_SR04, &GPIO_InitStruct);
//
//    // 初始化定时器1
//    htim1.Instance = TIM1;
//    htim1.Init.Prescaler = 72 - 1; // 设置预分频器，72MHz主时钟 -> 1MHz
//    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
//    htim1.Init.Period = 1000 - 1;  // 设置周期为1000（1ms）
//    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    htim1.Init.RepetitionCounter = 0; // 高级定时器的重复计数器设置为0
//    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//    HAL_TIM_Base_Init(&htim1);
//
//    // 清除定时器计数和中断标志
//    __HAL_TIM_SET_COUNTER(&htim1, 0);
//    __HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
//
//    // 开启定时器中断
//    HAL_TIM_Base_Start_IT(&htim1);
//
//}


// 超声波初始化
void Ultrasonic_Init(void)
{
    // 使能GPIOB和定时器1的时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 配置TRIG引脚为推挽输出
    GPIO_InitStruct.Pin = GPIO_TRIG;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PORT_SR04, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PORT_SR04, GPIO_TRIG, GPIO_PIN_RESET);

    // 配置ECHO引脚为上拉输入
    GPIO_InitStruct.Pin = GPIO_ECHO;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(PORT_SR04, &GPIO_InitStruct);

    // 初始化定时器1
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 72 - 1; // 设置预分频器，72MHz主时钟 -> 10kHz
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 10000 - 1;      // 设置周期为200（20ms）
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0; // 高级定时器的重复计数器设置为0
    HAL_TIM_Base_Init(&htim1);

    // 清除定时器计数和中断标志
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    __HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);

    // 开启定时器中断
    HAL_TIM_Base_Start_IT(&htim1);
}


/******************************************************************
 * 函 数 名 称：Open_Timer
 * 函 数 说 明：打开定时器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：
******************************************************************/
void Open_Timer(void)
{
    __HAL_TIM_SET_COUNTER(&htim1, 0); // 清除定时器计数

    msHcCount = 0;

    HAL_TIM_Base_Start_IT(&htim1);   // 使能定时器
}

/******************************************************************
 *  1ms
 * 函 数 名 称：Get_TIMER_Count
 * 函 数 说 明：获取定时器定时时间
 * 函 数 形 参：无
 * 函 数 返 回：数据
 * 作       者：LC
 * 备       注：
******************************************************************/
uint32_t Get_TIMER_Count(void)
{
    uint32_t time = 0;
    time = msHcCount * 1000;                   // 得到us
    time += __HAL_TIM_GET_COUNTER(&htim1);     // 得到ms

    __HAL_TIM_SET_COUNTER(&htim1, 0);          // 清除定时器计数
    HAL_Delay(10);
    return time;
}

/******************************************************************
 * 函 数 名 称：Close_Timer
 * 函 数 说 明：关闭定时器
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：
******************************************************************/
void Close_Timer(void)
{
    HAL_TIM_Base_Stop_IT(&htim1);  // 关闭定时器
}

/******************************************************************
 * 函 数 名 称：TIMER_IRQHandler
 * 函 数 说 明：定时器中断服务函数
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：10ms进入一次
******************************************************************/
//void TIM1_UP_IRQHandler(void) // 定时器1的更新中断服务函数
//{
//
//    if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE) != RESET)  // 检查定时器中断发生
//    {
//        if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_UPDATE) != RESET)
//        {
//            msHcCount++;
//
//            __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);  // 清除中断标志
//        }
//    }
//}


/******************************************************************
 * 函 数 名 称：Hcsr04GetLength
 * 函 数 说 明：获取测量距离
 * 函 数 形 参：无
 * 函 数 返 回：测量距离
 * 作       者：LC
 * 备       注：无
******************************************************************/
float Hcsr04GetLength(void)
{
    /*测5次数据计算一次平均值*/
    float length = 0;
    float t = 0;
    float sum = 0;
    unsigned int  i = 0;
    while(i != 10)
    {

        SR04_TRIG(1);//trig拉高信号，发出高电平
        Delay_us(20);//持续时间超过10us
        SR04_TRIG(0);//trig拉低信号，发出低电平
        /*Echo发出信号 等待回响信号*/
        /*输入方波后，模块会自动发射8个40KHz的声波，与此同时回波引脚（echo）端的电平会由0变为1；
        （此时应该启动定时器计时）；当超声波返回被模块接收到时，回波引 脚端的电平会由1变为0；
        （此时应该停止定时器计数），定时器记下的这个时间即为
                                        超声波由发射到返回的总时长；*/

        while(SR04_ECHO() ==  GPIO_PIN_RESET);//echo等待回响

        Open_Timer();   //打开定时器

        i++;

        while(SR04_ECHO() == GPIO_PIN_SET);

        Close_Timer();   // 关闭定时器

        t = Get_TIMER_Count();   // 获取时间,分辨率为1us
        length = (float)t / 58.0f;   // cm
        sum += length;
    }
    length = sum/10;//五次平均值
    distance = length;
    return length;
}


