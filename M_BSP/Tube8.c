//
// Created by 刘嘉俊 on 24-9-4.
//



#include "Tube8.h"

unsigned char LED[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};	//用于LED的8位显示缓存

unsigned char  LED_0F[17] = //低电平显示
        {// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
                0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0x7F,0x7F
        };



void FloatToString(float a, int arr[4], int *decimal_point_pos) {
    char str[10];
    snprintf(str, sizeof(str), "%.1f", a); // 将浮点数 a 转换为字符串，保留一位小数

    int index = 0;
    *decimal_point_pos = -1; // 初始化小数点位置为-1，表示没有小数点

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '.') {
            *decimal_point_pos = index; // 记录小数点的位置
        } else {
            arr[index++] = str[i] - '0'; // 将字符转换为数字并存入数组
        }
    }

    while (index < 4) {
        arr[index++] = 0; // 如果数组未填满，填入 0
    }
}

void TubeShow(int number, int data, int dot)
{
    unsigned char  *led_table;          // 查表指针
    unsigned char i;
    //显示第1位
    led_table = LED_0F + LED[data - 1];

    if (dot){
        i = *led_table&0X7F;
    }else {
        i = *led_table;
    }

    LED_OUT(i);
    LED_OUT(0x01 << (number-1));
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);//管脚输出低
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);//管脚输出高
}

void DisplayNumber(float a) {
    char str[10];
    int digits[8] = {0};  // 用于存储分离出的每一位数字
    int dotPosition = -1; // 小数点的位置

    // 将浮点数转换为字符串
    sprintf(str, "%.1f", a); // 保留一位小数，例如 "22.4"

    int len = strlen(str);
    int j = 0;

    // 分离数字和小数点
    for (int i = 0; i < len && j < 8; i++) {
        if (str[i] == '.') {
            dotPosition = j - 1; // 记录小数点位置
        } else {
            digits[j++] = str[i] - '0'; // 将字符转换为整数
        }
    }

    // 显示每一位数字
    for (int i = 0; i < j; i++) {
        TubeShow(i + 1, digits[i], (i == dotPosition)); // i+1 是数码管的位置，digits[i] 是要显示的数字
    }
}

//8位数码管主函数
void LED8_Display (void)
{
    unsigned char  *led_table;          // 查表指针
    unsigned char i;
    //显示第1位
    led_table = LED_0F + LED[7];
    i = *led_table;
    LED_OUT(i);
    LED_OUT(0x01);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);//管脚输出低
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);//管脚输出高
    //显示第2位
    led_table = LED_0F + LED[7];
    i = *led_table;
    LED_OUT(i);
    LED_OUT(0x02);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);
    //显示第3位
    led_table = LED_0F + LED[7];
    i = *led_table;//带小数点
    LED_OUT(i);
    LED_OUT(0x04);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);
    //显示第4位
    led_table = LED_0F + LED[7];
    i = *led_table;
    LED_OUT(i);
    LED_OUT(0x08);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);

    //显示第5位
    led_table = LED_0F + LED[6];
    i = *led_table;
    LED_OUT(i);
    LED_OUT(0x10);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);

    //显示第6位
    led_table = LED_0F + LED[7];
    i = *led_table;
    LED_OUT(i);
    LED_OUT(0x20);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);

    //显示第7位
    led_table = LED_0F + LED[6];
    i = *led_table;
    LED_OUT(i);
    LED_OUT(0x40);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);

    //显示第8位
    led_table = LED_0F + LED[6];
    i = *led_table&0X7F;
    LED_OUT(i);
    LED_OUT(0x80);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RCLK_PIN, GPIO_PIN_SET);
}
//管脚输出控制
void LED_OUT(unsigned char X)
{
    unsigned char i;
    for(i=8;i>=1;i--)
    {
        if (X&0x80)
        {
            HAL_GPIO_WritePin(GPIOA, DIO_PIN, GPIO_PIN_SET);
        }else
        {
            HAL_GPIO_WritePin(GPIOA, DIO_PIN, GPIO_PIN_RESET);
        }
        X<<=1;
        HAL_GPIO_WritePin(GPIOA, SCLK_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, SCLK_PIN, GPIO_PIN_SET);
    }
}