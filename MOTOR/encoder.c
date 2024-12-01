//
// Created by 刘嘉俊 on 24-7-25.
//

#include "encoder.h"

int PWM_MAX=7200,PWM_MIN=-7200;	// PWM限幅变量

/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
uint32_t Read_Encoder(uint8_t TIMX)	//编码器控制周期10ms
{

    uint32_t Encoder_TIM;
    switch(TIMX)
    {
        case 4: //单周期位移作为速度值
            Encoder_TIM = (short)__HAL_TIM_GET_COUNTER(&htim4);//采集编码器的值并保存
            __HAL_TIM_SET_COUNTER(&htim4,0);							//将定时器的计数值清零
            break;

        case 3: Encoder_TIM = (short)__HAL_TIM_GET_COUNTER(&htim3);
            __HAL_TIM_SET_COUNTER(&htim3,0);
            break;

        default: Encoder_TIM = 0;

    }
    return Encoder_TIM;


}

/*绝对值函数*/
int abs(int p)
{
    int q;
    q=p>0?p:(-p);
    return q;
}
