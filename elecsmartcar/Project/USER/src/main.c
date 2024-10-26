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
/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */

void main()
{
    System_Init();
    while(1)
	{
        vl53l0x_get_distance ();
        oled_printf_float_spi(1 ,1,Speed_L,3,2);
        oled_printf_float_spi(1,3,Speed_R,3,2);
        oled_printf_float_spi(1,5,ADC_proc[0],3,2);
        oled_printf_float_spi(1,7,ADC_proc[2],3,2);
        oled_printf_float_spi(64,1,ADC_proc[3],3,2);
        oled_printf_float_spi(64,3,Pitch,3,2);
        oled_printf_float_spi(64,5,Roll,3,2);
        oled_uint16_spi(64,7,vl53l0x_distance_mm);
		printf(":%.2f,%.2f,%.2f,%.2f,%.2f\r\n",
               Act_PwmL,Act_PwmR,Ratio,Speed_L,Speed_R);
    }
}
