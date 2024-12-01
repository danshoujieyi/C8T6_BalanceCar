//
// Created by ���ο� on 24-9-19.
//

#include "buzzer.h"
// GPIO ��ʼ������

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ʹ��GPIOAʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ����PA11Ϊ�������
    GPIO_InitStruct.Pin = BUZZER_PIN; // ʹ��PA11���Ʒ�����
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // �������ģʽ
    GPIO_InitStruct.Pull = GPIO_PULLUP; // ��������
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // ����
    HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}

// �򿪷�����
void Buzzer_On(void)
{
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET); // �͵�ƽ����������
}

// �رշ�����
void Buzzer_Off(void)
{
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET); // �ߵ�ƽ�رշ�����
}