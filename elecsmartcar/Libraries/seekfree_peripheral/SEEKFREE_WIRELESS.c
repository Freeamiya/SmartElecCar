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
					����ת����      ��Ƭ��                        
    				RX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_INDEX_TX�궨��
    				TX              �鿴SEEKFREE_WIRELESS.h�ļ��е�WIRELESS_UART_INDEX_RX�궨��
    				RTS             �鿴SEEKFREE_WIRELESS.h�ļ��е�RTS_PIN�궨��
    				CMD             �鿴SEEKFREE_WIRELESS.h�ļ��е�CMD_PIN�궨��
					------------------------------------ 
 ********************************************************************************************************************/


#include "SEEKFREE_WIRELESS.h"
#include "zf_uart.h"
#include "zf_fifo.h"


static  fifo_struct     xdata wireless_uart_fifo;
static  uint8           xdata wireless_uart_buffer[WIRELESS_BUFFER_SIZE];  // ���ݴ������

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ��ص�����
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_callback(uint8 dat)
{
    // �ӵ�һ���ֽں�Ƭ��������봮���жϣ�ͨ���ڴ˴���ȡdat����ȡ������
    fifo_write_buffer(&wireless_uart_fifo, &dat, 1);       // ���� FIFO
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�鷢��һ���ֽ�
//  @param      dat 	��Ҫ���͵��ֽڳ���
//  @return     uint8	0�ɹ���1ʧ��					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint8 wireless_uart_send_byte(uint8 dat)
{
	if(WIRELESS_RTS_PIN == 1)  
	{
		return 1;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
	}
	
	uart_putchar(WIRELESS_UART_INDEX, dat);
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� ���ͺ���
//  @param      buff        ��Ҫ���͵����ݵ�ַ
//  @param      len         ���ͳ���
//  @return     uint32      ʣ��δ���͵��ֽ���   
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_buff(uint8 *buff, uint32 len)
{
    while(len>30)
    {
        if(WIRELESS_RTS_PIN == 1)  
        {
            return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
        }
        //while(RTS_PIN);  //���RTSΪ�͵�ƽ���������������
        uart_putbuff(WIRELESS_UART_INDEX,buff,30);

        buff += 30; //��ַƫ��
        len -= 30;//����
    }
    
    if(WIRELESS_RTS_PIN == 1)  
    {
        return len;//ģ��æ,�������ǰ����ʹ��while�ȴ� �����ʹ�ú���ע�͵�while�ȴ�����滻��if���
    }
    //while(WIRELESS_RTS_PIN);  //���RTSΪ�͵�ƽ���������������
    uart_putbuff(WIRELESS_UART_INDEX,buff,len);//������������
    
    return 0;
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת����ģ�� ��ȡ����
//  @param      buff            �洢�����ݵ�ַ
//  @param      len             ����
//  @return     uint32          ʵ�ʶ�ȡ�ֽ���
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_read_buff (uint8 *buff, uint32 len)
{
    uint32 xdata data_len = len;
    fifo_read_buffer(&wireless_uart_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ת ����ģ���ʼ��
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_init(void)
{
    WIRELESS_RTS_PIN = 0;
    wireless_type = WIRELESS_SI24R1;
	wireless_module_uart_handler = wireless_uart_callback;
    //������ʹ�õĲ�����Ϊ115200��Ϊ����ת����ģ���Ĭ�ϲ����ʣ�������������������������ģ�鲢�޸Ĵ��ڵĲ�����
    fifo_init(&wireless_uart_fifo, FIFO_DATA_8BIT, wireless_uart_buffer, WIRELESS_BUFFER_SIZE);
	uart_init(WIRELESS_UART_INDEX, WIRELESS_UART_RX_PIN, WIRELESS_UART_TX_PIN, WIRELESS_UART_BAUD, WIRELESS_TIMER_N);	//��ʼ������    
    
}