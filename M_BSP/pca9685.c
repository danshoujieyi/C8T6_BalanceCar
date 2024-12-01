//
// Created by ���ο� on 24-8-4.
//

#include "pca9685.h"

/******************************************************************
 * �� �� �� �ƣ�PCA9685_GPIO_Init
 * �� �� ˵ ����PCA9685�����ų�ʼ��
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void PCA9685_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(PORT_PCA9685, PCA_9685_SCL_Pin|PCA_9685_SDA_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : PB5 PB6 */
    GPIO_InitStruct.Pin = PCA_9685_SCL_Pin|PCA_9685_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(PORT_PCA9685, &GPIO_InitStruct);
    HAL_GPIO_WritePin(PORT_PCA9685, PCA_9685_SCL_Pin|PCA_9685_SDA_Pin, GPIO_PIN_SET);

}

/******************************************************************
 * �� �� �� �ƣ�IIC_Start
 * �� �� ˵ ����IIC��ʼʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void I2C_Start(void)
{
    PCA_SDA_OUT();

    PCA_SDA(1);
    Delay_us(5);
    PCA_SCL(1);
    Delay_us(5);

    PCA_SDA(0);
    Delay_us(5);
    PCA_SCL(0);
    Delay_us(5);

}
/******************************************************************
 * �� �� �� �ƣ�IIC_Stop
 * �� �� ˵ ����IICֹͣ�ź�
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void I2C_Stop(void)
{
    PCA_SDA_OUT();
    PCA_SCL(0);
    PCA_SDA(0);

    PCA_SCL(1);
    Delay_us(5);
    PCA_SDA(1);
    Delay_us(5);

}

/******************************************************************
 * �� �� �� �ƣ�IIC_Send_Ack
 * �� �� ˵ ������������Ӧ����߷�Ӧ���ź�
 * �� �� �� �Σ�0����Ӧ��  1���ͷ�Ӧ��
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void I2C_Send_Ack(unsigned char ack)
{
    PCA_SDA_OUT();
    PCA_SCL(0);
    PCA_SDA(0);
    Delay_us(5);
    if(!ack) PCA_SDA(0);
    else     PCA_SDA(1);
    PCA_SCL(1);
    Delay_us(5);
    PCA_SCL(0);
    PCA_SDA(1);
}


/******************************************************************
 * �� �� �� �ƣ�I2C_WaitAck
 * �� �� ˵ �����ȴ��ӻ�Ӧ��
 * �� �� �� �Σ���
 * �� �� �� �أ�0��Ӧ��  1��ʱ��Ӧ��
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
unsigned char I2C_WaitAck(void)
{

    char ack = 0;
    unsigned char ack_flag = 10;
    PCA_SCL(0);
    PCA_SDA(1);
    PCA_SDA_IN();
    Delay_us(5);
    PCA_SCL(1);
    Delay_us(5);

    while( (PCA_SDA_GET()==1) && ( ack_flag ) )
    {
        ack_flag--;
        Delay_us(5);
    }

    if( ack_flag <= 0 )
    {
        I2C_Stop();
        return 1;
    }
    else
    {
        PCA_SCL(0);
        PCA_SDA_OUT();
    }
    return ack;
}

/******************************************************************
 * �� �� �� �ƣ�Send_Byte
 * �� �� ˵ ����д��һ���ֽ�
 * �� �� �� �Σ�datҪд�˵�����
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void PCA_Send_Byte(uint8_t dat)
{
    int i = 0;
    PCA_SDA_OUT();
    PCA_SCL(0);//����ʱ�ӿ�ʼ���ݴ���

    for( i = 0; i < 8; i++ )
    {
        PCA_SDA( (dat & 0x80) >> 7 );
        Delay_us(1);
        PCA_SCL(1);
        Delay_us(5);
        PCA_SCL(0);
        Delay_us(5);
        dat<<=1;
    }
}

/******************************************************************
 * �� �� �� �ƣ�Read_Byte
 * �� �� ˵ ����IIC��ʱ��
 * �� �� �� �Σ���
 * �� �� �� �أ�����������
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
unsigned char PCA_Read_Byte(void)
{
    unsigned char i,receive=0;
    PCA_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
        PCA_SCL(0);
        Delay_us(5);
        PCA_SCL(1);
        Delay_us(5);
        receive<<=1;
        if( PCA_SDA_GET() )
        {
            receive|=1;
        }
        Delay_us(5);
    }
    PCA_SCL(0);
    return receive;
}

/******************************************************************
 * �� �� �� �ƣ�PCA9685_Write
 * �� �� ˵ ������PCA9685д���������
 * �� �� �� �Σ�addrд��ļĴ�����ַ    dataд������������
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void PCA9685_Write(uint8_t addr,uint8_t data)
{
    I2C_Start();

    PCA_Send_Byte(PCA_Addr);
    I2C_WaitAck();

    PCA_Send_Byte(addr);
    I2C_WaitAck();

    PCA_Send_Byte(data);
    I2C_WaitAck();

    I2C_Stop();
}

/******************************************************************
 * �� �� �� �ƣ�PCA9685_Read
 * �� �� ˵ ������ȡPCA9685����
 * �� �� �� �Σ�addr��ȡ�ļĴ�����ַ
 * �� �� �� �أ���ȡ������
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
uint8_t PCA9685_Read(uint8_t addr)
{
    uint8_t data;

    I2C_Start();

    PCA_Send_Byte(PCA_Addr);
    I2C_WaitAck();

    PCA_Send_Byte(addr);
    I2C_WaitAck();

    I2C_Stop();

    Delay_us(10);


    I2C_Start();

    PCA_Send_Byte(PCA_Addr|0x01);
    I2C_WaitAck();

    data = PCA_Read_Byte();
    I2C_Send_Ack(1);
    I2C_Stop();

    return data;
}
/******************************************************************
 * �� �� �� �ƣ�PCA9685_setPWM
 * �� �� ˵ �������õ�num��PWM���ţ�onĬ��Ϊ0�����ƶ����תoff�Ƕ�
 * �� �� �� �Σ�num�����õڼ��������������Χ0~15
 *              on ��Ĭ��Ϊ0
 *              off�������ת�Ƕȣ���Χ��0~180
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off)
{
    I2C_Start();

    PCA_Send_Byte(PCA_Addr);
    I2C_WaitAck();

    PCA_Send_Byte(LED0_ON_L+4*num);
    I2C_WaitAck();

    PCA_Send_Byte(on&0xFF);
    I2C_WaitAck();

    PCA_Send_Byte(on>>8);
    I2C_WaitAck();

    PCA_Send_Byte(off&0xFF);
    I2C_WaitAck();

    PCA_Send_Byte(off>>8);
    I2C_WaitAck();

    I2C_Stop();

}



/******************************************************************
 * �� �� �� �ƣ�PCA9685_setFreq
 * �� �� ˵ ��������PCA9685�����Ƶ��
 * �� �� �� �Σ�freq
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע��
floor�﷨��
FLOOR(number, significance)
    Number���衣Ҫ�������ֵ��
    Significance���衣Ҫ���뵽�ı�����
˵��
    ������ number �������루�ؾ���ֵ��С�ķ���Ϊ��ӽ��� significance �ı�����
    �����һ����Ϊ����ֵ�ͣ��� FLOOR �����ش���ֵ #VALUE!��
    ��� number �ķ���Ϊ������ significance �ķ���Ϊ������ FLOOR �����ش���ֵ #NUM!
ʾ��
    ��ʽ                                ˵��                                                                ���
    FLOOR(3.7,2)                �� 3.7 �ؾ���ֵ��С�ķ����������룬ʹ�������ӽ��� 2 �ı���                2
    FLOOR(-2.5, -2)                �� -2.5 �ؾ���ֵ��С�ķ����������룬ʹ�������ӽ��� -2 �ı���                -2
******************************************************************/
void PCA9685_setFreq(float freq)
{
    uint8_t prescale,oldmode,newmode;

    double prescaleval;

//        freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).

//        PCA9685���ڲ�ʱ��Ƶ����25Mhz
//        ��ʽ: presale_Volue = round( 25000000/(4096 * update_rate) ) - 1
//        round = floor();  floor����ѧ��������Ҫ���� math.h �ļ�
//        update_rate = freq;
    prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;
    prescale = floor(prescaleval+0.5f);

    //����MODE1��ַ�ϵ����ݣ������������ݣ�
    oldmode = PCA9685_Read(PCA_Model);

    //��MODE1������SLEEPλ
    newmode = (oldmode&0x7F)|0x10;
    //�����ĵ�MODE1��ֵд��MODE1��ַ,ʹоƬ˯��
    PCA9685_Write(PCA_Model,newmode);
    //д�����Ǽ��������Ƶ�ʵ�ֵ
    //PCA_Pre = presale ��ַ��0xFE�����������ֲ�����ҵ�
    PCA9685_Write(PCA_Pre,prescale);
    //���¸�λ
    PCA9685_Write(PCA_Model,oldmode);
    //�ȴ���λ���
    HAL_Delay(5);
    //����MODE1�Ĵ��������Զ�����
    PCA9685_Write(PCA_Model,oldmode|0xa1);
}

