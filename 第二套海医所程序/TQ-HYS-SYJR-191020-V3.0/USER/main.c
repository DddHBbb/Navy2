#include "tm1638.h"
u8 Flag = 0;
float kk,kk1;
int main(void)
{		
	IO_init();
	IWDG_Init(4,220);
	delay_init();
	uart_init(115200);	
	max31865_init();
	//max31865_init_2();
	TM1638_init();
  TIM6_7_init1();
	LED1_ON();
	Beep_ON();
	delay_ms(200);
	Beep_OFF();
while(1)
{	
	key_times();	
	delay_ms(80);
	kk = tran - kk1;
	Right_suck_Bai = kk*10/100;
	Right_suck_Shi = (int)(kk*10/10)%10;
	Right_suck_Ge  = (int)(kk*10)%10;
	printf("\r\n ÎÂ¶È = %f ¡æ  ÕæÊµ = %f ¡æ\r\n",kk,tran);	   
	
	printf("\n\r");
//	printf("\r\n pid = %d ¡æ \r\n",TIM2->CCR1);	   
//	printf("\n\r");
	
//if((Record.key4_times == 0) && (Flag == 0))
//	{
//		T_show(Right_suck_Bai,Right_suck_Shi,Right_suck_Ge);		
//	}		
if(Record.key6_times == 1)
	{		
		LED3_ON();	
		TIM_Cmd(TIM7,ENABLE);
		if(Start_Time == 2)
			{
				Start_Time=0;
				TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Right_suck_Bai,Right_suck_Shi,Right_suck_Ge,time_bai,time_shi,time_ge);
			}
		if((tran - kk1)>= Record.set_temp) 
			{
				Transfuse_PWM7 =0;
			}
		else
			{
				Transfuse_PWM7 =100;
			}
	}
if(End_Flag == 1)
	{
		Beep_Flag = 1;
	}
IWDG_Feed();
}	
} 


