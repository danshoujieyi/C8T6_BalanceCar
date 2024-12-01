//
// Created by ���ο� on 24-9-16.
//

#ifndef C8T6_BALANCE_DHT11_H
#define C8T6_BALANCE_DHT11_H

#include "robot_config.h"

/**************�����޸Ĵ˴�****************/
#define RCU_DHT11   __HAL_RCC_GPIOA_CLK_ENABLE()  // ʹ��GPIOBʱ��
#define PORT_DHT11  GPIOA
#define GPIO_DHT11  GPIO_PIN_12

// ����DHT11����߻�͵�ƽ
#define DATA_GPIO_OUT(x)    HAL_GPIO_WritePin(PORT_DHT11, GPIO_DHT11, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)
// ��ȡDHT11�������Ÿߵ͵�ƽ״̬
#define DATA_GPIO_IN        HAL_GPIO_ReadPin(PORT_DHT11, GPIO_DHT11)

extern float temperature;
extern float humidity;

void DHT11_GPIO_Init(void);//���ų�ʼ��
unsigned int DHT11_Read_Data(void);//��ȡģ������
float Get_temperature(void);//���ض�ȡģ�����¶�����
float Get_humidity(void);//���ض�ȡģ����ʪ������

#endif
