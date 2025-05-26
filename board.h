/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-26     LCKFB     first version
 */
#ifndef	__BOARD_H__
#define __BOARD_H__

#include "ti_msp_dl_config.h"
#include "drv_oled.h"
#include "pid.h"
#include "bsp_mpu6050.h"
#include "inv_mpu.h"
typedef struct
{
	uint8_t keyState;
	uint8_t state;
	uint8_t singleFlag;

}Key;


void board_init(void);
void clickKey ();
void delay_us(unsigned long __us);
void delay_ms(unsigned long ms);
void delay_1us(unsigned long __us);
void delay_1ms(unsigned long ms);

void uart0_send_char(char ch);
void uart1_send_char(char ch);
void uart0_send_string(char* str);
void uart0_send_buf(uint8_t *buf,uint8_t len);;
void uart1_send_buf(uint8_t *buf,uint8_t len);
void openmvData(uint8_t *data);
void uart3_send_buf(uint8_t *buf,uint8_t len);
#endif
