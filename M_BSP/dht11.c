//
// Created by ���ο� on 24-9-16.
//


#include "dht11.h"

extern float temperature;
extern float humidity;

// ��ʼ�� DHT11 GPIO
void DHT11_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIOBʱ��
    RCU_DHT11; // ʹ�� GPIOB ʱ��

    GPIO_InitStructure.Pin = GPIO_DHT11; // ��������
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // ����Ϊ�������
    GPIO_InitStructure.Pull = GPIO_NOPULL; // ����������
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // �����ٶ�Ϊ����

    // ��ʼ�� GPIO
    HAL_GPIO_Init(PORT_DHT11, &GPIO_InitStructure);

    // ���� DHT11 ��������Ϊ�ߵ�ƽ
    DATA_GPIO_OUT(1);
}

/******************************************************************
 * �� �� �� �ƣ�DHT11_GPIO_Mode_OUT
 * �� �� ˵ ��������DHT11����������Ϊ���ģʽ
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void DHT11_GPIO_Mode_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIO����Ϊ���ģʽ
    GPIO_InitStructure.Pin = GPIO_DHT11; // ��������
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // �������ģʽ
    GPIO_InitStructure.Pull = GPIO_NOPULL; // ������������
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // ����Ϊ����

    // ����HAL�⺯����ʼ��GPIO
    HAL_GPIO_Init(PORT_DHT11, &GPIO_InitStructure);
}


/******************************************************************
 * �� �� �� �ƣ�DHT11_GPIO_Mode_IN
 * �� �� ˵ ��������DHT11����������Ϊ����ģʽ
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void DHT11_GPIO_Mode_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ����GPIO����Ϊ��������ģʽ
    GPIO_InitStructure.Pin = GPIO_DHT11; // ��������
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // ����ģʽ
    GPIO_InitStructure.Pull = GPIO_PULLUP; // ��������
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // ����Ϊ����

    // ����HAL�⺯����ʼ��GPIO
    HAL_GPIO_Init(PORT_DHT11, &GPIO_InitStructure);
}

/******************************************************************
 * �� �� �� �ƣ�DHT11_Read_Data
 * �� �� ˵ ��������ʱ���ȡ��ʪ������
 * �� �� �� �Σ���
 * �� �� �� �أ�0=����У��ʧ��  ����=��ʪ��δ���������
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
unsigned int DHT11_Read_Data(void)
{
    int i;
    long long val=0;
    int timeout=0;
    float small_point=0;
    unsigned char verify_num = 0;//��ֵ֤

    DATA_GPIO_OUT(0);//����������͵�ƽ
    HAL_Delay(19);  // ��ʼ�źű���ʱ��19ms
    DATA_GPIO_OUT(1);//�����ͷ�����
    Delay_us( 20 );//���ߵȴ�

    DHT11_GPIO_Mode_IN();//������תΪ����ģʽ
    //���ǰ��û�д�����ģ��ᷢ���͵�ƽ��Ӧ���źţ�����ֱ�ӵȴ�DHT11���ߣ�80us
    timeout = 5000;
    while( (! DATA_GPIO_IN ) && ( timeout >0 ) )timeout--;         //�ȴ��ߵ�ƽ�ĵ���

    //ģ�鵱ǰ��������׼��������ݣ�����ֱ�ӵȴ�DHT11���ͣ�80us
    timeout = 5000;//���ó�ʱʱ��
    //DATA_GPIO_IN=0ʱ,while�����������˳�while ˵�����յ���Ӧ�ź�
    //��timeout<=0ʱ��while�����������˳�while  ˵����ʱ
    while( DATA_GPIO_IN && ( timeout >0 ) )timeout-- ;         //�ȴ��͵�ƽ�ĵ���

#define CHECK_TIME 28 //ʵ�ⷢ�ֳ���0ֵ�ĸߵ�ƽʱ��
    for(i=0;i<40;i++)//ѭ������40λ����
    {
        timeout = 5000;
        while( ( !DATA_GPIO_IN ) && (timeout > 0) ) timeout--;         //�ȴ��͵�ƽ��ȥ

        Delay_us(CHECK_TIME);//����0ֵ�ĸߵ�ƽʱ��
        if ( DATA_GPIO_IN )//������Ǹߵ�ƽ��˵����1ֵ
        {
            val=(val<<1)+1;
        }
        else //����ǵ͵�ƽ��˵����0ֵ
        {
            val<<=1;
        }

        timeout = 5000;
        while( DATA_GPIO_IN && (timeout > 0) ) timeout-- ;         //������Ǹߵ�ƽ
    }

    DHT11_GPIO_Mode_OUT();//תΪ���ģʽ
    DATA_GPIO_OUT(1);//�����ͷ�����

    //           ʪ��8     + ʪ��8      + �¸�8     + �µ�8
    verify_num = (val>>32) + (val>>24) + (val>>16) + (val>>8);
    //�����У��� �� ���յ�У��� �Ĳ�Ϊ0˵��һ�£���Ϊ0˵����һ��
    verify_num = verify_num - (val&0xff);
    //����У��
    if( verify_num  )
    {
//      У�����
        return 0;
    }
    else //У��ɹ�
    {
        //���ݴ���
        humidity = (val>>32)&0xff;//ʪ��ǰ8λ��С����ǰ���ݣ�
        small_point = (val>>24)&0x00ff;//ʪ�Ⱥ�8λ��С��������ݣ�
        small_point = small_point * 0.1;//����ΪС����
        humidity = humidity + small_point;//С��ǰ+С����
//        printf("ʪ�ȣ�%.2f\r\n",humidity);

        temperature = (val>>16)&0x0000ff;//�¶�ǰ8λ��С����ǰ���ݣ�
        small_point = (val>>8)&0x000000ff;//�¶Ⱥ�8λ��С��������ݣ�
        small_point = small_point * 0.1;//����ΪС����
        temperature = temperature + small_point;//С��ǰ+С����
//        printf("�¶ȣ�%.2f\r\n",temperature);

        return val>>8; //����δ���������
    }
}

/******************************************************************
 * �� �� �� �ƣ�Get_temperature
 * �� �� ˵ ������ȡ�¶�����
 * �� �� �� �Σ���
 * �� �� �� �أ��¶�ֵ
 * ��       �ߣ�LC
 * ��       ע��ʹ��ǰ�����ȵ��� DHT11_Read_Data ��ȡ������
******************************************************************/
float Get_temperature(void)
{
    return temperature;
}

/******************************************************************
 * �� �� �� �ƣ�Get_humidity
 * �� �� ˵ ������ȡʪ������
 * �� �� �� �Σ���
 * �� �� �� �أ�ʪ��ֵ
 * ��       �ߣ�LC
 * ��       ע��ʹ��ǰ�����ȵ��� DHT11_Read_Data ��ȡ������
******************************************************************/
float Get_humidity(void)
{
    return humidity;
}