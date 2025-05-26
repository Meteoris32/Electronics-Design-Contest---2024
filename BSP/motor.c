#include "motor.h"

void  MotorSet(int motor_b,int motor_a,uint16_t servo1,uint16_t servo2)
{
	//Forward and reverse control of motor
	//电机正反转控制DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, a,GPIO_PWM_Motor_C0_IDX)
	if(motor_a<0)	
	{
	DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, -motor_a,GPIO_PWM_Motor_C0_IDX);
	DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, 3200,GPIO_PWM_Motor_C1_IDX);
	}
	else 	
	{
		DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, 3200,GPIO_PWM_Motor_C0_IDX);
	DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, motor_a,GPIO_PWM_Motor_C1_IDX);
	}
	
	//Forward and reverse control of motor
	//电机正反转控制	
	if(motor_b<0)		
	{
		DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, -motor_b,GPIO_PWM_Motor_C2_IDX);
	DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, 3200,GPIO_PWM_Motor_C3_IDX);
	
	}
	else
	{
		DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, 3200,GPIO_PWM_Motor_C2_IDX);
	DL_TimerA_setCaptureCompareValue(PWM_Motor_INST, motor_b,GPIO_PWM_Motor_C3_IDX);
	}
	//500 1000 1500 2000 2500
	DL_TimerA_setCaptureCompareValue(Servo_INST, servo1,GPIO_Servo_C0_IDX);
DL_TimerA_setCaptureCompareValue(Servo_INST, servo2,GPIO_Servo_C1_IDX);
}

extern Car car;
int32_t Front_Left_Count = 0;
int32_t Front_Right_Count = 0;
extern float TargetEncoder;
float alpha=0.6f;
void GetPerEncoder()
{
		car.Left_Count=Front_Left_Count;
		car.Right_Count=Front_Right_Count;
	  car.Filtered_Left_Count = alpha * car.Left_Count + (1.0f - alpha) * car.Filtered_Left_Count;
    car.Filtered_Right_Count = alpha * car.Right_Count + (1.0f - alpha) * car.Filtered_Right_Count;
		car.EncoderAll+=(car.Filtered_Left_Count+car.Filtered_Right_Count)/2.0f;
			printf("%.1f,%.1f\n",(car.Filtered_Left_Count+car.Filtered_Right_Count)/2,TargetEncoder);
		Front_Left_Count=0;
	Front_Right_Count=0;
	
}
void GROUP1_IRQHandler(void)
{
    
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(Encoder_PORT,
    Encoder_PIN_0_PIN | Encoder_PIN_1_PIN);

    if((gpioA & Encoder_PIN_0_PIN) == Encoder_PIN_0_PIN)
    {
        //Pin0上升沿
        if(!DL_GPIO_readPins(Encoder_PORT,Encoder_PIN_1_PIN))//P1为高电平
        {
            Front_Right_Count--;
        }
        else//P1为低电平
        {
            Front_Right_Count++;
        }
    }
    
    else if((gpioA & Encoder_PIN_1_PIN) == Encoder_PIN_1_PIN)
    {
        //Pin1上升沿
        if(!DL_GPIO_readPins(Encoder_PORT,Encoder_PIN_0_PIN))//P0为高电平
        {
            Front_Right_Count++;
        }
        else//P1为低电平
        {
            Front_Right_Count--;
        }
    }
    
    DL_GPIO_clearInterruptStatus(Encoder_PORT,  Encoder_PIN_0_PIN | Encoder_PIN_1_PIN);
		
		
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(Encoder_PORT,
    Encoder_PIN_2_PIN | Encoder_PIN_3_PIN);
		
		    if((gpioB & Encoder_PIN_2_PIN) == Encoder_PIN_2_PIN)
    {
        //Pin0上升沿
        if(!DL_GPIO_readPins(Encoder_PORT,Encoder_PIN_3_PIN))//P1为高电平
        {
            Front_Left_Count++;
        }
        else//P1为低电平
        {
            Front_Left_Count--;
        }
    }
    
    else if((gpioB & Encoder_PIN_3_PIN) == Encoder_PIN_3_PIN)
    {
        //Pin1上升沿
        if(!DL_GPIO_readPins(Encoder_PORT,Encoder_PIN_2_PIN))//P0为高电平
        {
            Front_Left_Count--;
        }
        else//P1为低电平
        {
            Front_Left_Count++;
        }
    }
    
    DL_GPIO_clearInterruptStatus(Encoder_PORT,  Encoder_PIN_2_PIN | Encoder_PIN_3_PIN);
}