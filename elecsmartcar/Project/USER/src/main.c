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



uint16 adc_data[3];

void ADC_Init_All(void);

/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */

void main()
{
	board_init();			// 初始化寄存器,勿删除此句代码。
    MPU6050_DMP_Init();         // 初始化MPU6050

    ADC_InitAll();          // 初始化ADC

//    lcd_init();      // 初始化LCD
//    lcd_clear(BLACK);     // 清屏
//    lcd_showstr(0, 0, "ADC0:");

    vl53l0x_init();     // 初始化VL53L0X

    pit_timer_ms(TIM_4, 10);    // 定时10ms
    ctimer_count_init(CTIM0_P34);	    //编码器1计数
    ctimer_count_init(CTIM3_P04);	    //编码器2计数

    Motor_Init();

    gpio_mode(P5_3, GPIO);      //编码器方向引脚初始化
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
