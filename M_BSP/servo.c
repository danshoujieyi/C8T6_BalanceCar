//
// Created by 刘嘉俊 on 24-9-15.
//

#include "servo.h"
#include "tim.h"

// SG90 舵机控制的PWM参数
#define PWM_FREQUENCY 50         // PWM频率为50Hz
#define SERVO_MIN_PULSE_WIDTH  500 // 最小脉宽（0.5ms）
#define SERVO_MAX_PULSE_WIDTH  2500 // 最大脉宽（2.5ms）

// 设置舵机的角度（0到180）
void SetServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle)
{
    // 计算脉宽的占比
    uint32_t pulseWidth = (SERVO_MIN_PULSE_WIDTH + (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH) * angle / 180);

    // 设置PWM信号的脉宽
    __HAL_TIM_SET_COMPARE(htim, channel, pulseWidth);
}

// 初始化舵机位置
void InitServo()
{


    // 设置舵机1和舵机2的初始位置（可调）
    SetServoAngle(&htim1, TIM_CHANNEL_1, 90); // 设置舵机1在90度
    SetServoAngle(&htim1, TIM_CHANNEL_4, 90); // 设置舵机2在90度
}

// 在主循环中可以动态调整舵机位置
void AdjustServo()
{
    // 可以在这里设置需要的角度，例如：
    SetServoAngle(&htim1, TIM_CHANNEL_1, 90); // 将舵机1设置为45度
    HAL_Delay(1000); // 等待1秒

    SetServoAngle(&htim1, TIM_CHANNEL_4, 90); // 将舵机1设置为135度
    HAL_Delay(1000); // 等待1秒
}


