//
// Created by 刘嘉俊 on 24-7-25.
//

#include "pid.h"

/***************************************************************************
直立环PD控制器：Kp*Ek+Kd*Ek_D
入口：Med:机械中值(期望角度)，Angle:真实角度，gyro_Y:真实角速度
出口：PMW数值
******************************************************************************/
int Vertical(float Angle,float Gyro_Y)
{
    PWM_out = Vertical_Kp*(Angle-Med_Angle)+Vertical_Kd*(Gyro_Y+10);
    return PWM_out;
}

/*********************************************************************
速度环PI控制器：Kp*Ek+Ki*Ek_S(Ek_S：偏差的积分)
入口：左右编码器测到的数值
出口：
**********************************************************************/
int Velocity(int Encoder_left,int Encoder_right)
{
    // 定义成静态变量，保存在静态存储器，使得变量不丢掉
    static float Velocity,Encoder_Err,Encoder,Encoder_last,Movement=500; //速度，误差，编码器
    static float Encoder_Integral;					  //编码器数值积分


//    //--------------蓝牙控制----------------
//    if(1==Flag_forward) 		    Movement = -200;
//    else if(1==Flag_retreat)    Movement = 200;
//    else							    Movement = 0;


    // 计算速度偏差
    Encoder_Err = ((Encoder_Left+Encoder_Right)-0);
    // 对速度偏差进行--低通滤波--
    Encoder = Encoder_Err*0.3 + Encoder_last*0.7;// 使得波形更加平滑
    Encoder_last = Encoder; 							// 防止速度过大影响直立环的正常工作
    // 对速度偏差积分出位移,遥控的速度通过积分融入速度控制器，减缓速度突变对直立控制的影响
    Encoder_Integral += Encoder+Movement;

    // 4.积分限幅
    if(Encoder_Integral>3000)  	Encoder_Integral=3000;
    if(Encoder_Integral<-3000)	   Encoder_Integral=-3000;

    if(Moto_Flag == 1||Start_Flag ==0) 			Encoder_Integral=0;     		//===电机关闭后或者复位清除积分
    //5.速度环控制输出
    Velocity=Encoder*kp+Encoder_Integral*ki;

    return Velocity;
}

/*********************************************************************
转向环：系数*Z轴角速度+系数*遥控数据
入口：左右电机编码器测得数值，Z轴角速度
**********************************************************************/
int Turn(int Encoder_Left,int Encoder_Right,float gyro)
{
    float Turn_Target,Turn_PWM,Bias,Encoder_temp,Turn_Convert=70,Turn_Count;
    float Turn_Amplitude=100,Turn_Kp=10,Turn_Kd=0;

//    // --- 蓝牙控制 ---
//    if(1==Flag_left) 			Turn_Target+=Turn_Convert;//左转标志
//    else if(1==Flag_right)  Turn_Target-=Turn_Convert; //右转标志
//    else 						 Turn_Target=0;

    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude; //转速限幅
    if(Turn_Target<-Turn_Amplitude)  Turn_Target=-Turn_Amplitude;

//    if(Flag_forward==1||Flag_retreat==1) Turn_Kd=7;
//    else 										  Turn_Kd=0;//前进或者后退标志


    //=============turing PD controller==================//
    Turn_PWM= -Turn_Target*Turn_Kp+gyro*Turn_Kd;

    return Turn_PWM;

}


void calculate(void)
{
    Encoder_Left  =   Read_Encoder(3);		//读取编码器测量的电机转速
    Encoder_Right =   Read_Encoder(4);

    Vertical_out = Vertical(roll,gyro[1]);// 直立环输出PWM
    Velocity_out = Velocity(Encoder_Left,Encoder_Right);// 速度环输出误差

    // -------------蓝牙控制--------------
//	  if(1==Flag_left||1==Flag_right)
//			Turn_Pwm =Turn(Encoder_Left,Encoder_Right,gyroz+33);//出现左右转标志才进入转向环闭环控制
//	  else
//			Turn_Pwm=-0.5*(gyroz+33); //保持走直线


    //------------最终输出----------------
    PWM_out= Vertical_out+Velocity_out;

    // 3.把控制输出量加载到电机上，完成最终控制
    Moto1 = PWM_out;//+Turn_Pwm; // 左电机
    Moto2 = PWM_out;//-Turn_Pwm; // 右电机
    Limit(&Moto1,&Moto2);     // PWM限幅
    Set_Pwm(Moto1,Moto2);        // 加载到电机上
}