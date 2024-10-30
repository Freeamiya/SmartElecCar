//
// Created by Free on 2024/10/23.
//

#include "Control.h"
#include "headfile.h"

float Exp_Speed;
float Exp_Speed_L,Exp_Speed_R;
short gx,gy,gz;
float Act_PwmL,Act_PwmR;

void Control_Speed(void)
{
    Get_Speed();        //��ȡ�ٶ�
    ADC_GetValue();			//��ȡ���ֵ
    Get_Ratio();        //����ƫ��ֵ
    MPU6050_Refresh_DMP();				//��ȡ�Ƕ�ֵ
    MPU_Get_Gyroscope(&gx, &gy, &gz);	//��ȡ���ٶ�
    Motor_Change_Speed();               //��������ٶȱ仯
    Limit_Out(&Ratio,-0.9f,0.9f);   //��Ⱥ��޷�
    Exp_Speed = NORMAL_SPEED;
    PID_Calculate(&Turn_PID,Ratio*150,gz/100);
//    Limit_Out(&Turn_PID.PID_Out,-8000,8000);
    if(Ratio >= 0)
    {
        Exp_Speed_L = Exp_Speed + Turn_PID.PID_Out*0.09f;
        Exp_Speed_R = Exp_Speed - Turn_PID.PID_Out*0.08f*(1-Ratio);
    }
    else
    {
        Exp_Speed_L = Exp_Speed + Turn_PID.PID_Out*0.08f*(1+Ratio);
        Exp_Speed_R = Exp_Speed - Turn_PID.PID_Out*0.09f;
    }
    PID_Incremental_Calc(&Left_Wheel,Exp_Speed_L,Speed_L);
    PID_Incremental_Calc(&Right_Wheel,Exp_Speed_R,Speed_R);
    Act_PwmL = Left_SetSpeed(Left_Wheel.out);
    Act_PwmR = Right_SetSpeed(Right_Wheel.out);
}


