#include "zf_tim.h"
#include "common.h"
#include "Motor.h"
#include "ZF_PWM.h"
#include "ADC.h"
#include "Control.h"

volatile float Speed_L=0,Speed_R=0;

void Limit_Out(float *Output,float Limit_Min,float Limit_Max)
{
    if (*Output <= Limit_Min) *Output = Limit_Min;
    else if (*Output >= Limit_Max) *Output = Limit_Max;
}

//#define Num2Abs(x)    ((x) < 0 ? -(x) : (x))
float Num2Abs(float x)
{
	if(x < 0)
		return -x;
	return x;
}

void Motor_Init(void)//四路PWM信号控制两个电机
{
	pwm_init(PWMA_CH1P_P60, 15000, 0);		//左电机-
    pwm_init(PWMA_CH2P_P62, 15000, 0);		//左电机-PWM
    
	pwm_init(PWMA_CH3P_P64, 15000, 0);		//右电机-
	pwm_init(PWMA_CH4P_P66, 15000, 0);		//右电机-PWM
}

float Left_SetSpeed(float speed)
{
	static int16 Special_NumL = 0;  //异常情况记数
	if(Num2Abs(Speed_L) >= SPECIAL_SPEED)  		//连续10次都超过最大速度，发生异常
		Special_NumL++;
	else 
		Special_NumL = 0;
	if(Special_NumL >= 10)   		//出现异常
	{
		pwm_duty(PWMA_CH2P_P62, 0);
		pwm_duty(PWMA_CH1P_P60, 0);
		return 0;
	}
	else				 //没有出现异常
	{
		if(speed >= SPEED_MAX)			speed = SPEED_MAX; 
		else if(speed <= -SPEED_MAX)	speed = -SPEED_MAX;
		if(speed >= 0)
		{
			pwm_duty(PWMA_CH2P_P62, (uint32)speed);
			pwm_duty(PWMA_CH1P_P60, 0);
		} 
		else if(speed < 0)
		{
			pwm_duty(PWMA_CH2P_P62, 0);
			pwm_duty(PWMA_CH1P_P60, -(int)speed);
		} 
		return speed;
	}
}

float Right_SetSpeed(float speed)	
{
	static int16 Special_NumR = 0;  //异常情况记数
	if(Num2Abs(Speed_R) >= SPECIAL_SPEED)  		//连续10次都超过最大速度，发生异常
		Special_NumR++;
	else 
		Special_NumR = 0;
	if(Special_NumR >= 10)   		//出现异常
    {
        pwm_duty(PWMA_CH3P_P64, 0);
        pwm_duty(PWMA_CH4P_P66, 0);
        return 0;
    }else
    {
        if(speed >= SPEED_MAX)			speed = SPEED_MAX;
        else if(speed <= -SPEED_MAX)	speed = -SPEED_MAX;
        if(speed >= 0)
        {
            pwm_duty(PWMA_CH3P_P64, (uint32)speed);
            pwm_duty(PWMA_CH4P_P66, 0);
        }
        else if(speed < 0)
        {
            pwm_duty(PWMA_CH3P_P64, 0);
            pwm_duty(PWMA_CH4P_P66, -(int)speed);
        }
        return speed;
    }
}

 void Get_Speed(void)	//获取速度
{
	static float Speed_L_Last;
	static float Speed_R_Last;
	if(P53 == 0)  		 Speed_L = (float)ctimer_count_read(CTIM3_P04);	////左轮方向读取数值
	else  				{Speed_L = (float)ctimer_count_read(CTIM3_P04); Speed_L = -Speed_L;}
	ctimer_count_clean(CTIM3_P04);									//清除计数值，开始下一轮计数

	
	if(P35 == 1)		 Speed_R = (float)ctimer_count_read(CTIM0_P34);		//右轮方向读取数值
	else  				{Speed_R = (float)ctimer_count_read(CTIM0_P34); Speed_R = -Speed_R;}
	ctimer_count_clean(CTIM0_P34);									//清除计数值，开始下一轮计数
	
	Speed_L = Speed_L_Last*0.7f + Speed_L*0.3f;
	Speed_R = Speed_R_Last*0.7f + Speed_R*0.3f;
	Speed_L_Last = Speed_L;
	Speed_R_Last = Speed_R;
	
}

void Motor_Change_Speed(void)
{
    if(Ratio >= -0.15 && Ratio <= 0.15) //直线
    {
        Exp_Speed = NORMAL_SPEED;
    }
    else
    {
        Exp_Speed = NORMAL_SPEED-30-Num2Abs(Ratio)*90;
    }
}

void Motor_Test(float Speed)
{
	Right_SetSpeed(-Speed);
	Left_SetSpeed(Speed);	
}
