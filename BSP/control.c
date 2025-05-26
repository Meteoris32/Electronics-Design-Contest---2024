#include "control.h"

Car car;
extern Key key[3];
uint16_t Servo1Init,Servo2Init;
float MotorPID[3]={40,4,0};
float XunJiPID[3]={13,0,13};
fp32 CarAnglePID[3]={0.2,0,0.5};
fp32 PosePID[3]={0.8,0.001,0};
float TargetEncoder=0;
float angleOutPut,XunJiOutPut,PosetionOutPut;
uint8_t XunjiFlag,poseFlag,angleFlag,beepFlag;
extern int32_t Front_Left_Count , Front_Right_Count ;
float encoderSet;//里程计目标值
extern uint8_t NOLineFlag;
void systemInit()
{
	//编码器pid初始化
	for(int i=0;i<2;i++)
		PID_init(&car.Speed_pid[i],PID_POSITION,MotorPID,2000,500);
	//循迹pid 
	PID_init(&car.XunJiPid,PID_POSITION,XunJiPID,40,10);
		//角度闭环初始化
	PID_init(&car.CarAnglePid,PID_POSITION_ANGLE,CarAnglePID,15,4);	
		//位置编码
	PID_init(&car.posePid,PID_POSITION,PosePID,30,10);	
	car.mode=1;
	car.XunXianMiddleSet=0;
}
uint8_t taskflag;
void Control()
{

	clickKey();
	if (key[0].singleFlag==1)
	{
			key[0].singleFlag=0;
//		XunjiFlag=1;
//		TargetEncoder=25;
//		car.running=1;
		taskflag=1;
	}
	if(key[1].singleFlag==1)
	{
	key[1].singleFlag=0;
		car.mode++;
		if(car.mode>4)car.mode=1;
	}
			GetPerEncoder();
			MainTask();
		//循迹pid
			if(XunjiFlag)
					XunJiOutPut=PID_calc(&car.XunJiPid,car.SenorErro,car.XunXianMiddleSet);
			else
					XunJiOutPut=0;
		//角度pid
			if(angleFlag)
			{
				ecd_format(car.CarAngleSet);
				angleOutPut=PID_calc(&car.CarAnglePid,car.yaw,car.CarAngleSet);
			}
			else
				angleOutPut=0;
				//编码pid
			if(poseFlag)
			{
				PosetionOutPut=PID_calc(&car.posePid,car.EncoderAll,encoderSet);
			}
			else
				PosetionOutPut=0;
				//角度环
			car.MotorEncoder_set[0]=TargetEncoder+XunJiOutPut-angleOutPut+PosetionOutPut;
			car.MotorEncoder_set[1]=TargetEncoder-XunJiOutPut+angleOutPut+PosetionOutPut;
			
			car.Speed_pid[0].out=PID_calc(&car.Speed_pid[0],car.Left_Count,car.MotorEncoder_set[0]);
			car.Speed_pid[1].out=PID_calc(&car.Speed_pid[1],car.Right_Count,car.MotorEncoder_set[1]);
	
				if(car.running==1)
				{
				MotorSet(car.Speed_pid[0].out,car.Speed_pid[1].out,Servo1Init,Servo2Init);
				}
				else{
				MotorSet(0,0,Servo1Init,Servo2Init);
				}
}
void beepONTimeTask()
{
			static uint8_t i;
	if(beepFlag==1)
	{

		if(++i<60)
			DL_GPIO_setPins(BEEP_PORT,BEEP_beep_PIN);
		else
		{
			i=0;
			beepFlag=0;
				DL_GPIO_clearPins(BEEP_PORT,BEEP_beep_PIN);
		}
	}
	else
	{
		i=0;
		DL_GPIO_clearPins(BEEP_PORT,BEEP_beep_PIN);
	}
}
int  Task1()
{
		static uint8_t state,i;
		static float tempAngle,tempPose;
		switch(state)
		{
			case 0:
				if(++i>10)
				{
					i=0;
					tempPose=car.EncoderAll;
					encoderSet=tempPose+3400;
					tempAngle=car.yaw;
					car.CarAngleSet=tempAngle;
					state++;
				}
				break;
			case 1:
						car.running=1;
//								TargetEncoder=25;
						poseFlag=1;
						angleFlag=1;
				//有黑线
				if(NOLineFlag==0)
				{
					angleFlag=0;
					poseFlag=0;
					car.running=0;
					beepFlag=1;
					state++;
				}
				break;
			case 2:
				state=0;
				return 1;
				break;
		}
		return 0;
}
int  Task2()
{
	static uint8_t state,i;
		static float tempAngle,tempPose;
		switch(state)
		{
			case 0:
				if(++i>10)
				{
					i=0;
//					tempPose=car.EncoderAll;
//					encoderSet=tempPose+3400;
					tempAngle=car.yaw;
					car.CarAngleSet=tempAngle;

				//
					state++;
				}
				break;
			case 1:
						car.running=1;
//						poseFlag=1;
					TargetEncoder=25;
						angleFlag=1;
				//有黑线
				if(NOLineFlag==0)
				{
					angleFlag=0;
					poseFlag=0;
					XunjiFlag=1;
					TargetEncoder=20;
					beepFlag=1;
					state++;
				}
				break;
			case 2:
				//没线
					if(NOLineFlag==1)
				{
					angleFlag=1;
					poseFlag=0;
					XunjiFlag=0;
					TargetEncoder=25;
					beepFlag=1;
//					tempAngle=car.yaw;
					car.CarAngleSet=tempAngle+180;
					state++;
				}
				break;
			case 3:
				//有线
				if(NOLineFlag==0)
				{
					angleFlag=0;
					poseFlag=0;
					XunjiFlag=1;
					beepFlag=1;
					TargetEncoder=25;
					state++;
				}
				break;
			case 4:
				//没线
				if(NOLineFlag==1)
				{	
					TargetEncoder=0;
					angleFlag=0;
					poseFlag=0;
					XunjiFlag=0;
					beepFlag=1;
					car.running=0;
					state++;
				}
				break;
			case 5:
				state=0;
				return 1;
				break;
		}
		return 0;
}
float angle;
uint8_t flag_for_task4 = 1;//标志位，用于区别任务4中的第一与，二，三，四圈 第一圈时标志位为1
int  Task3()
{
		static uint16_t state,i;
		static float tempAngle,tempPose;
		static uint16_t time = 0;

		switch(state)
		{
			case 0:
				if(++i>10)
				{
					i=0;
					tempAngle=car.yaw;
						
					if (flag_for_task4)
					{
						angle=tempAngle;
					}
          car.CarAngleSet=angle-42.8;					
					state++;
				}
				
				break;
			case 1:
				car.running=1;
				angleFlag=1;
				TargetEncoder=34;
			  i++;
			  if (i > 100)  //前1s不要识别黑线
				{
					if(i > 170)//1.5s即将到达减速
					{
							TargetEncoder=18;
					}
					if(NOLineFlag==0)//有线
					{
						poseFlag=0;
						XunjiFlag=1;
						beepFlag=1;
						state++;
						i = 0;
					}					
				}
	
				break;
			case 2://转向步奏
				TargetEncoder=0;
				if(++i>20)
				{
					i=0;
					angleFlag=0;
					state++;
				}
				break;
			
			case 3:
				TargetEncoder=34;
				if(NOLineFlag==1)//无线
				{
					car.running=1;

//					tempAngle=car.yaw;
					car.CarAngleSet=angle+32.8+180;
					angleFlag=1; //打开角度换关闭循迹
					XunjiFlag=0;				
					TargetEncoder=34;
					beepFlag=1;
					state++;
				}
				break;
			case 4:
					if(++i>170)
					{
							TargetEncoder=20;
					}
				if(NOLineFlag==0)//有线
				{
					i=0;
					XunjiFlag=1;
					angleFlag=0;	
					beepFlag=1;
					state++;
				}
				break;
			case 5:
						if (++time > 200)
					{

						if(NOLineFlag==1)//无线
						{
							time=0;
							XunjiFlag=0;
							angleFlag=0;
							car.running=0;		
							beepFlag=1;	
							state++;
						}
					}

				break;
			case 6:
				state=0;
			return 1;
			break;
		}
	return 0;
}

int Task4()
{
	static uint8_t temp;
  if(temp == 4)
	{
		  temp = 0;
			XunjiFlag=0;
			angleFlag=0;
			car.running=0;	
		  return 1;
	}
	else 
	{
		temp += Task3();
		if (temp >= 1)
		{
			flag_for_task4 = 0;
		}
		return 0;
	}
	
}

void MainTask()
{
	//角度换 编码器 巡线
	if(taskflag==1)
	{
		if(car.mode==1)
		{
			if(Task1()==1) //任务完成
			{
				taskflag=0;
			}
		}
		else if(car.mode==2)
		{
				if(Task2()==1) //任务完成
			{
				taskflag=0;
			}
		}
		else if(car.mode==3)
		{
				if(Task3()==1) //任务完成
			{
				taskflag=0;
			}
		
		}
		else if (car.mode == 4)
		{
			  if (Task4() == 1)
				{
					taskflag=0;					
				}
		}
	}
}