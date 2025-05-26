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
#include "board.h"
#include "stdio.h"
#include "soft_timer.h"
#include "control.h"

#define RE_0_BUFF_LEN_MAX	128

volatile uint8_t  recv0_buff[RE_0_BUFF_LEN_MAX] = {0};
volatile uint16_t recv0_length = 0;
volatile uint8_t  recv0_flag = 0;
Key key[3];
uint8_t OpenMvStopLine,Cross,NumStopLine,Firstflag;
void board_init(void)
{
	// SYSCFG��ʼ��
	SYSCFG_DL_init();
	// uart0 (debug)
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	//ʹ�ܴ����ж�
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	
	//uart1 (openmv)
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
	//ʹ�ܴ����ж�
	NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
	//uart2 (zigbee)
	NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
	//ʹ�ܴ����ж�
	NVIC_EnableIRQ(UART_2_INST_INT_IRQN);	
	//uart3 (������)
	NVIC_ClearPendingIRQ(UART_3_INST_INT_IRQN);
	//ʹ�ܴ����ж�
	NVIC_EnableIRQ(UART_3_INST_INT_IRQN);
		//mpu6050

		//�����ʱ���жϱ�־
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	//ʹ�ܶ�ʱ���ж�
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
	//Encoder
	NVIC_EnableIRQ(Encoder_INT_IRQN);

	oled_init();//oled��ʾ����ʼ��
	printf("Board Init [[ ** LCKFB ** ]]\r\n");
	MPU6050_Init();
	  while(!MPU6050_Init())
	{
		  LCD_clear_L(0,0);display_6_8_string(0,0,"MPU error\r\n");		
	}
	while( mpu_dmp_init() )
    {
        printf("dmp error\r\n");                    //���MPU6050û��ʼ���ɹ��ʹ���һֱ��ӡdmp error
        delay_ms(200);
    }
	printf("Board Init [[ ** LCKFB ** ]]\r\n");
	systemInit();
//	delay_ms(2000);
}
uint32_t i=0;
uint8_t ControlFlag,showFlag,ReadMPUFlag,SendFlag;
void clickKey ()
{
	key[0].keyState=!DL_GPIO_readPins(key_PORT,key_PIN_4_PIN);//����Ϊ0,��ʱkeystateΪ1
	key[1].keyState=!DL_GPIO_readPins(key_PORT,key_PIN_5_PIN);//����Ϊ0,��ʱkeystateΪ1
	for(int i=0;i<3;i++)
	{
		switch(key[i].state)
		{
			case 0:
			if(key[i].keyState)key[i].state=1;
				break;
			case 1:
			if(key[i].keyState)key[i].state=2;
			else
			{
				key[i].state=0;
			}
			break;
			case 2:
				if(!key[i].keyState)
				{
					key[i].state=0;
					key[i].singleFlag=1;
				}
				break;
		}
	}
}
//��ʱ�����жϷ����� ������Ϊ1�������
void TIMER_0_INST_IRQHandler(void)
{
    //��������˶�ʱ���ж�
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
    {
        case DL_TIMER_IIDX_ZERO://�����0����ж�
            //��LED�Ƶ�״̬��ת
						++i;
						if(i%10==0)
								ControlFlag=1;
						if(i%20==0)
								ReadMPUFlag=1;						
						if(i%60==0)
						{
							showFlag=1;
						}
						if(i%250==0)
						{
							SendFlag=1;
						}
						if(i%1000==0)
						{
//							sec++;
										DL_GPIO_togglePins(RGB_PORT, RGB_R_PIN|RGB_G_PIN|RGB_B_PIN);
						}
            break;

        default://�����Ķ�ʱ���ж�
            break;
    }
}
void delay_us(unsigned long __us) 
{
    delay_cycles(CPUCLK_FREQ/1000000);
}

void delay_ms(unsigned long ms) 
{
	delay_cycles(CPUCLK_FREQ/1000);
}



void delay_1us(unsigned long __us)
{ 
    delay_us(__us); 
}



void delay_1ms(unsigned long ms)
{ 
    delay_ms(ms); 
}
//����0 
void uart0_send_char(char ch)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_0_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(UART_0_INST, ch);

}
void uart0_send_string(char* str)
{
	//��ǰ�ַ�����ַ���ڽ�β ���� �ַ����׵�ַ��Ϊ��
	while(*str!=0&&str!=0)
	{
		//�����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
		uart0_send_char(*str++);
	}
}
void uart0_send_buf(uint8_t *buf,uint8_t len)
{
    for(int i = 0; i < len; i++)
    {
        uart0_send_char(buf[i]);
    }
}
//����1

