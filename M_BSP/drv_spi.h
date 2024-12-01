//
// Created by ���ο� on 24-9-21.
//

#ifndef C8T6_BALANCE_RUBBISH_H
#define C8T6_BALANCE_RUBBISH_H

#include "stm32f1xx_hal.h"
#include "spi.h"

// SPI ���Ŷ���
#define SPI_CLK_GPIO_PORT                GPIOB                        // SCK �������ڵ� GPIO �˿�
#define SPI_CLK_GPIO_PIN                 GPIO_PIN_3                  // SCK ����
#define SPI_CLOCK_GPIO_CLK               __HAL_RCC_GPIOB_CLK_ENABLE() // ʹ�� GPIOA ʱ��

#define SPI_MISO_GPIO_PORT               GPIOB                        // MISO �������ڵ� GPIO �˿�
#define SPI_MISO_GPIO_PIN                GPIO_PIN_4                  // MISO ����
#define SPI_MISO_GPIO_CLK                __HAL_RCC_GPIOB_CLK_ENABLE() // ʹ�� GPIOA ʱ��

#define SPI_MOSI_GPIO_PORT               GPIOB                       // MOSI �������ڵ� GPIO �˿�
#define SPI_MOSI_GPIO_PIN                GPIO_PIN_5                  // MOSI ����
#define SPI_MOSI_GPIO_CLK                __HAL_RCC_GPIOB_CLK_ENABLE() // ʹ�� GPIOA ʱ��

#define SPI_NSS_GPIO_PORT                GPIOA                        // NSS �������ڵ� GPIO �˿�
#define SPI_NSS_GPIO_PIN                 GPIO_PIN_15                  // NSS ����
#define SPI_NSS_GPIO_CLK                 __HAL_RCC_GPIOA_CLK_ENABLE() // ʹ�� GPIOA ʱ��

// ����Ƭѡ���ŵĺ꣬����Ƭѡ�źŵĸߵ�
#define spi_set_nss_high( )              HAL_GPIO_WritePin(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_PIN_SET)   // Ƭѡ�ø�
#define spi_set_nss_low( )               HAL_GPIO_WritePin(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_PIN_RESET) // Ƭѡ�õ�

/******** Ӳ�� SPI �޸Ĵ˴� ********/
#define RCU_SPI_HARDWARE                 __HAL_RCC_SPI1_CLK_ENABLE() // ʹ�� SPI1 ʱ��
#define PORT_SPI                         SPI1                        // ʹ�õ� SPI ʵ����SPI1


void drv_spi_init( void );
uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );

#endif //C8T6_BALANCE_RUBBISH_H
