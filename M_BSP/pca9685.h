//
// Created by 刘嘉俊 on 24-8-4.
//

#ifndef C8T6_BALANCE_PCA9685_H
#define C8T6_BALANCE_PCA9685_H

#include "robot_config.h"

//端口移植
#define RCC_PCA9685_GPIO          RCC_APB2Periph_GPIOA
#define PORT_PCA9685              GPIOB

#define PCA_9685_SDA_Pin              GPIO_PIN_9
#define PCA_9685_SCL_Pin              GPIO_PIN_8
#define GPIO_PIN_SDA                  PCA_9685_SDA_Pin
#define GPIO_PIN_SCL                  PCA_9685_SCL_Pin


// HAL库
#define PCA_SDA_OUT()   {                                   \
                        GPIO_InitTypeDef GPIO_InitStruct; \
                        GPIO_InitStruct.Pin = GPIO_PIN_SDA; \
                        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; \
                        GPIO_InitStruct.Pull = GPIO_NOPULL; \
                        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; \
                        HAL_GPIO_Init(PORT_PCA9685, &GPIO_InitStruct); \
                    }

#define PCA_SDA_IN()    {                                   \
                        GPIO_InitTypeDef GPIO_InitStruct; \
                        GPIO_InitStruct.Pin = GPIO_PIN_SDA; \
                        GPIO_InitStruct.Mode = GPIO_MODE_INPUT; \
                        GPIO_InitStruct.Pull = GPIO_PULLUP; \
                        HAL_GPIO_Init(PORT_PCA9685, &GPIO_InitStruct); \
                    }

#define PCA_SDA_GET()   HAL_GPIO_ReadPin(PORT_PCA9685, GPIO_PIN_SDA)

#define PCA_SDA(x)      HAL_GPIO_WritePin(PORT_PCA9685, GPIO_PIN_SDA, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define PCA_SCL(x)      HAL_GPIO_WritePin(PORT_PCA9685, GPIO_PIN_SCL, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)


//设置SDA输出模式 标准库
//#define SDA_OUT()   {        \
//                        GPIO_InitTypeDef  GPIO_InitStructure; \
//                        GPIO_InitStructure.GPIO_Pin = GPIO_SDA; \
//                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; \
//                        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; \
//                        GPIO_Init(GPIOA, &GPIO_InitStructure); \
//                     }
//设置SDA输入模式 标准库
//#define SDA_IN()    {        \
//                        GPIO_InitTypeDef  GPIO_InitStructure; \
//                        GPIO_InitStructure.GPIO_Pin = GPIO_SDA; \
//                        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; \
//                        GPIO_Init(GPIOA, &GPIO_InitStructure); \
//                    }
//
////获取SDA引脚的电平变化
//#define SDA_GET()       GPIO_ReadInputDataBit(GPIOA, GPIO_SDA)
////SDA与SCL输出
//#define SDA(x)          GPIO_WriteBit(GPIOA, GPIO_SDA, (x?Bit_SET:Bit_RESET) )
//#define SCL(x)          GPIO_WriteBit(GPIOA, GPIO_SCL, (x?Bit_SET:Bit_RESET) )

void PCA9685_Init(float hz,uint8_t angle);
void setAngle(uint8_t num,uint8_t angle);
void PCA9685_setFreq(float freq);
void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off);


#define PCA_Addr              0x80        //IIC地址
#define PCA_Model             0x00
#define LED0_ON_L             0x06
#define LED0_ON_H             0x07
#define LED0_OFF_L            0x08
#define LED0_OFF_H            0x09
#define PCA_Pre               0xFE        //配置频率地址


#endif //C8T6_BALANCE_PCA9685_H
