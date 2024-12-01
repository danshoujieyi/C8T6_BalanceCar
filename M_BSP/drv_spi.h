//
// Created by 刘嘉俊 on 24-9-21.
//

#ifndef C8T6_BALANCE_RUBBISH_H
#define C8T6_BALANCE_RUBBISH_H

#include "stm32f1xx_hal.h"
#include "spi.h"

// SPI 引脚定义
#define SPI_CLK_GPIO_PORT                GPIOB                        // SCK 引脚所在的 GPIO 端口
#define SPI_CLK_GPIO_PIN                 GPIO_PIN_3                  // SCK 引脚
#define SPI_CLOCK_GPIO_CLK               __HAL_RCC_GPIOB_CLK_ENABLE() // 使能 GPIOA 时钟

#define SPI_MISO_GPIO_PORT               GPIOB                        // MISO 引脚所在的 GPIO 端口
#define SPI_MISO_GPIO_PIN                GPIO_PIN_4                  // MISO 引脚
#define SPI_MISO_GPIO_CLK                __HAL_RCC_GPIOB_CLK_ENABLE() // 使能 GPIOA 时钟

#define SPI_MOSI_GPIO_PORT               GPIOB                       // MOSI 引脚所在的 GPIO 端口
#define SPI_MOSI_GPIO_PIN                GPIO_PIN_5                  // MOSI 引脚
#define SPI_MOSI_GPIO_CLK                __HAL_RCC_GPIOB_CLK_ENABLE() // 使能 GPIOA 时钟

#define SPI_NSS_GPIO_PORT                GPIOA                        // NSS 引脚所在的 GPIO 端口
#define SPI_NSS_GPIO_PIN                 GPIO_PIN_15                  // NSS 引脚
#define SPI_NSS_GPIO_CLK                 __HAL_RCC_GPIOA_CLK_ENABLE() // 使能 GPIOA 时钟

// 设置片选引脚的宏，控制片选信号的高低
#define spi_set_nss_high( )              HAL_GPIO_WritePin(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_PIN_SET)   // 片选置高
#define spi_set_nss_low( )               HAL_GPIO_WritePin(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_PIN_RESET) // 片选置低

/******** 硬件 SPI 修改此次 ********/
#define RCU_SPI_HARDWARE                 __HAL_RCC_SPI1_CLK_ENABLE() // 使能 SPI1 时钟
#define PORT_SPI                         SPI1                        // 使用的 SPI 实例，SPI1


void drv_spi_init( void );
uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );

#endif //C8T6_BALANCE_RUBBISH_H
