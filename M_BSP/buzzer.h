//
// Created by ���ο� on 24-9-19.
//

#ifndef C8T6_BALANCE_BUZZER_H
#define C8T6_BALANCE_BUZZER_H

#include "stm32f1xx_hal.h" // �������ľ���оƬѡ����ʵ�HALͷ�ļ�

// �����������������
#define BUZZER_PORT GPIOA
#define BUZZER_PIN GPIO_PIN_11


// ����ԭ��
void Buzzer_Init(void);  // ��ʼ������������
void Buzzer_On(void);    // �򿪷�����
void Buzzer_Off(void);   // �رշ�����

#endif //C8T6_BALANCE_BUZZER_H