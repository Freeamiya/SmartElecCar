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

//��ȡ����ADC��ͨ��ֵ����ȡƽ��ֵ
void ADC_GetValue(void)
{
	float temp;
	char i,j;
	for(i=0;i<3;i++)
	{
		ADC_Array_Original[0][i] = adc_once(ADC_P10, ADC_8BIT);		//��һ·���
		ADC_Array_Original[1][i] = adc_once(ADC_P00, ADC_8BIT);		//���·���	

		ADC_Array_Original[2][i] = adc_once(ADC_P05, ADC_8BIT);		//����·���
		
		ADC_Array_Original[3][i] = adc_once(ADC_P06, ADC_8BIT);		//�м���� 
		ADC_Array_Original[4][i] = adc_once(ADC_P16, ADC_8BIT);		//����·���
	}
	//ȡ���ε��ֵƽ��ֵ
	for(i=0;i<5;i++)
	{
		temp = 0;
		for(j=0;j<3;j++)
		{
			temp += (float)ADC_Array_Original[i][j];
		}
		ADC_proc[i] = temp/3;
		//�Ե��ֵ�޷�
		if(ADC_proc[i] >= 200)			ADC_proc[i] = 200;	
		else if(ADC_proc[i] <= 2)		ADC_proc[i] = 2;
		//��һ��,�����ֵ������0~100֮��
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
        Ratio = (Params.A*Diff+Params.B*DiffM)/(Params.A*Plus+Params.B*PlusM);	//���С��EDGE_PROTECT//�������ߣ��´�ƫ��ֵ
        Flags.Flag_Out_L = 0;		//���ϴλ������ٴμӣ�����
        Flags.Flag_Out_R = 0;
    }
//    else
//    {
//        if(ADC_proc[0] + ADC_proc[4] < 4)
//            Flag_Stop = 1;                      //�ڱ��Ͻ׶κͻ����׶��Լ���һ�ζ���δѰ��ǰ�����ж�
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
	float guess = x / 2.0f; // ��ʼ�²�ֵ
    float epsilon = 0.001f; // ����
	
    if (x < 0) {
        // ���ڸ���������һ������ֵ�������
        return -1;
    }
    if (x == 0) {
        return 0; // 0 ��ƽ������ 0
    }
    while ((guess * guess - x) > epsilon || (x - guess * guess) > epsilon) 
	{
        guess = (guess + x / guess) / 2.0f; // ���²²�ֵ
    }

    return guess;
}