void uart1_send_char(char ch)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_1_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(UART_1_INST, ch);

}
void uart1_send_string(char* str)
{
	//��ǰ�ַ�����ַ���ڽ�β ���� �ַ����׵�ַ��Ϊ��
	while(*str!=0&&str!=0)
	{
		//�����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
		uart0_send_char(*str++);
	}
}
void uart1_send_buf(uint8_t *buf,uint8_t len)
{
    for(int i = 0; i < len; i++)
    {
        uart1_send_char(buf[i]);
    }
}

#if !defined(__MICROLIB)
//��ʹ��΢��Ļ�����Ҫ�������ĺ���
#if (__ARMCLIB_VERSION <= 6000000)
//�����������AC5  �Ͷ�����������ṹ��
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
#endif


//printf�����ض���
int fputc(int ch, FILE *stream)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);
	
	return ch;
}

//���ڵ��жϷ�����
void UART_0_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	
	//��������˴����ж�
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_RX://����ǽ����ж�
			
			// ���շ��͹��������ݱ���
			receivedData = DL_UART_Main_receiveData(UART_0_INST);

			// ��黺�����Ƿ�����
			if (recv0_length < RE_0_BUFF_LEN_MAX - 1)
			{
				recv0_buff[recv0_length++] = receivedData;

				// ������������ٷ��ͳ�ȥ������ش�����ע�͵�
				uart0_send_char(receivedData);
			}
			else
			{
				recv0_length = 0;
			}

			// ��ǽ��ձ�־
			recv0_flag = 1;
		
			break;
		
		default://�����Ĵ����ж�
			break;
	}
}
uint8_t openmvBuf[10];
//����1���жϷ�����(openmv)
void UART_1_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	static uint8_t state;
	static uint8_t cnt;
	//��������˴����ж�
	switch( DL_UART_getPendingInterrupt(UART_1_INST) )
	{
		case DL_UART_IIDX_RX://����ǽ����ж�
			
			// ���շ��͹��������ݱ���
			receivedData = DL_UART_Main_receiveData(UART_1_INST);
			if (receivedData==0xff&&state==0)
			{
				state=1;
				openmvBuf[0]=receivedData;
			}
			else if(state==1)
			{
							openmvBuf[cnt+1]=receivedData;
							cnt++;
				if(cnt==9)
				{
					if(openmvBuf[9]==0xfe)
					{
//						uart1_send_buf(openmvBuf,4);
						cnt=0;
					state=0;
					}
						else			
					{
						cnt=0;
						state=0;
					}
				}
			}
		
			break;
		
		default://�����Ĵ����ж�
			break;
	}
}

//UART3������  
uint8_t SerialScreenBuf[10];
uint8_t Send2openmv[5]={0};
void UART_3_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	static uint8_t state;
	static uint8_t cnt;
	//��������˴����ж�
	switch( DL_UART_getPendingInterrupt(UART_3_INST) )
	{
		case DL_UART_IIDX_RX://����ǽ����ж�
			
			// ���շ��͹��������ݱ���
			receivedData = DL_UART_Main_receiveData(UART_3_INST);
			if (receivedData==0xff&&state==0)
			{
				state=1;
				SerialScreenBuf[0]=receivedData;
			}
			else if(state==1)
			{
					SerialScreenBuf[cnt+1]=receivedData;
					cnt++;
				if(cnt==3)
				{
					if(SerialScreenBuf[3]==0xfe)
					{
						Send2openmv[0]=SerialScreenBuf[0];
						Send2openmv[1]=SerialScreenBuf[1];
						Send2openmv[2]=SerialScreenBuf[2];
						Send2openmv[3]=SerialScreenBuf[3];
						cnt=0;
						state=0;
					}
						else			
					{
						cnt=0;
						state=0;
					}
				}
			}
		
			break;
		
		default://�����Ĵ����ж�
			break;
	}
}
//����3
void uart3_send_char(char ch)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_3_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(UART_3_INST, ch);

}
void uart3_send_buf(uint8_t *buf,uint8_t len)
{
    for(int i = 0; i < len; i++)
    {
        uart3_send_char(buf[i]);
    }
}
//UART2  zigbee
void UART_2_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	static uint8_t state;
	static uint8_t cnt;
	//��������˴����ж�
	switch( DL_UART_getPendingInterrupt(UART_2_INST) )
	{
		case DL_UART_IIDX_RX://����ǽ����ж�
			
			// ���շ��͹��������ݱ���
			receivedData = DL_UART_Main_receiveData(UART_2_INST);

			break;
		
		default://�����Ĵ����ж�
			break;
	}
}

//����2
void uart2_send_char(char ch)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_2_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(UART_2_INST, ch);

}
void uart2_send_buf(uint8_t *buf,uint8_t len)
{
    for(int i = 0; i < len; i++)
    {
        uart2_send_char(buf[i]);
    }
}