#include "pid.h"
#include "tm1638.h"
spid PID = {0};

float PID_Calculate(spid *vPID,float Samp_Val)
{
   int DEk = 0;  //微分偏差，取最近,所以是本地变量
	vPID->Ek = Record.set_temp - Samp_Val;   //Ek偏差
//	if(Record.set_temp - Samp_Val > 0)				
//	{
//		vPID->Error_SumP += vPID->Ek;    //正数项偏差 
//		vPID->Flag_Symbol = 0;           //0为+
//	}
//	else
//	{
//		vPID->Error_SumN += vPID->Ek;   //负数项偏差
//		vPID->Flag_Symbol = 1;          //1为-
//	}
//	vPID->Error_Sum = vPID->Error_SumP - vPID->Error_SumN;  //求和，求积分，其实可以直接加，忽略正负项
//	else if(vPID->Error_SumP >= (2^30))  vPID->Error_SumP = 0;   //防溢出
//	else if(vPID->Error_SumN >= (2^30))  vPID->Error_SumN = 0;  //防溢出，这么费劲是因为可能会看正、负向的值
	vPID->Error_Sum += vPID->Ek;
	if(vPID->Error_Sum >= 180)  			vPID->Error_Sum = 100;   //上封顶值
	else if(vPID->Error_Sum < -180)  vPID->Error_Sum = -100;   //下封顶值
	DEk = vPID->Last_ErrorVal - vPID->Pre_ErrorVal;              //微分偏差
	vPID->Pre_ErrorVal = vPID->Last_ErrorVal;                   //想象此序列始终右移，这一刻会变为上一刻,上一刻会变为上上一刻
	vPID->Last_ErrorVal = vPID->Ek;
	
	return ((vPID->Kp * (vPID->Ek))
				 +(vPID->Ki * (vPID->Error_Sum))
				 +(vPID->Kd * (DEk)));	
}
unsigned int PID_Opreation(float kp,float ki,float kd)
{
 unsigned int Val=0;
 PID.Kp = kp;
 PID.Ki = ki;
 PID.Kd = kd;
 Val = PID_Calculate(&PID,tran);
return Val;
}
















