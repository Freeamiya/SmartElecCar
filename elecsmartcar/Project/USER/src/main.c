/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"



uint16 adc_data[3];

void ADC_Init_All(void);

/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */

void main()
{
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
    MPU6050_DMP_Init();         // ��ʼ��MPU6050

    ADC_InitAll();          // ��ʼ��ADC

//    lcd_init();      // ��ʼ��LCD
//    lcd_clear(BLACK);     // ����
//    lcd_showstr(0, 0, "ADC0:");

    vl53l0x_init();     // ��ʼ��VL53L0X

    pit_timer_ms(TIM_4, 10);    // ��ʱ10ms
    ctimer_count_init(CTIM0_P34);	    //������1����
    ctimer_count_init(CTIM3_P04);	    //������2����

    Motor_Init();

    gpio_mode(P5_3, GPIO);      //�������������ų�ʼ��
    gpio_mode(P3_5, GPIO);

    oled_init_spi();

    Key_Init();
    while(1)
	{
        vl53l0x_get_distance ();
        oled_printf_float_spi(1,1,Speed_L,3,2);
//      printf("distance = %d mm\r\n", vl53l0x_distance_mm);
        printf(" %.2f ,%.2f ,%.2f ,%.2f ,%.2f, %.2f ,%.2f ",
               Speed_L, Speed_R,ADC_proc[0], ADC_proc[2], ADC_proc[3],Pitch, Roll);

    }
}
