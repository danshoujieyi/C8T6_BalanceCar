//
// Created by ���ο� on 24-9-19.
//

#include "gray_detection.h"

_gray_state gray_state;

float gray_status[2]={0},gray_status_backup[2][20]={0};//�Ҷȴ�����״̬����ʷֵ
uint32_t gray_status_worse=0;	//�Ҷȹ��쳣״̬������



/***************************************************
������: void gpio_input_init(void)
˵��:	12·�Ҷȹ�gpio����ʼ��
���:	��
����:	��
��ע:	��
����:	��������
****************************************************/
void gpio_input_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; // ����һ��GPIO�ṹ�����

    // ʹ��GPIOA��GPIOB��ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // ����GPIOA������Ϊ��������
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // ����ģʽ
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;    // ����ģʽ
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // ����Ϊ����

    // ��ʼ��GPIOA
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ����GPIOB������Ϊ��������
    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;

    // �ٴ�����Ϊ����ģʽ����������
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}




/***************************************************
������: void gpio_input_check_channel_12(void)
˵��:	12·�Ҷȹ�gpio���
���:	��
����:	��
��ע:	��
����:	��������
****************************************************/
void gpio_input_check_channel_12(void)
{
    gray_state.gray.bit1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    gray_state.gray.bit2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
    gray_state.gray.bit3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
    gray_state.gray.bit4 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);

    gray_state.gray.bit5 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
    gray_state.gray.bit6 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
    gray_state.gray.bit7 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
    gray_state.gray.bit8 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);

    gray_state.gray.bit9  = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
    gray_state.gray.bit10 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
    gray_state.gray.bit11 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
    gray_state.gray.bit12 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);

    for(uint16_t i=19;i>0;i--)
    {
        gray_status_backup[0][i]=gray_status_backup[0][i-1];
    }
    gray_status_backup[0][0]=gray_status[0];
    switch(gray_state.state)
    {
        case 0x0001:gray_status[0]=-11;gray_status_worse/=2;break;									//000000000001b
        case 0x0003:gray_status[0]=-10;gray_status_worse/=2;break;									//000000000011b
        case 0x0002:gray_status[0]=-9;	gray_status_worse/=2;break;									//000000000010b
        case 0x0006:gray_status[0]=-8;	gray_status_worse/=2;break;									//000000000110b
        case 0x0004:gray_status[0]=-7;	gray_status_worse/=2;break;									//000000000100b
        case 0x000C:gray_status[0]=-6;	gray_status_worse/=2;break;									//000000001100b
        case 0x0008:gray_status[0]=-5;	gray_status_worse/=2;break;									//000000001000b
        case 0x0018:gray_status[0]=-4;	gray_status_worse/=2;break;									//000000011000b
        case 0x0010:gray_status[0]=-3;	gray_status_worse/=2;break;									//000000010000b
        case 0x0030:gray_status[0]=-2;	gray_status_worse/=2;break;									//000000110000b
        case 0x0020:gray_status[0]=-1;	gray_status_worse/=2;break;									//000000100000b
        case 0x0060:gray_status[0]=0;		gray_status_worse/=2;break;									//000001100000b
        case 0x0040:gray_status[0]=1;		gray_status_worse/=2;break;									//000001000000b
        case 0x00C0:gray_status[0]=2;		gray_status_worse/=2;break;									//000011000000b
        case 0x0080:gray_status[0]=3;		gray_status_worse/=2;break;									//000010000000b
        case 0x0180:gray_status[0]=4;		gray_status_worse/=2;break;									//000110000000b
        case 0x0100:gray_status[0]=5;		gray_status_worse/=2;break;									//000100000000b
        case 0x0300:gray_status[0]=6;		gray_status_worse/=2;break;									//001100000000b
        case 0x0200:gray_status[0]=7;		gray_status_worse/=2;break;									//001000000000b
        case 0x0600:gray_status[0]=8;		gray_status_worse/=2;break;									//011000000000b
        case 0x0400:gray_status[0]=9;		gray_status_worse/=2;break;									//010000000000b
        case 0x0C00:gray_status[0]=10;	gray_status_worse/=2;break;									//110000000000b
        case 0x0800:gray_status[0]=11;	gray_status_worse/=2;break;									//100000000000b
        case 0x0000:gray_status[0]=gray_status_backup[0][0];gray_status_worse++;break; //00000000b
        default://����������������ж�
        {
            gray_status[0]=gray_status_backup[0][0];
            gray_status_worse++;
        }
    }

    static uint16_t tmp_cnt=0;
    switch(gray_state.state)//ֹͣ�߼��
    {
        case 0x0030:tmp_cnt++;break;//000000110000b
        case 0x0020:tmp_cnt++;break;//000000100000b
        case 0x0060:tmp_cnt++;break;//000001100000b
        case 0x0040:tmp_cnt++;break;//000001000000b
        case 0x00C0:tmp_cnt++;break;//000011000000b
        case 0x00F0://000011110000b
        {
            if(tmp_cnt>=10)
            {
                tmp_cnt=0;
            }
        }
            break;
    }
}