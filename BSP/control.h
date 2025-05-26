#ifndef __DRV_CXON_H
#define __DRV_CXON_H

#include "board.h"
#include "motor.h"
#include <math.h>
#define ecd_format(ecd)         \
    {                           \
        if ((ecd) > 180)  \
            (ecd) -= 360; \
        else if ((ecd) < -180)     \
            (ecd) += 360; \
    }
typedef struct
{
	float Left_Count ,Right_Count,Filtered_Left_Count,Filtered_Right_Count;
	float EncoderAll;
	float MotorEncoder_set[2];
	float pitch;
	float roll;
	float yaw;
	float CarSpeed;
	float CarAngleSet;//С���Ƕ�
	float XunXianMiddleSet;
	float SenorErro;
	pid_type_def Speed_pid[2];
	pid_type_def CarAnglePid;
	pid_type_def XunJiPid;
	pid_type_def posePid ;
	uint8_t mode;//����ģʽ�л�
	uint8_t running;//��������
}Car;
extern Car car;
void MainTask();
void systemInit();
int carDistance(float distance);
int carZizhuan(float target);
void Control();
void beepONTimeTask();
int Task4();
#endif