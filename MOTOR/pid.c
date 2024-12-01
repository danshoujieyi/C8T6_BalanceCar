//
// Created by ���ο� on 24-7-25.
//

#include "pid.h"

/***************************************************************************
ֱ����PD��������Kp*Ek+Kd*Ek_D
��ڣ�Med:��е��ֵ(�����Ƕ�)��Angle:��ʵ�Ƕȣ�gyro_Y:��ʵ���ٶ�
���ڣ�PMW��ֵ
******************************************************************************/
int Vertical(float Angle,float Gyro_Y)
{
    PWM_out = Vertical_Kp*(Angle-Med_Angle)+Vertical_Kd*(Gyro_Y+10);
    return PWM_out;
}

/*********************************************************************
�ٶȻ�PI��������Kp*Ek+Ki*Ek_S(Ek_S��ƫ��Ļ���)
��ڣ����ұ������⵽����ֵ
���ڣ�
**********************************************************************/
int Velocity(int Encoder_left,int Encoder_right)
{
    // ����ɾ�̬�����������ھ�̬�洢����ʹ�ñ���������
    static float Velocity,Encoder_Err,Encoder,Encoder_last,Movement=500; //�ٶȣ���������
    static float Encoder_Integral;					  //��������ֵ����


//    //--------------��������----------------
//    if(1==Flag_forward) 		    Movement = -200;
//    else if(1==Flag_retreat)    Movement = 200;
//    else							    Movement = 0;


    // �����ٶ�ƫ��
    Encoder_Err = ((Encoder_Left+Encoder_Right)-0);
    // ���ٶ�ƫ�����--��ͨ�˲�--
    Encoder = Encoder_Err*0.3 + Encoder_last*0.7;// ʹ�ò��θ���ƽ��
    Encoder_last = Encoder; 							// ��ֹ�ٶȹ���Ӱ��ֱ��������������
    // ���ٶ�ƫ����ֳ�λ��,ң�ص��ٶ�ͨ�����������ٶȿ������������ٶ�ͻ���ֱ�����Ƶ�Ӱ��
    Encoder_Integral += Encoder+Movement;

    // 4.�����޷�
    if(Encoder_Integral>3000)  	Encoder_Integral=3000;
    if(Encoder_Integral<-3000)	   Encoder_Integral=-3000;

    if(Moto_Flag == 1||Start_Flag ==0) 			Encoder_Integral=0;     		//===����رպ���߸�λ�������
    //5.�ٶȻ��������
    Velocity=Encoder*kp+Encoder_Integral*ki;

    return Velocity;
}

/*********************************************************************
ת�򻷣�ϵ��*Z����ٶ�+ϵ��*ң������
��ڣ����ҵ�������������ֵ��Z����ٶ�
**********************************************************************/
int Turn(int Encoder_Left,int Encoder_Right,float gyro)
{
    float Turn_Target,Turn_PWM,Bias,Encoder_temp,Turn_Convert=70,Turn_Count;
    float Turn_Amplitude=100,Turn_Kp=10,Turn_Kd=0;

//    // --- �������� ---
//    if(1==Flag_left) 			Turn_Target+=Turn_Convert;//��ת��־
//    else if(1==Flag_right)  Turn_Target-=Turn_Convert; //��ת��־
//    else 						 Turn_Target=0;

    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude; //ת���޷�
    if(Turn_Target<-Turn_Amplitude)  Turn_Target=-Turn_Amplitude;

//    if(Flag_forward==1||Flag_retreat==1) Turn_Kd=7;
//    else 										  Turn_Kd=0;//ǰ�����ߺ��˱�־


    //=============turing PD controller==================//
    Turn_PWM= -Turn_Target*Turn_Kp+gyro*Turn_Kd;

    return Turn_PWM;

}


void calculate(void)
{
    Encoder_Left  =   Read_Encoder(3);		//��ȡ�����������ĵ��ת��
    Encoder_Right =   Read_Encoder(4);

    Vertical_out = Vertical(roll,gyro[1]);// ֱ�������PWM
    Velocity_out = Velocity(Encoder_Left,Encoder_Right);// �ٶȻ�������

    // -------------��������--------------
//	  if(1==Flag_left||1==Flag_right)
//			Turn_Pwm =Turn(Encoder_Left,Encoder_Right,gyroz+33);//��������ת��־�Ž���ת�򻷱ջ�����
//	  else
//			Turn_Pwm=-0.5*(gyroz+33); //������ֱ��


    //------------�������----------------
    PWM_out= Vertical_out+Velocity_out;

    // 3.�ѿ�����������ص�����ϣ�������տ���
    Moto1 = PWM_out;//+Turn_Pwm; // ����
    Moto2 = PWM_out;//-Turn_Pwm; // �ҵ��
    Limit(&Moto1,&Moto2);     // PWM�޷�
    Set_Pwm(Moto1,Moto2);        // ���ص������
}