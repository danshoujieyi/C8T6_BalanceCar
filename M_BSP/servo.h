//
// Created by 刘嘉俊 on 24-9-15.
//

#ifndef C8T6_BALANCE_SERVO_H
#define C8T6_BALANCE_SERVO_H

#include "tim.h"


// 设置舵机的角度（0到180）
void SetServoAngle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle);

// 初始化舵机位置
void InitServo();


// 在主循环中可以动态调整舵机位置
void AdjustServo();


#endif //C8T6_BALANCE_SERVO_H
