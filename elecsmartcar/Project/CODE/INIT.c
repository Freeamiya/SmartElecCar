//
// Created by Free on 2024/10/18.
//
#include "headfile.h"
void System_Init(void)
{
    board_init();

////编码器方向引脚初始化
    gpio_mode(P5_3, GPIO);
    gpio_mode(P3_5, GPIO);

////按键引脚初始化
    Key_Init();

//    lcd_init();      // 初始化LCD
//    lcd_clear(BLACK);     // 清屏
//    lcd_showstr(0, 0, "ADC0:");

////测距模块初始化
    vl53l0x_init();

////OLED初始化
    oled_init_spi();

////MPU6050初始化
    MPU6050_DMP_Init();

////定时器初始化
    pit_timer_ms(TIM_4, 10);		//10ms定时器

////编码器初始化
    ctimer_count_init(CTIM0_P34);	//编码器1计数
    ctimer_count_init(CTIM3_P04);	//编码器2计数

////电机初始化
    Motor_Init();

////蜂鸣器初始化
    Buzzer_Init();

////初始化所有AD引脚
    ADC_InitAll();

    PID_Init(&Turn_PID , 0,0, 0, 0 ,0, 0);
    PID_Incremental_Init(&Left_Wheel ,0,0,0,0,0,0);//48
    PID_Incremental_Init(&Right_Wheel,0,0,0,0,0,0);//48
}