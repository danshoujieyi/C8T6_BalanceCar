//
// Created by ���ο� on 24-7-25.
//

#ifndef C8T6_BALANCE_ROBOT_CONFIG_H
#define C8T6_BALANCE_ROBOT_CONFIG_H

#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "math.h"
#include "tim.h"

//#include "mpu6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"

#include "HCSR04.h"
#include "pca9685.h"
#include "servo.h"
//#include "dht11.h"
//#include "buzzer.h"
#include "openmv_1.h"
#include "sg90_arm.h"

//#include "encoder.h"
//#include "pid.h"
//#include "motor.h"



void Delay_us(__IO uint32_t delay);


extern int Vertical_out, Velocity_out, Turn_out; // ֱ����&�ٶȻ�&ת�򻷵��������
extern int Encoder_Left, Encoder_Right, Balance_PWM;
extern int Moto1, Moto2;//������ �ҵ��
extern int PWM_out, Turn_Pwm; //�ջ����
extern int dead_zone;// 3000 ;		//L298N�������� 0 - 3000
extern uint8_t AIN1, AIN2;//���Ƶ������ת���ҵ��
extern uint8_t BIN1, BIN2;//����
extern uint8_t Moto_Flag;//������Ʊ�־

//PID
extern float Vertical_Kp, Vertical_Kd;	//ֱ����Kp,Kd
extern float kp, ki;

extern float temp;
extern float pitch, roll, yaw;   //ŷ����
extern short gyro[3];//gyro_x, gyro_y, gyro_z;        // ���ٶ�
extern short acc[3];//acc_x, acc_y, acc_z;           // ���ٶ�
extern float Med_Angle;//��е��ֵ����ʹ��С������ƽ��ס�ĽǶ�

extern uint8_t Start_Flag;//ϵͳ��ʼ����ɱ�־

#endif //C8T6_BALANCE_ROBOT_CONFIG_H
