//
// Created by 刘嘉俊 on 24-9-19.
//

#include "buzzer.h"
// GPIO 初始化函数

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置PA11为推挽输出
    GPIO_InitStruct.Pin = BUZZER_PIN; // 使用PA11控制蜂鸣器
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出模式
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

// 打开蜂鸣器
void Buzzer_On(void)
{
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET); // 低电平驱动蜂鸣器
}

// 关闭蜂鸣器
void Buzzer_Off(void)
{
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET); // 高电平关闭蜂鸣器
}