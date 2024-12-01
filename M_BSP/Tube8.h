//
// Created by 刘嘉俊 on 24-9-4.
//

#ifndef F103_TUBE8_H
#define F103_TUBE8_H

#include "main.h"
#include <stdio.h>
#include <string.h>

#define SCLK_PIN GPIO_PIN_4
#define RCLK_PIN GPIO_PIN_5
#define DIO_PIN GPIO_PIN_6

void DisplayNumber(float a);
void FloatToString(float a, int arr[4], int *decimal_point_pos);
void TubeShow(int number, int data, int dot);
void LED8_Display (void);			// LED显示
void LED_OUT(unsigned char X);				// LED单字节串行移位函数

#endif //F103_TUBE8_H
