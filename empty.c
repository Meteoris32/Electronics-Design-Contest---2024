/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "board.h"
#include <stdio.h>
#include "control.h"
#include "as5600.h"
#include "gw_grayscale_sensor.h"
uint8_t grayRet;
uint8_t SensorBuf[8];
extern uint8_t NOLineFlag;
extern uint8_t ControlFlag,showFlag,ReadMPUFlag,SendFlag;
extern Car car;
int main(void)
{
    //开发板初始化
    board_init();
    float pitch=0,roll=0,yaw=0;                     //定义三个角度
	
    while(1) 
    {
			if(ControlFlag==1)
			{
				grayRet=gw_gray_serial_read();
				SEP_ALL_BIT8(grayRet,SensorBuf[0],SensorBuf[1],SensorBuf[2],SensorBuf[3],SensorBuf[4],SensorBuf[5],SensorBuf[6],SensorBuf[7]);
				XunJi(SensorBuf);
				Control();

//			GetPerEncoder();
//			MotorSet(1000,1000,0,0);//对应20
				ControlFlag=0;
			}
			if(ReadMPUFlag==1)
			{
				//灰度循迹
				beepONTimeTask();
				 if( mpu_dmp_get_data(&car.pitch,&car.roll,&car.yaw) == 0 )                                       //如果为0就串口打印数据
        { 
//            printf("pitch =%d\r\n", (int)car.pitch);
//            printf("roll =%d\r\n", (int)car.roll);
//            printf("yaw =%d\r\n\r\n", (int)car.yaw);
        }
				ReadMPUFlag=0;
			}
			if(showFlag==1)//显示阻塞程序 导致计数不准 闭环识别
			{
				
//					LCD_clear_L(0,0);display_6_8_string(0,0,"L:");display_6_8_number_f1(15,0,car.Left_Count);//显示计数器值16X8
//					LCD_clear_L(0,1);display_6_8_string(0,1,"R:");display_6_8_number_f1(15,1,car.Right_Count);//显示计数器值
//					display_6_8_string(0,2,"P:");display_6_8_number_f1(15,2,car.pitch);//显示计数器值16X6
//					display_6_8_string(0,3,"R:");display_6_8_number_f1(15,3,car.roll);//显示计数器值
					display_6_8_string(0,3,"Y:");display_6_8_number_f1(15,3,car.yaw);//显示计数器值16X6
					display_6_8_string(0,4,"Mode:");display_6_8_number_f1(30,4,car.mode);//显示计数器值16X6
					display_6_8_string(0,5,"EnALL:");display_6_8_number_f1(40,5,car.EncoderAll);//显示计数器值16X6
				display_6_8_number_f1(40,6,NOLineFlag);
				showFlag=0;
			}
    }

}














