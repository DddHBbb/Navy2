#include "tm1638.h"
float ADC_ConvertedValueLocal[4];
int time_ge,time_shi,time_bai;
int show_time;
float Temp_Left_blow=0,Temp_Left_suck=0,Temp_Right_blow=0,Temp_Right_suck=0;
int Right_suck_Bai=0,Right_suck_Shi=0,Right_suck_Ge=0;

void TIM6_7_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7, ENABLE); //ʹ��TIM6ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	
	
	/*��������*/
	TIM_TimeBaseStructure.TIM_Period = 999;//����ֵ10000 ??
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;//Ԥ��Ƶ,��ֵ+1Ϊ��Ƶ�ĳ���
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	
	TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);//ʹ��TIM6�ж�
	TIM_ClearFlag(TIM6,TIM_IT_Update);
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM6, ENABLE); //ʹ�ܶ�ʱ��6
	
	TIM_TimeBaseStructure.TIM_Period = 9999;//����ֵ10000 ??
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;//Ԥ��Ƶ,��ֵ+1Ϊ��Ƶ�ĳ���
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	
	TIM_ITConfig(TIM7,TIM_IT_Update, ENABLE);//ʹ��TIM6�ж�
	TIM_ClearFlag(TIM7,TIM_IT_Update);
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM7, DISABLE); //ʹ�ܶ�ʱ��7
	
}
void TIM2_3_4_GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	// ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM2_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM2_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM2_CH1_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM2_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM2_CH2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM2_CH2_PORT, &GPIO_InitStructure);
	
	////////////////////////////////////////////////////////////////////////////
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM3_CH2_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM3_CH3_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH4_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH4_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM3_CH4_PORT, &GPIO_InitStructure);
	
	////////////////////////////////////////////////////////////////////////////
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM4_CH1_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM4_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM4_CH1_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(GENERAL_TIM4_CH2_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM4_CH2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM4_CH2_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM4_CH3_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM4_CH3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GENERAL_TIM4_CH3_PORT, &GPIO_InitStructure);
	
}
void TIM2_3_4_init(void)
{
	GENERAL_TIM2_APBxClock_FUN(GENERAL_TIM2_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM2_Period;	
	
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM2_Prescaler;	
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	
	TIM_TimeBaseInit(GENERAL_TIM2, &TIM_TimeBaseStructure);
	
	///////////////////////////////////////////////////////////////////////////////////////////	
	
	GENERAL_TIM3_APBxClock_FUN(GENERAL_TIM3_CLK,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM3_Period;	
	
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM3_Prescaler;	
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	
	TIM_TimeBaseInit(GENERAL_TIM3, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);//ʹ��TIM6�ж�
	TIM_ClearFlag(TIM3,TIM_IT_Update);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��6
	
	///////////////////////////////////////////////////////////////////////////////////////////
	
	GENERAL_TIM4_APBxClock_FUN(GENERAL_TIM4_CLK,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM4_Period;	
	
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM4_Prescaler;	
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	
	TIM_TimeBaseInit(GENERAL_TIM4, &TIM_TimeBaseStructure);
	
}
void TIM2_3_4_OCinit(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM2, ENABLE);
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 4
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM3, ENABLE);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(GENERAL_TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(GENERAL_TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	
	// ����Ƚ�ͨ�� 3
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(GENERAL_TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	
	// ʹ�ܼ�����
	TIM_Cmd(GENERAL_TIM4, ENABLE);
}
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�������2?
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM6_IRQn;//TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//ռ��ʽ���ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;//TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//ռ��ʽ���ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;//TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//ռ��ʽ���ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);//�жϳ�ʼ��
}
void TIM6_7_init1(void)
{
	TIM6_7_init();
	NVIC_Config();
	TIM2_3_4_GPIO_init();
	TIM2_3_4_init();
	TIM2_3_4_OCinit();
}
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//��������жϱ�־λ
		if((Record.key6_times == 1) && (Record.key5_times == 1))
		{
			__set_FAULTMASK(1); // �ر������ж�
			NVIC_SystemReset(); // ��λ				
		}
	}
}
extern float kk1;
void TIM6_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);//��������жϱ�־λ
		tran =  get_value();
		//tran =get_value_2();
		key_show();
		if(Record.key6_times == 1)
		{
			if(Record.set_temp <= 34)
			{
					kk1 = 0.5;
			}
			else  if((Record.set_temp > 34)&&(Record.set_temp <= 37))
			{
					kk1 = 1;
			}
			else if((Record.set_temp > 37)&&(Record.set_temp < 42))
			{
					kk1 = 1;
			}
			else if(Record.set_temp >= 42)
			{
					kk1 = 1;
			}
		}
	}
}
u8 Contorl_PWM_1=1,Contorl_PWM_2=0;
u8 End_Flag = 0,Time_Flag = 1,Start_Time=0;
void TIM7_IRQHandler(void)
{
static int t,t1;
if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
{	
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//��������жϱ�־λ
	t++;
	Start_Time++;
//	TIM2->CCR1 = PID_Opreation(12.5,1.2,1.1);
	if(Beep_Flag == 1)
	{
		t1++;
		if(t1<5)  
		{
			BEEP = !BEEP;
			Warning_Led = !Warning_Led;
			
		}
		else  
		{
			Beep_Flag = 0;
			BEEP = 0;
			t1 = 0;
		}
	}
	
	if(Time_Flag == 1)
	{
		if(t == 60)
		{
			t=0;
			time_ge--;
			if((time_ge < 0))
			{
				time_ge = 9;
				Record.time_shi_flag = 1;
			}
			if((time_shi == 0)&&(time_bai== 0)&&(time_ge== 0))
			{
				End_Flag = 1;
				Time_Flag = 0;
			}
		}
		if(Record.time_shi_flag == 1 )
		{
			Record.time_shi_flag = 0;
			time_shi--;
			if((time_shi < 0) && (time_bai != 0))
			{
				time_shi = 9;
				Record.time_bai_flag = 1;
			}
		}
		if(Record.time_bai_flag == 1)
		{
			Record.time_bai_flag = 0;
			time_bai--;
		}	
	}
}
}




