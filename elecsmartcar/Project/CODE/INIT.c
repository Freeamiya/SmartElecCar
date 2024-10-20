//
// Created by Free on 2024/10/18.
//
#include "headfile.h"
void System_Init(void)
{
    board_init();

////�������������ų�ʼ��
    gpio_mode(P5_3, GPIO);
    gpio_mode(P3_5, GPIO);

////�������ų�ʼ��
    Key_Init();

//    lcd_init();      // ��ʼ��LCD
//    lcd_clear(BLACK);     // ����
//    lcd_showstr(0, 0, "ADC0:");

////���ģ���ʼ��
    vl53l0x_init();

////OLED��ʼ��
    oled_init_spi();

////MPU6050��ʼ��
    MPU6050_DMP_Init();

////��ʱ����ʼ��
    pit_timer_ms(TIM_4, 10);		//10ms��ʱ��

////��������ʼ��
    ctimer_count_init(CTIM0_P34);	//������1����
    ctimer_count_init(CTIM3_P04);	//������2����

////�����ʼ��
    Motor_Init();

////��������ʼ��
    Buzzer_Init();

////��ʼ������AD����
    ADC_InitAll();

    PID_Init(&Turn_PID , 0,0, 0, 0 ,0, 0);
    PID_Incremental_Init(&Left_Wheel ,0,0,0,0,0,0);//48
    PID_Incremental_Init(&Right_Wheel,0,0,0,0,0,0);//48
}