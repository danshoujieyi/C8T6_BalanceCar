//
// Created by ���ο� on 24-9-15.
//

#ifndef C8T6_BALANCE_SERVO_H
#define C8T6_BALANCE_SERVO_H

#include "tim.h"


// ���ö���ĽǶȣ�0��180��
void SetServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle);

// ��ʼ�����λ��
void InitServo();


// ����ѭ���п��Զ�̬�������λ��
void AdjustServo();


#endif //C8T6_BALANCE_SERVO_H
