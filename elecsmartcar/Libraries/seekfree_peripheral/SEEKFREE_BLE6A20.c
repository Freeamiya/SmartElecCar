/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		��ɿƼ�ble6a20����ģ��
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


#include "SEEKFREE_BLE6A20.h"
#include "zf_uart.h"
#include "zf_fifo.h"


static  fifo_struct     xdata ble6a20_fifo;
static  uint8           xdata ble6a20_buffer[BLE6A20_BUFFER_SIZE];  // ���ݴ������

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ble6a20����ģ��ص�����
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void ble6a20_callback(uint8 dat)
{
    // �ӵ�һ���ֽں�Ƭ��������봮���жϣ�ͨ���ڴ˴���ȡdat����ȡ������
    fifo_write_buffer(&ble6a20_fifo, &dat, 1);       // ���� FIFO
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ble6a20����ģ�鷢��һ���ֽ�
//  @param      dat 	��Ҫ���͵��ֽڳ���
//  @return     uint8	0�ɹ���1ʧ��						
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint8 ble6a20_send_byte(uint8 dat)
{
	if(BLE6A20_RTS_PIN == 1)  
	{
		return 1;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
	}
	
	uart_putchar(BLE6A20_UART_INDEX, dat);
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ble6a20����ģ�� ���ͺ���
//  @param      buff        ��Ҫ���͵����ݵ�ַ
//  @param      len         ���ͳ���
//  @return     uint32      ʣ��δ���͵��ֽ���   
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint32 ble6a20_send_buff(uint8 *buff, uint32 len)
{
    while(len>30)
    {
        if(BLE6A20_RTS_PIN == 1)  
        {
            return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
        }
        //while(RTS_PIN);  //���RTSΪ�͵�ƽ���������������
        uart_putbuff(BLE6A20_UART_INDEX,buff,30);

        buff += 30; //��ַƫ��
        len -= 30;//����
    }
    
    if(BLE6A20_RTS_PIN == 1)  
    {
        return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
    }
    //while(WIRELESS_RTS_PIN);  //���RTSΪ�͵�ƽ���������������
    uart_putbuff(BLE6A20_UART_INDEX,buff,len);//������������
    
    return 0;
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ble6a20����ģ�� ��ȡ����
//  @param      buff            �洢�����ݵ�ַ
//  @param      len             ����
//  @return     uint32          ʵ�ʶ�ȡ�ֽ���
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 ble6a20_read_buff (uint8 *buff, uint32 len)
{
    uint32 xdata data_len = len;
    fifo_read_buffer(&ble6a20_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ble6a20����ģ���ʼ��
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void ble6a20_init(void)
{
    BLE6A20_RTS_PIN = 0;
    wireless_type = WIRELESS_BLE6A20;
	wireless_module_uart_handler = ble6a20_callback;
    //������ʹ�õĲ�����Ϊ115200��Ϊble6a20����ģ���Ĭ�ϲ����ʣ�������������������������ģ�鲢�޸Ĵ��ڵĲ�����
    fifo_init(&ble6a20_fifo, FIFO_DATA_8BIT, ble6a20_buffer, BLE6A20_BUFFER_SIZE);
	uart_init(BLE6A20_UART_INDEX, BLE6A20_RX_PIN, BLE6A20_TX_PIN, BLE6A20_BAUD, BLE6A20_TIMER_N);	//��ʼ������    
    
}