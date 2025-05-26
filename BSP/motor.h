#ifndef __motor_H
#define __motor_H 

#include "board.h"
#include "stdlib.h"	
#include "control.h"	
void MotorSet(int motor_a,int motor_b,uint16_t servo1,uint16_t servo2);
void GetPerEncoder();
#endif