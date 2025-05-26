#include "as5600.h"


void _us(unsigned long __us) 
{
    delay_cycles(CPUCLK_FREQ/1000000);
}



void _ms(unsigned long ms) 
{
	delay_cycles(CPUCLK_FREQ/1000);
}
/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始时序
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void AS5600_IIC_Start(void)
{
        SDA_OUT();
        SCL(1); 
        SDA(0);
        
        SDA(1);
        _us(5);
        SDA(0);
        _us(5);
                       
        SCL(0);
}
/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void AS5600_IIC_Stop(void)
{
        SDA_OUT();
        SCL(0);
        SDA(0);
        
        SCL(1);
        _us(5);
        SDA(1);
        _us(5);
        
}

/******************************************************************
 * 函 数 名 称：IIC_Send_Ack
 * 函 数 说 明：主机发送应答或者非应答信号
 * 函 数 形 参：0发送应答  1发送非应答
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void AS5600_IIC_Send_Ack(unsigned char ack)
{
        SDA_OUT();
        SCL(0);
        SDA(0);
        _us(5);
        if(!ack) SDA(0);
        else         SDA(1);
        SCL(1);
        _us(5);
        SCL(0);
        SDA(1);
}


/******************************************************************
 * 函 数 名 称：I2C_WaitAck
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：0有应答  1超时无应答
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char AS5600_I2C_WaitAck(void)
{
        
        char ack = 0;
        unsigned char ack_flag = 10;
        SCL(0);
        SDA(1);
        SDA_IN();
        
        SCL(1);
        while( (SDA_GET()==1) && ( ack_flag ) )
        {
                ack_flag--;
                _us(5);
        }
        
        if( ack_flag <= 0 )
        {
                AS5600_IIC_Stop();
                return 1;
        }
        else
        {
                SCL(0);
                SDA_OUT();
        }
        return ack;
}

/******************************************************************
 * 函 数 名 称：Send_Byte
 * 函 数 说 明：写入一个字节
 * 函 数 形 参：dat要写人的数据
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void AS5600_Send_Byte(uint8_t dat)
{
        int i = 0;
        SDA_OUT();
        SCL(0);//拉低时钟开始数据传输
        
        for( i = 0; i < 8; i++ )
        {
                SDA( (dat & 0x80) >> 7 );
                _us(1);
                SCL(1);
                _us(5);
                SCL(0);
                _us(5);
                dat<<=1;
        }        
}

/******************************************************************
 * 函 数 名 称：Read_Byte
 * 函 数 说 明：IIC读时序
 * 函 数 形 参：无
 * 函 数 返 回：读到的数据
 * 作       者：LC
 * 备       注：无
******************************************************************/
unsigned char AS5600_Read_Byte(void)
{
        unsigned char i,receive=0;
        SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
        {
        SCL(0);
        _us(5);
        SCL(1);
        _us(5);
        receive<<=1;
        if( SDA_GET() )
        {        
            receive|=1;   
        }
        _us(5); 
    }                                         
        SCL(0); 
  return receive;
}


uint8_t  AS5600_ReadOneByte(uint16_t ReadAddr)
{                  
    uint8_t temp=-1;                                                                                   
		AS5600_IIC_Start();  
    AS5600_Send_Byte((0X36<<1)|0x00);       //
    AS5600_I2C_WaitAck(); 
		AS5600_Send_Byte(ReadAddr);   //
    AS5600_I2C_WaitAck();        
    AS5600_IIC_Start();              
    AS5600_Send_Byte((0X36<<1)|0x01);           //           
    AS5600_I2C_WaitAck();     
		temp=AS5600_Read_Byte();           
		AS5600_IIC_Stop();//       
    return temp;
}


 uint16_t AS5600_ReadTwoByte(	)
{
	uint16_t TwoByte_Data=-1;
	uint8_t hi_Data=0,lo_Data=0;
	hi_Data=AS5600_ReadOneByte(_raw_ang_hi);
	lo_Data=AS5600_ReadOneByte(_raw_ang_lo);
	TwoByte_Data = (hi_Data<<8)|lo_Data;
	return TwoByte_Data;
}
