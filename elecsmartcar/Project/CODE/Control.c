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
    Get_Speed();        //获取速度
    ADC_GetValue();			//获取电感值
    MPU6050_Refresh_DMP();				//读取角度值
    MPU_Get_Gyroscope(&gx, &gy, &gz);	//读取角速度
    Get_Ratio();        //计算偏差值
    Motor_Change_Speed();               //电机期望速度变化
    Limit_Out(&Ratio,-0.9f,0.9f);   //差比和限幅
    PID_Calculate(&Turn_PID,0,Ratio*100);
    Limit_Out(&Turn_PID.PID_Out,-4000,4000);
    if(Ratio >= 0)
    {
        Exp_Speed_L = Exp_Speed + Turn_PID.PID_Out*0.03f;
        Exp_Speed_R = Exp_Speed - Turn_PID.PID_Out*0.03f;
    }
    else
    {
        Exp_Speed_L = Exp_Speed + Turn_PID.PID_Out*0.03f;
        Exp_Speed_R = Exp_Speed - Turn_PID.PID_Out*0.03f;
    }
    PID_Incremental_Calc(&Left_Wheel,Exp_Speed_L,Speed_L);
    PID_Incremental_Calc(&Right_Wheel,Exp_Speed_R,Speed_R);
    Act_PwmL = Left_SetSpeed(Left_Wheel.out);
    Act_PwmR = Right_SetSpeed(Right_Wheel.out);
}


