#include "common.h"
#include "zf_adc.h"
#include "ADC.h"
#include "Flag.h"
#include "motor.h"
#include "Control.h"

uint16 ADC_Array_Original[5][3];
float Diff,Plus;
float DiffM,PlusM;
float Ratio = 0;
float sum_L,sum_R;
float ADC_proc[5];
float Last_Ratio;
float Voltage;
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
//        Flags.Flag_Out_L = 0;		//在上次基础上再次加（减）
//        Flags.Flag_Out_R = 0;
        Last_Ratio = Ratio;

    }
    else {
        if (Last_Ratio>0 ) {
            Exp_Speed = 130;
            Ratio = 0.24+(Speed_L/110)*0.15;
        } else if (Last_Ratio<0 ) {
            Exp_Speed = 130;
            Ratio = -0.24-(Speed_L/110)*0.15;
        }
    }
}

float Voltage_Detect(void)
{
    uint16 ADC_Value;
    ADC_Value = adc_once(ADC_P15, ADC_8BIT);
    Voltage = (float)(ADC_Value*2.2*4/255);
    return Voltage;
}
