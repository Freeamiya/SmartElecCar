/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/
#include "headfile.h"
/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */

void main()
{
    System_Init();
    while(1)
	{
//        vl53l0x_get_distance ();
//        oled_printf_float_spi(1 ,1,Speed_L,3,2);
//        oled_printf_float_spi(1,3,Speed_R,3,2);
//        oled_printf_float_spi(1,5,ADC_proc[0],3,2);
//        oled_printf_float_spi(1,7,ADC_proc[2],3,2);
//        oled_printf_float_spi(64,1,ADC_proc[3],3,2);
//        oled_printf_float_spi(64,3,Pitch,3,2);
//        oled_printf_float_spi(64,5,Roll,3,2);
//        oled_uint16_spi(64,7,vl53l0x_distance_mm);
		printf(":%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\r\n",
		Ratio,Speed_L,Speed_R,Exp_Speed_L,Exp_Speed_R,Voltage_Detect());
    }
}
