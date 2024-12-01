//
// Created by 刘嘉俊 on 24-9-16.
//

#ifndef C8T6_BALANCE_DHT11_H
#define C8T6_BALANCE_DHT11_H

#include "robot_config.h"

/**************引脚修改此处****************/
#define RCU_DHT11   __HAL_RCC_GPIOA_CLK_ENABLE()  // 使能GPIOB时钟
#define PORT_DHT11  GPIOA
#define GPIO_DHT11  GPIO_PIN_12

// 设置DHT11输出高或低电平
#define DATA_GPIO_OUT(x)    HAL_GPIO_WritePin(PORT_DHT11, GPIO_DHT11, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)
// 获取DHT11数据引脚高低电平状态
#define DATA_GPIO_IN        HAL_GPIO_ReadPin(PORT_DHT11, GPIO_DHT11)

extern float temperature;
extern float humidity;

void DHT11_GPIO_Init(void);//引脚初始化
unsigned int DHT11_Read_Data(void);//读取模块数据
float Get_temperature(void);//返回读取模块后的温度数据
float Get_humidity(void);//返回读取模块后的湿度数据

#endif
