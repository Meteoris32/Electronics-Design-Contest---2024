/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
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
	// SYSCFG初始化
	SYSCFG_DL_init();
	// uart0 (debug)
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	//使能串口中断
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
	
	//uart1 (openmv)
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
	//使能串口中断
	NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
	//uart2 (zigbee)
	NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
	//使能串口中断
	NVIC_EnableIRQ(UART_2_INST_INT_IRQN);	
	//uart3 (串口屏)
	NVIC_ClearPendingIRQ(UART_3_INST_INT_IRQN);
	//使能串口中断
	NVIC_EnableIRQ(UART_3_INST_INT_IRQN);
		//mpu6050

		//清除定时器中断标志
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	//使能定时器中断
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
	//Encoder
	NVIC_EnableIRQ(Encoder_INT_IRQN);

	oled_init();//oled显示屏初始化
	printf("Board Init [[ ** LCKFB ** ]]\r\n");
	MPU6050_Init();
	  while(!MPU6050_Init())
	{
		  LCD_clear_L(0,0);display_6_8_string(0,0,"MPU error\r\n");		
	}
	while( mpu_dmp_init() )
    {
        printf("dmp error\r\n");                    //如果MPU6050没初始化成功就串口一直打印dmp error
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
	key[0].keyState=!DL_GPIO_readPins(key_PORT,key_PIN_4_PIN);//按下为0,此时keystate为1
	key[1].keyState=!DL_GPIO_readPins(key_PORT,key_PIN_5_PIN);//按下为0,此时keystate为1
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
//定时器的中断服务函数 已配置为1秒的周期
void TIMER_0_INST_IRQHandler(void)
{
    //如果产生了定时器中断
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
    {
        case DL_TIMER_IIDX_ZERO://如果是0溢出中断
            //将LED灯的状态翻转
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

        default://其他的定时器中断
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
//串口0 
void uart0_send_char(char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_0_INST) == true );
	//发送单个字符
	DL_UART_Main_transmitData(UART_0_INST, ch);

}
void uart0_send_string(char* str)
{
	//当前字符串地址不在结尾 并且 字符串首地址不为空
	while(*str!=0&&str!=0)
	{
		//发送字符串首地址中的字符，并且在发送完成之后首地址自增
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
//串口1

void uart1_send_char(char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_1_INST) == true );
	//发送单个字符
	DL_UART_Main_transmitData(UART_1_INST, ch);

}
void uart1_send_string(char* str)
{
	//当前字符串地址不在结尾 并且 字符串首地址不为空
	while(*str!=0&&str!=0)
	{
		//发送字符串首地址中的字符，并且在发送完成之后首地址自增
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
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif


//printf函数重定义
int fputc(int ch, FILE *stream)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);
	
	return ch;
}

//串口的中断服务函数
void UART_0_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	
	//如果产生了串口中断
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_RX://如果是接收中断
			
			// 接收发送过来的数据保存
			receivedData = DL_UART_Main_receiveData(UART_0_INST);

			// 检查缓冲区是否已满
			if (recv0_length < RE_0_BUFF_LEN_MAX - 1)
			{
				recv0_buff[recv0_length++] = receivedData;

				// 将保存的数据再发送出去，不想回传可以注释掉
				uart0_send_char(receivedData);
			}
			else
			{
				recv0_length = 0;
			}

			// 标记接收标志
			recv0_flag = 1;
		
			break;
		
		default://其他的串口中断
			break;
	}
}
uint8_t openmvBuf[10];
//串口1的中断服务函数(openmv)
void UART_1_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	static uint8_t state;
	static uint8_t cnt;
	//如果产生了串口中断
	switch( DL_UART_getPendingInterrupt(UART_1_INST) )
	{
		case DL_UART_IIDX_RX://如果是接收中断
			
			// 接收发送过来的数据保存
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
		
		default://其他的串口中断
			break;
	}
}

//UART3串口屏  
uint8_t SerialScreenBuf[10];
uint8_t Send2openmv[5]={0};
void UART_3_INST_IRQHandler(void)
{
	uint8_t receivedData = 0;
	static uint8_t state;
	static uint8_t cnt;
	//如果产生了串口中断
	switch( DL_UART_getPendingInterrupt(UART_3_INST) )
	{
		case DL_UART_IIDX_RX://如果是接收中断
			
			// 接收发送过来的数据保存
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
		
		default://其他的串口中断
			break;
	}
}
//串口3
void uart3_send_char(char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_3_INST) == true );
	//发送单个字符
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
	//如果产生了串口中断
	switch( DL_UART_getPendingInterrupt(UART_2_INST) )
	{
		case DL_UART_IIDX_RX://如果是接收中断
			
			// 接收发送过来的数据保存
			receivedData = DL_UART_Main_receiveData(UART_2_INST);

			break;
		
		default://其他的串口中断
			break;
	}
}

//串口2
void uart2_send_char(char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_2_INST) == true );
	//发送单个字符
	DL_UART_Main_transmitData(UART_2_INST, ch);

}
void uart2_send_buf(uint8_t *buf,uint8_t len)
{
    for(int i = 0; i < len; i++)
    {
        uart2_send_char(buf[i]);
    }
}