//
/******************************************************************
 * �� �� �� �ƣ�setAngle
 * �� �� ˵ �������ýǶ�
 * �� �� �� �Σ�numҪ���õ�PWM����     angle���õĽǶ�
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void setAngle(uint8_t num,uint8_t angle)
{
    uint32_t off = 0;

    off = (uint32_t)(158+angle*2.2);

    PCA9685_setPWM(num,0,off);
}

/******************************************************************
 * �� �� �� �ƣ�PCA9685_Init
 * �� �� ˵ ����PCA9685��ʼ��������PWM���Ƶ������������PWM��������Ķ���Ƕ�
 * �� �� �� �Σ�hz���õĳ�ʼƵ��  angle���õĳ�ʼ�Ƕ�
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void PCA9685_Init(float hz,uint8_t angle)
{
    uint32_t off = 0;

    PCA9685_GPIO_Init();

    //��MODE1��ַ��д0x00
    PCA9685_Write(PCA_Model,0x00);        //��һ���ܹؼ������û����һ��PCA9685�Ͳ�������������

//        pwm.setPWMFreq(SERVO_FREQ)������Ҫ������PCA9685�����Ƶ�ʣ�
//        PCA9685��16·PWM���Ƶ����һ�µģ������ǲ���ʵ�ֲ�ͬ���Ų�ͬƵ�ʵġ�
//        ������setPWMFreq���������ݣ���Ҫ�Ǹ���Ƶ�ʼ���PRE_SCALE��ֵ��
    PCA9685_setFreq(hz);
    //����Ƕ�
    off = (uint32_t)(145+angle*2.4);

    //����16��������off�Ƕ�
    PCA9685_setPWM(0,0,off);
    PCA9685_setPWM(1,0,off);
    PCA9685_setPWM(2,0,off);
    PCA9685_setPWM(3,0,off);
    PCA9685_setPWM(4,0,off);
    PCA9685_setPWM(5,0,off);
    PCA9685_setPWM(6,0,off);
    PCA9685_setPWM(7,0,off);
    PCA9685_setPWM(8,0,off);
    PCA9685_setPWM(9,0,off);
    PCA9685_setPWM(10,0,off);
    PCA9685_setPWM(11,0,off);
    PCA9685_setPWM(12,0,off);
    PCA9685_setPWM(13,0,off);
    PCA9685_setPWM(14,0,off);
    PCA9685_setPWM(15,0,off);

    HAL_Delay(100);

}
