/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		��ɿƼ�����ת����ģ��
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-03-27
 * @note		
					���߶��壺
					------------------------------------ 
					BLE6A20����      ��Ƭ��                        
    				RX              �鿴SEEKFREE_BLE6A20.h�ļ��е�BLE6A20_TX_PIN�궨��
    				TX              �鿴SEEKFREE_BLE6A20.h�ļ��е�BLE6A20_RX_PIN�궨��
    				RTS             �鿴SEEKFREE_BLE6A20.h�ļ��е�BLE6A20_RTS_PIN�궨��
					------------------------------------ 
 ********************************************************************************************************************/

#ifndef _SEEKFREE_BLE6A20_
#define _SEEKFREE_BLE6A20_

#include "common.h"


#define BLE6A20_UART_INDEX        		UART_4         //����ת����ģ�� ��ʹ�õ��Ĵ���     
#define BLE6A20_TX_PIN    				UART4_TX_P03
#define BLE6A20_RX_PIN    				UART4_RX_P02
#define BLE6A20_TIMER_N    				TIM_2
#define BLE6A20_BAUD   					115200
#define BLE6A20_RTS_PIN P07 			//��������λ����  ָʾ��ǰģ���Ƿ���Խ�������  0���Լ�������  1�����Լ�������

#define BLE6A20_BUFFER_SIZE       		64
#define BLE6A20_TIMEOUT_COUNT     		500


void ble6a20_init(void);
void ble6a20_callback(uint8 dat);

uint8  ble6a20_send_byte(uint8 dat);
uint32 ble6a20_send_buff(uint8 *buff, uint32 len);
uint32 ble6a20_read_buff(uint8 *buff, uint32 len);

#endif 
