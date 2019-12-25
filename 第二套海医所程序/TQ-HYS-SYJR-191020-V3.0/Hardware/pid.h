#ifndef _PID__H
#define _PID__H

#include "stm32f10x.h"

typedef struct tt 
{
	float Error_SumP;
	float Error_SumN;
	float Error_Sum;
	float Ek;
	u8  Flag_Symbol;
	float  Kp;
	float  Ki;
	float  Kd;
	float Current_ErrorVal;
	float Last_ErrorVal;
	float Pre_ErrorVal;
}spid;

float PID_Calculate(spid *vPID,float Samp_Val);
unsigned int PID_Opreation(float kp,float ki,float kd);
#endif

















