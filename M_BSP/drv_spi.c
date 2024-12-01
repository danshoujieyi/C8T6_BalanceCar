////
//// Created by 刘嘉俊 on 24-9-21.
////
//
//#include "drv_spi.h"
///*
// * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
// * 开发板官网：www.lckfb.com
// * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
// * 立创论坛：https://oshwhub.com/forum
// * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
// * 不靠卖板赚钱，以培养中国工程师为己任
// * Change Logs:
// * Date           Author       Notes
// * 2024-04-01     LCKFB-LP    first version
// */
//
//#include "drv_spi.h"
//
///** 硬件SPI */
//#define SPI_WAIT_TIMEOUT       ((uint16_t)0xFFFF)
//
///**
//  * @brief :SPI初始化(硬件)
//  * @param :无
//  * @note  :无
//  * @retval:无
//  */
//// SPI 句柄
//SPI_HandleTypeDef hspi;
//
//// SPI 初始化函数
//void drv_spi_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//    // 使能 GPIO 时钟
//    __HAL_RCC_GPIOA_CLK_ENABLE();  // 假设 SPI 引脚在 GPIOA, 根据实际情况更改
//    __HAL_RCC_GPIOB_CLK_ENABLE();  // 假设 SPI 引脚在 GPIOB, 根据实际情况更改
//    // 使能 SPI 时钟
//    __HAL_RCC_SPI1_CLK_ENABLE(); // 根据使用的 SPI 实例选择 SPI1, SPI2, 或 SPI3
//
//    // 配置 SPI 引脚 SCK
//    GPIO_InitStruct.Pin = SPI_CLK_GPIO_PIN; // 根据实际引脚更改
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // 复用推挽输出
//    GPIO_InitStruct.Pull = GPIO_NOPULL;      // 无上下拉
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
//    HAL_GPIO_Init(SPI_CLK_GPIO_PORT, &GPIO_InitStruct); // 根据实际端口更改
//
//    // 配置 SPI 引脚 MOSI
//    GPIO_InitStruct.Pin = SPI_MOSI_GPIO_PIN; // 根据实际引脚更改
//    HAL_GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStruct); // 根据实际端口更改
//
//    // 配置 SPI 引脚 MISO
//    GPIO_InitStruct.Pin = SPI_MISO_GPIO_PIN; // 根据实际引脚更改
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;   // 浮空输入
//    GPIO_InitStruct.Pull = GPIO_NOPULL;       // 无上下拉
//    HAL_GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStruct); // 根据实际端口更改
//
//    // 配置 SPI 引脚 CS
//    GPIO_InitStruct.Pin = SPI_NSS_GPIO_PIN; // 根据实际引脚更改
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
//    GPIO_InitStruct.Pull = GPIO_NOPULL; // 无上下拉
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
//    HAL_GPIO_Init(SPI_NSS_GPIO_PORT, &GPIO_InitStruct); // 根据实际端口更改
//
//    // 设置 CS 引脚为高
//    HAL_GPIO_WritePin(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_PIN_SET);
//
//    // FLASH_SPI 配置
//    hspi.Instance = SPI1; // 根据实际使用的 SPI 实例选择
//    hspi.Init.Mode = SPI_MODE_MASTER; // 主机模式
//    hspi.Init.Direction = SPI_DIRECTION_2LINES; // 全双工传输
//    hspi.Init.DataSize = SPI_DATASIZE_8BIT; // 8 位数据
//    hspi.Init.CLKPolarity = SPI_POLARITY_LOW; // 时钟极性
//    hspi.Init.CLKPhase = SPI_PHASE_1EDGE; // 时钟相位
//    hspi.Init.NSS = SPI_NSS_SOFT; // 软件控制 NSS
//    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // 波特率预分频
//    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB; // 高位优先
//
//    // 初始化 SPI
//    if (HAL_SPI_Init(&hspi) != HAL_OK)
//    {
//        //初始化错误处理
//        Error_Handler(); // 用户需定义 Error_Handler 函数
//    }
//
//    // 使能 FLASH_SPI
//    __HAL_SPI_ENABLE(&hspi);
//}
//
///**
//  * @brief :SPI收发一个字节
//  * @param :
//  *                        @TxByte: 发送的数据字节
//  * @note  :非堵塞式，一旦等待超时，函数会自动退出
//  * @retval:接收到的字节
//  */
//uint8_t drv_spi_read_write_byte( uint8_t TxByte )
//{
//    uint8_t l_Data = 0;
//    uint16_t l_WaitTime = 0;
//
//    while(RESET == SPI_I2S_GetFlagStatus(PORT_SPI, SPI_I2S_FLAG_TXE))//等待发送缓冲区为空
//    {
//        if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
//        {
//            break;                        //如果等待超时则退出
//        }
//    }
//    l_WaitTime = SPI_WAIT_TIMEOUT / 2;                //重新设置接收等待时间(因为SPI的速度很快，正常情况下在发送完成之后会立即收到数据，等待时间不需要过长)
//    SPI_I2S_SendData(PORT_SPI, TxByte);//发送数据
//
//    while(RESET == SPI_I2S_GetFlagStatus(PORT_SPI, SPI_I2S_FLAG_RXNE))//等待接收缓冲区非空
//    {
//        if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
//        {
//            break;                        //如果等待超时则退出
//        }
//    }
//    l_Data = SPI_I2S_ReceiveData(PORT_SPI);//读取接收数据
//
//    return l_Data;                //返回
//}
//
///**
//  * @brief :SPI收发字符串
//  * @param :
//  *                        @ReadBuffer: 接收数据缓冲区地址
//  *                        @WriteBuffer:发送字节缓冲区地址
//  *                        @Length:字节长度
//  * @note  :非堵塞式，一旦等待超时，函数会自动退出
//  * @retval:无
//  */
//void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
//{
//    spi_set_nss_low( );//拉低片选
//    while( Length-- )
//    {
//        *ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );                //收发数据
//        ReadBuffer++;
//        WriteBuffer++;                                //读写地址加1
//    }
//    spi_set_nss_high( );//拉高片选
//}