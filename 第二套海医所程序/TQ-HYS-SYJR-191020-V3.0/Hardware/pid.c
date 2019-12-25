#include "pid.h"
#include "tm1638.h"
spid PID = {0};

float PID_Calculate(spid *vPID,float Samp_Val)
{
   int DEk = 0;  //΢��ƫ�ȡ���,�����Ǳ��ر���
	vPID->Ek = Record.set_temp - Samp_Val;   //Ekƫ��
//	if(Record.set_temp - Samp_Val > 0)				
//	{
//		vPID->Error_SumP += vPID->Ek;    //������ƫ�� 
//		vPID->Flag_Symbol = 0;           //0Ϊ+
//	}
//	else
//	{
//		vPID->Error_SumN += vPID->Ek;   //������ƫ��
//		vPID->Flag_Symbol = 1;          //1Ϊ-
//	}
//	vPID->Error_Sum = vPID->Error_SumP - vPID->Error_SumN;  //��ͣ�����֣���ʵ����ֱ�Ӽӣ�����������
//	else if(vPID->Error_SumP >= (2^30))  vPID->Error_SumP = 0;   //�����
//	else if(vPID->Error_SumN >= (2^30))  vPID->Error_SumN = 0;  //���������ô�Ѿ�����Ϊ���ܻῴ���������ֵ
	vPID->Error_Sum += vPID->Ek;
	if(vPID->Error_Sum >= 180)  			vPID->Error_Sum = 100;   //�Ϸⶥֵ
	else if(vPID->Error_Sum < -180)  vPID->Error_Sum = -100;   //�·ⶥֵ
	DEk = vPID->Last_ErrorVal - vPID->Pre_ErrorVal;              //΢��ƫ��
	vPID->Pre_ErrorVal = vPID->Last_ErrorVal;                   //���������ʼ�����ƣ���һ�̻��Ϊ��һ��,��һ�̻��Ϊ����һ��
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
















