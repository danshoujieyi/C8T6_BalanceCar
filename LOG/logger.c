//
// Created by Áõ¼Î¿¡ on 24-9-14.
//


#include "logger.h"
#include "logger.h"
#include "usart.h"

#define LOG_UART_HANDLE huart3

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&LOG_UART_HANDLE, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

void log_dump(const uint8_t *data, uint16_t len)
{
    uint8_t ch, cl;
    for (int i = 0; i < len; i++) {
        ch = data[i] >> 4;
        cl = data[i] & 0x0F;
        if (ch < 10) ch += '0'; else ch += 'A' - 10;
        if (cl < 10) cl += '0'; else cl += 'A' - 10;
        HAL_UART_Transmit(&LOG_UART_HANDLE, &ch, 1, HAL_MAX_DELAY);
        HAL_UART_Transmit(&LOG_UART_HANDLE, &cl, 1, HAL_MAX_DELAY);
        printf(" ");
        if ((i + 1) % 16 == 0) {
            printf("\r\n");
        } else if ((i + 1) % 8 == 0) {
            ch = ' ';
            HAL_UART_Transmit(&LOG_UART_HANDLE, &ch, 1, HAL_MAX_DELAY);
            HAL_UART_Transmit(&LOG_UART_HANDLE, &ch, 1, HAL_MAX_DELAY);
            HAL_UART_Transmit(&LOG_UART_HANDLE, &ch, 1, HAL_MAX_DELAY);
            HAL_UART_Transmit(&LOG_UART_HANDLE, &ch, 1, HAL_MAX_DELAY);
        } else {
            ch = ' ';
            HAL_UART_Transmit(&LOG_UART_HANDLE, &ch, 1, HAL_MAX_DELAY);
        }
    }
    printf("\r\n");
}