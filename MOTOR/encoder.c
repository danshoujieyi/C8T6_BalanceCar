//
// Created by ���ο� on 24-7-25.
//

#include "encoder.h"

int PWM_MAX=7200,PWM_MIN=-7200;	// PWM�޷�����

/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
**************************************************************************/
uint32_t Read_Encoder(uint8_t TIMX)	//��������������10ms
{

    uint32_t Encoder_TIM;
    switch(TIMX)
    {
        case 4: //������λ����Ϊ�ٶ�ֵ
            Encoder_TIM = (short)__HAL_TIM_GET_COUNTER(&htim4);//�ɼ���������ֵ������
            __HAL_TIM_SET_COUNTER(&htim4,0);							//����ʱ���ļ���ֵ����
            break;

        case 3: Encoder_TIM = (short)__HAL_TIM_GET_COUNTER(&htim3);
            __HAL_TIM_SET_COUNTER(&htim3,0);
            break;

        default: Encoder_TIM = 0;

    }
    return Encoder_TIM;


}

/*����ֵ����*/
int abs(int p)
{
    int q;
    q=p>0?p:(-p);
    return q;
}
