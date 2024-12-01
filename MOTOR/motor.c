//
// Created by ���ο� on 24-7-25.
//

#include "motor.h"

/***************************************************************************
�������ܣ����Ƶ��
******************************************************************************/
void Contrl(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, BIN2);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, BIN1);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, AIN1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, AIN2);
}




/**************************************************************************
�������ܣ�����쳣�رպ���
��ڲ������Ƕ�
����  ֵ��1���رգ�0�����ر�
**************************************************************************/
u8 Stop(signed int angle)
{
    u8 temp= 0;
    if(angle<-40||angle>40)
    {	                                //===��Ǵ���40�ȹرյ��
        temp=1;                   		   //===Flag_Stop��1�رյ��
        Moto1 = 0;
        Moto2 = 0;
    }

    return temp;
}


/**************************************************************************
�������ܣ����ת�����ƺ���
��ڲ������ջ������������ֵ
**************************************************************************/
void Set_Pwm(int Moto1,int Moto2)
{
    Moto_Flag=Stop(roll);	//��ȡ�Ƿ��µı�־
    if(Start_Flag == 1)		//һ���ж�ϵͳ�Ƿ�������ʼ��
    {
        if(Moto_Flag==0)	//�����ж�
        {
            if(Moto1>0)  BIN1 = 1, BIN2 = 0;
            else			 BIN1 = 0, BIN2 = 1;
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,abs(Moto1)+dead_zone);

            if(Moto2>0)  AIN1 = 1, AIN2 = 0;
            else		    AIN1 = 0 , AIN2 = 1;
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,abs(Moto2)+dead_zone); //0-7200
        }

        else//���¾͹رյ��
        {
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_4,0);	//4500-6000
            __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);	//4500-6000
        }
        Contrl();
    }
}

/**************************************************************************
�������ܣ����Ƶ���ٶ�
��ڲ������ջ������������ֵ
**************************************************************************/
void Limit(int *motoA,int *motoB)
{
    if(*motoA>7000)*motoA=7000;//���7200
    if(*motoA<-7000)*motoA=-7000;

    if(*motoB>7000)*motoB=7000;
    if(*motoB<-7000)*motoB=-7000;
}