//
// Created by 刘嘉俊 on 24-9-19.
//

#ifndef C8T6_BALANCE_BUZZER_H
#define C8T6_BALANCE_BUZZER_H

#include "stm32f1xx_hal.h" // 根据您的具体芯片选择合适的HAL头文件

// 定义蜂鸣器控制引脚
#define BUZZER_PORT GPIOA
#define BUZZER_PIN GPIO_PIN_11


// 函数原型
void Buzzer_Init(void);  // 初始化蜂鸣器引脚
void Buzzer_On(void);    // 打开蜂鸣器
void Buzzer_Off(void);   // 关闭蜂鸣器

#endif //C8T6_BALANCE_BUZZER_H
