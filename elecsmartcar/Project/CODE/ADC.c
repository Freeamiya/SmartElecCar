#include "common.h"
#include "zf_adc.h"
#include "ADC.h"
#include "Flag.h"
#include "motor.h"

uint16 ADC_Array_Original[5][3];
float Diff,Plus;
float DiffM,PlusM;
float Ratio = 0;
float sum_L,sum_R;
float ADC_proc[5];
void ADC_InitAll(void)
{
	adc_init(ADC_P10, ADC_SYSclk_DIV_2);
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);
	
	adc_init(ADC_P16, ADC_SYSclk_DIV_2);

	adc_init(ADC_P05, ADC_SYSclk_DIV_2);
	adc_init(ADC_P06, ADC_SYSclk_DIV_2);
}

//读取三次ADC各通道值，并取平均值
void ADC_GetValue(void)
{
	float temp;
	char i,j;
	for(i=0;i<3;i++)
	{
		ADC_Array_Original[0][i] = adc_once(ADC_P10, ADC_8BIT);		//左一路电感
		ADC_Array_Original[1][i] = adc_once(ADC_P00, ADC_8BIT);		//左二路电感	

		ADC_Array_Original[2][i] = adc_once(ADC_P05, ADC_8BIT);		//右三路电感
		
		ADC_Array_Original[3][i] = adc_once(ADC_P06, ADC_8BIT);		//中间横电感 
		ADC_Array_Original[4][i] = adc_once(ADC_P16, ADC_8BIT);		//右四路电感
	}
	//取三次电感值平均值
	for(i=0;i<5;i++)
	{
		temp = 0;
		for(j=0;j<3;j++)
		{
			temp += (float)ADC_Array_Original[i][j];
		}
		ADC_proc[i] = temp/3;
		//对电感值限幅
		if(ADC_proc[i] >= 200)			ADC_proc[i] = 200;	
		else if(ADC_proc[i] <= 2)		ADC_proc[i] = 2;
		//归一化,将电感值限制在0~100之间
		ADC_proc[i] = 100*(ADC_proc[i]/200);	

	}
}
void Get_Ratio(void)
{
    float sum_01;
    float sum_34;
    float sum;

    Diff = ADC_proc[0] - ADC_proc[4];
    Plus = ADC_proc[0] + ADC_proc[4];
    DiffM= ADC_proc[1] - ADC_proc[3];
    PlusM= ADC_proc[1] + ADC_proc[3];

    sum_01= ADC_proc[0] + ADC_proc[1];
    sum_34= ADC_proc[3] + ADC_proc[4];
    sum   = sum_01 + sum_34;

    if(sum > EDGE_PROTECT)
    {
        Ratio = (Params.A*Diff+Params.B*DiffM)/(Params.A*Plus+Params.B*PlusM);	//如果小于EDGE_PROTECT//视作丢线，下次偏差值
        Flags.Flag_Out_L = 0;		//在上次基础上再次加（减）
        Flags.Flag_Out_R = 0;
    }
//    else
//    {
//        if(ADC_proc[0] + ADC_proc[4] < 4)
//            Flag_Stop = 1;                      //在避障阶段和环岛阶段以及上一次丢线未寻回前不做判断
//        else if(Barrier_Executed == 1 && Circle_Flag1 == 0 && Circle_Delay2 == 0 && Edge_Delay == 0)
//        {
//            Edge_Delay = 10;	//50ms
//            if(sum_01 >= sum_34 && Flag_Out_R == 0)
//            {
//                //x10_ms = 10;
//                Flag_Out_L = 1;
//            }
//            else if(sum_01 < sum_34 && Flag_Out_L == 0)
//            {
//                //x10_ms = 10;
//                Flag_Out_R = 1;
//            }
//        }
//    }
}
float sqrtf_custom(float x) {
	float guess = x / 2.0f; // 初始猜测值
    float epsilon = 0.001f; // 精度
	
    if (x < 0) {
        // 对于负数，返回一个特殊值或处理错误
        return -1;
    }
    if (x == 0) {
        return 0; // 0 的平方根是 0
    }
    while ((guess * guess - x) > epsilon || (x - guess * guess) > epsilon) 
	{
        guess = (guess + x / guess) / 2.0f; // 更新猜测值
    }

    return guess;
}
