#include "gw_grayscale_sensor.h"
#include "ti_msp_dl_config.h"
#include "board.h"
#include "control.h"
extern Car car;
uint8_t NOLineFlag=1;
uint8_t gw_gray_serial_read()
{
	uint8_t ret = 0; /* 把8个bit塞进这个变量里 */
	uint8_t i;
	/* 循环八次 */
	for (int i = 0; i < 8; ++i) {
		//输出下降沿
		DL_GPIO_clearPins(GrayScale_PORT,GrayScale_CLK_PIN);
		//延时
		delay_us(4);
		ret |=(!DL_GPIO_readPins(GrayScale_PORT,GrayScale_DAT_PIN))<<i;
		DL_GPIO_setPins(GrayScale_PORT,GrayScale_CLK_PIN);
		delay_us(4);
	}
	return ret;
}

void XunJi(uint8_t *data)
{
	static uint8_t i1,i2;
	if(data[0]==0&&data[1]==0&&data[2]==0&&data[3]==0&&data[4]==0&&data[5]==0&&data[6]==0&&data[7]==0)
	{
		if(++i1>2)
		{
		NOLineFlag=1;//没线
			car.SenorErro=0;
			i1=0;
		}
		
	}
	else
	{
		if(++i2>2)
		{
			i2=0;
		NOLineFlag=0;//有线
		}
	}
	//0 1 2   (3 4)   5 6 7
	if(data[3]==1&&data[4]==1)
	{
		car.SenorErro=0;
	}
	if(data[3]==1&&data[4]==0)
	{
		car.SenorErro=0.5;
	}
	if(data[4]==1&&data[3]==0)
	{
		car.SenorErro=-0.5;
	}

  if(data[5]==1)
	{
		car.SenorErro=-1.0;
	}
	if(data[6]==1)
	{
		car.SenorErro=-1.5;
	}
	if(data[7]==1)
	{
		car.SenorErro=-4.5;
	}
	
	if(data[2]==1)
	{
	  car.SenorErro=1;
	}
	if(data[1]==1)
	{
		car.SenorErro=1.5;
	}
	if(data[0]==1)
	{
		car.SenorErro=4.5;
	}
}