//
// Created by 刘嘉俊 on 24-7-25.
//

#include "motor.h"

/***************************************************************************
函数功能：控制电机
******************************************************************************/
void Contrl(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, BIN2);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, BIN1);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, AIN1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, AIN2);
}




/**************************************************************************
函数功能：电机异常关闭函数
入口参数：角度
返回  值：1：关闭，0：不关闭
**************************************************************************/
u8 Stop(signed int angle)
{
    u8 temp= 0;
    if(angle<-40||angle>40)
    {	                                //===倾角大于40度关闭电机
        temp=1;                   		   //===Flag_Stop置1关闭电机
        Moto1 = 0;
        Moto2 = 0;
    }

    return temp;
}


/**************************************************************************
函数功能：电机转动控制函数
入口参数：闭环控制最终输出值
**************************************************************************/
void Set_Pwm(int Moto1,int Moto2)
{
    Moto_Flag=Stop(roll);	//获取是否倒下的标志
    if(Start_Flag == 1)		//一级判断系统是否正常初始化
    {
        if(Moto_Flag==0)	//二级判断
        {
            if(Moto1>0)  BIN1 = 1, BIN2 = 0;
            else			 BIN1 = 0, BIN2 = 1;
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,abs(Moto1)+dead_zone);

            if(Moto2>0)  AIN1 = 1, AIN2 = 0;
            else		    AIN1 = 0 , AIN2 = 1;
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,abs(Moto2)+dead_zone); //0-7200
        }

        else//倒下就关闭电机
        {
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	//4500-6000
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	//4500-6000
        }
        Contrl();
    }
}

/**************************************************************************
函数功能：限制电机速度
入口参数：闭环控制最终输出值
**************************************************************************/
void Limit(int *motoA,int *motoB)
{
    if(*motoA>7000)*motoA=7000;//最大7200
    if(*motoA<-7000)*motoA=-7000;

    if(*motoB>7000)*motoB=7000;
    if(*motoB<-7000)*motoB=-7000;
}