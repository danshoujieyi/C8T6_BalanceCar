//
// Created by ���ο� on 24-7-25.
//

#ifndef C8T6_BALANCE_PID_H
#define C8T6_BALANCE_PID_H
#include "robot_config.h"
/***************************************************************************
ֱ����PD��������Kp*Ek+Kd*Ek_D
��ڣ�Med:��е��ֵ(�����Ƕ�)��Angle:��ʵ�Ƕȣ�gyro_Y:��ʵ���ٶ�
���ڣ�PMW��ֵ
******************************************************************************/
int Vertical(float Angle,float Gyro_Y);
/*********************************************************************
�ٶȻ�PI��������Kp*Ek+Ki*Ek_S(Ek_S��ƫ��Ļ���)
��ڣ����ұ������⵽����ֵ
���ڣ�
**********************************************************************/
int Velocity(int Encoder_left,int Encoder_right);
/*********************************************************************
ת�򻷣�ϵ��*Z����ٶ�+ϵ��*ң������
��ڣ����ҵ�������������ֵ��Z����ٶ�
**********************************************************************/
int Turn(int Encoder_Left,int Encoder_Right,float gyro);

void calculate(void);

#endif //C8T6_BALANCE_PID_H