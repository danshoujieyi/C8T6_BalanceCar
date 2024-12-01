////
//// Created by ���ο� on 24-9-21.
////
//
//#include "drv_spi.h"
///*
// * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
// * �����������www.lckfb.com
// * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
// * ������̳��https://oshwhub.com/forum
// * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
// * ��������׬Ǯ���������й�����ʦΪ����
// * Change Logs:
// * Date           Author       Notes
// * 2024-04-01     LCKFB-LP    first version
// */
//
//#include "drv_spi.h"
//
///** Ӳ��SPI */
//#define SPI_WAIT_TIMEOUT       ((uint16_t)0xFFFF)
//
///**
//  * @brief :SPI��ʼ��(Ӳ��)
//  * @param :��
//  * @note  :��
//  * @retval:��
//  */
//// SPI ���
//SPI_HandleTypeDef hspi;
//
//// SPI ��ʼ������
//void drv_spi_init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//    // ʹ�� GPIO ʱ��
//    __HAL_RCC_GPIOA_CLK_ENABLE();  // ���� SPI ������ GPIOA, ����ʵ���������
//    __HAL_RCC_GPIOB_CLK_ENABLE();  // ���� SPI ������ GPIOB, ����ʵ���������
//    // ʹ�� SPI ʱ��
//    __HAL_RCC_SPI1_CLK_ENABLE(); // ����ʹ�õ� SPI ʵ��ѡ�� SPI1, SPI2, �� SPI3
//
//    // ���� SPI ���� SCK
//    GPIO_InitStruct.Pin = SPI_CLK_GPIO_PIN; // ����ʵ�����Ÿ���
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // �����������
//    GPIO_InitStruct.Pull = GPIO_NOPULL;      // ��������
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // ����
//    HAL_GPIO_Init(SPI_CLK_GPIO_PORT, &GPIO_InitStruct); // ����ʵ�ʶ˿ڸ���
//
//    // ���� SPI ���� MOSI
//    GPIO_InitStruct.Pin = SPI_MOSI_GPIO_PIN; // ����ʵ�����Ÿ���
//    HAL_GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStruct); // ����ʵ�ʶ˿ڸ���
//
//    // ���� SPI ���� MISO
//    GPIO_InitStruct.Pin = SPI_MISO_GPIO_PIN; // ����ʵ�����Ÿ���
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;   // ��������
//    GPIO_InitStruct.Pull = GPIO_NOPULL;       // ��������
//    HAL_GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStruct); // ����ʵ�ʶ˿ڸ���
//
//    // ���� SPI ���� CS
//    GPIO_InitStruct.Pin = SPI_NSS_GPIO_PIN; // ����ʵ�����Ÿ���
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // �������
//    GPIO_InitStruct.Pull = GPIO_NOPULL; // ��������
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // ����
//    HAL_GPIO_Init(SPI_NSS_GPIO_PORT, &GPIO_InitStruct); // ����ʵ�ʶ˿ڸ���
//
//    // ���� CS ����Ϊ��
//    HAL_GPIO_WritePin(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN, GPIO_PIN_SET);
//
//    // FLASH_SPI ����
//    hspi.Instance = SPI1; // ����ʵ��ʹ�õ� SPI ʵ��ѡ��
//    hspi.Init.Mode = SPI_MODE_MASTER; // ����ģʽ
//    hspi.Init.Direction = SPI_DIRECTION_2LINES; // ȫ˫������
//    hspi.Init.DataSize = SPI_DATASIZE_8BIT; // 8 λ����
//    hspi.Init.CLKPolarity = SPI_POLARITY_LOW; // ʱ�Ӽ���
//    hspi.Init.CLKPhase = SPI_PHASE_1EDGE; // ʱ����λ
//    hspi.Init.NSS = SPI_NSS_SOFT; // ������� NSS
//    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // ������Ԥ��Ƶ
//    hspi.Init.FirstBit = SPI_FIRSTBIT_MSB; // ��λ����
//
//    // ��ʼ�� SPI
//    if (HAL_SPI_Init(&hspi) != HAL_OK)
//    {
//        //��ʼ��������
//        Error_Handler(); // �û��趨�� Error_Handler ����
//    }
//
//    // ʹ�� FLASH_SPI
//    __HAL_SPI_ENABLE(&hspi);
//}
//
///**
//  * @brief :SPI�շ�һ���ֽ�
//  * @param :
//  *                        @TxByte: ���͵������ֽ�
//  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
//  * @retval:���յ����ֽ�
//  */
//uint8_t drv_spi_read_write_byte( uint8_t TxByte )
//{
//    uint8_t l_Data = 0;
//    uint16_t l_WaitTime = 0;
//
//    while(RESET == SPI_I2S_GetFlagStatus(PORT_SPI, SPI_I2S_FLAG_TXE))//�ȴ����ͻ�����Ϊ��
//    {
//        if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
//        {
//            break;                        //����ȴ���ʱ���˳�
//        }
//    }
//    l_WaitTime = SPI_WAIT_TIMEOUT / 2;                //�������ý��յȴ�ʱ��(��ΪSPI���ٶȺܿ죬����������ڷ������֮��������յ����ݣ��ȴ�ʱ�䲻��Ҫ����)
//    SPI_I2S_SendData(PORT_SPI, TxByte);//��������
//
//    while(RESET == SPI_I2S_GetFlagStatus(PORT_SPI, SPI_I2S_FLAG_RXNE))//�ȴ����ջ������ǿ�
//    {
//        if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
//        {
//            break;                        //����ȴ���ʱ���˳�
//        }
//    }
//    l_Data = SPI_I2S_ReceiveData(PORT_SPI);//��ȡ��������
//
//    return l_Data;                //����
//}
//
///**
//  * @brief :SPI�շ��ַ���
//  * @param :
//  *                        @ReadBuffer: �������ݻ�������ַ
//  *                        @WriteBuffer:�����ֽڻ�������ַ
//  *                        @Length:�ֽڳ���
//  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
//  * @retval:��
//  */
//void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
//{
//    spi_set_nss_low( );//����Ƭѡ
//    while( Length-- )
//    {
//        *ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );                //�շ�����
//        ReadBuffer++;
//        WriteBuffer++;                                //��д��ַ��1
//    }
//    spi_set_nss_high( );//����Ƭѡ
//}