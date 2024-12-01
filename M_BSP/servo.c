//
// Created by ���ο� on 24-9-15.
//

#include "servo.h"
#include "tim.h"

// SG90 ������Ƶ�PWM����
#define PWM_FREQUENCY 50         // PWMƵ��Ϊ50Hz
#define SERVO_MIN_PULSE_WIDTH  500 // ��С����0.5ms��
#define SERVO_MAX_PULSE_WIDTH  2500 // �������2.5ms��

// ���ö���ĽǶȣ�0��180��
void SetServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle)
{
    // ���������ռ��
    uint32_t pulseWidth = (SERVO_MIN_PULSE_WIDTH + (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) * angle / 180);

    // ����PWM�źŵ�����
    __HAL_TIM_SET_COMPARE(htim, channel, pulseWidth);
}

// ��ʼ�����λ��
void InitServo()
{


    // ���ö��1�Ͷ��2�ĳ�ʼλ�ã��ɵ���
    SetServoAngle(&htim1, TIM_CHANNEL_1, 90); // ���ö��1��90��
    SetServoAngle(&htim1, TIM_CHANNEL_4, 90); // ���ö��2��90��
}

// ����ѭ���п��Զ�̬�������λ��
void AdjustServo()
{
    // ����������������Ҫ�ĽǶȣ����磺
    SetServoAngle(&htim1, TIM_CHANNEL_1, 90); // �����1����Ϊ45��
    HAL_Delay(1000); // �ȴ�1��

    SetServoAngle(&htim1, TIM_CHANNEL_4, 90); // �����1����Ϊ135��
    HAL_Delay(1000); // �ȴ�1��
}


