
#include "headfile.h"



void Buzzer_Init(void)
{
	pwm_init(PWMB_CH4_P77,2000,0);
}

void Buzzer_Loud(uint16 times)
{
    //·äÃùÆ÷
    if(times > 0)
    {
        pwm_duty(PWMB_CH4_P77,2000);
        times--;
    }
    else
        pwm_duty(PWMB_CH4_P77,0);
}







