//
// Created by 刘嘉俊 on 24-7-25.
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


extern int Vertical_out, Velocity_out, Turn_out; // 直立环&速度环&转向环的输出变量
extern int Encoder_Left, Encoder_Right, Balance_PWM;
extern int Moto1, Moto2;//左电机， 右电机
extern int PWM_out, Turn_Pwm; //闭环输出
extern int dead_zone;// 3000 ;		//L298N控制死区 0 - 3000
extern uint8_t AIN1, AIN2;//控制电机正反转，右电机
extern uint8_t BIN1, BIN2;//左电机
extern uint8_t Moto_Flag;//电机控制标志

//PID
extern float Vertical_Kp, Vertical_Kd;	//直立环Kp,Kd
extern float kp, ki;

extern float temp;
extern float pitch, roll, yaw;   //欧拉角
extern short gyro[3];//gyro_x, gyro_y, gyro_z;        // 角速度
extern short acc[3];//acc_x, acc_y, acc_z;           // 加速度
extern float Med_Angle;//机械中值，能使得小车真正平衡住的角度

extern uint8_t Start_Flag;//系统初始化完成标志

#endif //C8T6_BALANCE_ROBOT_CONFIG_H
