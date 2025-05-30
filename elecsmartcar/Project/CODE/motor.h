#ifndef __MOTOR_H
#define __MOTOR_H

#include "zf_tim.h"
//#include "PID.h"

#define SPEED_MAX 			8500
#define SPECIAL_SPEED 		700


extern volatile float Speed_L;
extern volatile float Speed_R;


float Num2Abs(float x);
void Limit_Out(float *Output,float Limit_Min,float Limit_Max);

void Motor_Init(void);
float Right_SetSpeed(float speed);
float Left_SetSpeed(float speed);

void Get_Speed(void);	//获取速度
void Motor_Change_Speed(void);	//改变速度
void Motor_Test(float Speed);  //用来测试电机接线
#endif
