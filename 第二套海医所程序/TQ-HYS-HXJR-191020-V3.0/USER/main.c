#include "tm1638.h"
#define  water   0
#define  air     1

u8 FakeT_Flag=0,FakeT_Flag1=0,Flag=1,BJ=0,One_Show=0;
float FakeT_Left_suck=0,Fake_Bai=0,Fake_Shi=0,Fake_Ge=0;
int main(void)
{		
	  ADCx_Init();
	  IO_init();
//	IWDG_Init(4,3125);
	  delay_init();
	  uart_init(115200);	
	  Dir_GPIO_init();
	  TM1638_init();
    TIM6_7_init1();
	  LED1_ON();
		Beep_ON();
   	delay_ms(200);
	  Beep_OFF();
	  
while(1)
{	
	key_times();	
	delay_ms(100);
  Temp_water  =  ADC_ConvertedValueLocal[water];	
	Right_suck_Bai = Temp_Right_suck*10/100;
	Right_suck_Shi = (int)(Temp_Right_suck*10/10)%10;
	Right_suck_Ge  = (int)(Temp_Right_suck*10)%10;
	printf("\r\n 水温度 = %f V \r\n",Temp_water);		   //Left_blow    3     
	printf("\n\r");
	printf("\r\n 空气温度 = %f ℃ \r\n",Temp_Right_suck);     //Right_suck   1 
	printf("\n\r");
	printf("\r\n 角度= %d ℃ \r\n",Dir_value());
	printf("\n\r");

if(Record.key6_times == 1)
	{		
		LED3_ON();
		TIM_Cmd(TIM7,ENABLE);	
		if(Flag == 1)
		{
			Warm_air(10);  //34°   开10  十分钟
			Flag = 0;
		}
		if(Temp_water < 1.2)  Warm_water(0);
		else                  Warm_water(30);		
		if((Start_Time == 2) && (FakeT_Flag == 0))
		{
			Start_Time=0;
			if((One_Show == 0) && (Right_suck_Bai != 0))
			{
				TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Right_suck_Bai,Right_suck_Shi,Right_suck_Ge,time_bai,time_shi,time_ge);		
			}	
			else if((Temp_Right_suck < Record.set_temp + 1) && (Temp_Right_suck > Record.set_temp - 1))
			{
				TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Right_suck_Bai,Right_suck_Shi,Right_suck_Ge,time_bai,time_shi,time_ge);
			}
			printf("1\n"); 
			delay_ms(1);	
		}
	}
if(((Temp_Right_suck + 1) >= Record.set_temp) && (Record.key6_times == 1)&& (BJ == 0))
	{			
		BJ = 1;
		One_Show = 1;	
		FakeT_Flag1 =1;	
		Samp_Flag = 0;				
		printf("2\n"); 
	}
if(FakeT_Flag1 == 1)
	{
	if((Temp_Right_suck < Record.set_temp + 1) && (Temp_Right_suck > Record.set_temp - 1))
		{
		 FakeT_Left_suck = Temp_Right_suck;
		}	
		Warm_air(0);
    FakeT_Flag = 1;	
		Samp_Flag = 1;
	  Fake_Bai = FakeT_Left_suck*10/100;
	  Fake_Shi = (int)(FakeT_Left_suck*10/10)%10;
	  Fake_Ge  = (int)(FakeT_Left_suck*10)%10;
	if(Fake_Bai != 0)
		{
			TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Fake_Bai,Fake_Shi,Fake_Ge,time_bai,time_shi,time_ge);
		}				
		printf("3\n"); 
		delay_ms(1);
	if((Temp_Right_suck < Record.set_temp - 1)&&(Temp_Right_suck > Record.set_temp - 10))
		{
			FakeT_Flag  = 0;
			FakeT_Flag1 = 0;
			Samp_Flag = 0;
			Samp_time = 0;	
			Warm_air(10);	
			shu = 0;						
			BJ = 0;
			printf("4\n");
			delay_ms(1);					
		}
	}
while(Temp_Right_suck > 48) 
{
	while(1)
	{
		TIM_Cmd(TIM6,DISABLE);
		key_times();
		Beep_Flag = 1;
		Warm_air(0);
		Warm_water(0);
		BEEP = !BEEP;
		Warning_Led = !Warning_Led;
		delay_ms(150);
		TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Right_suck_Bai,Right_suck_Shi,Right_suck_Ge,time_bai,time_shi,time_ge);		
	}
}
while(End_Flag == 1)   
	{	
		key_times();
		delay_ms(100);
//		Temp_water  =  ADC_ConvertedValueLocal[water];	
//		Right_suck_Bai = Temp_Right_suck*10/100;
//		Right_suck_Shi = (int)(Temp_Right_suck*10/10)%10;
//		Right_suck_Ge  = (int)(Temp_Right_suck*10)%10;
		Beep_ON();
		Warning_Led = 1;
		TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Fake_Bai,Fake_Shi,Fake_Ge,0,0,0);
	}
} 

}
