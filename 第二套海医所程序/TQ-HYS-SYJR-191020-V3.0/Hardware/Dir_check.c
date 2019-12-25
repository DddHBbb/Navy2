#include "tm1638.h"

void Dir_GPIO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(Dir_check_APB|RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = Dir_check1_pin|Dir_check2_pin|Dir_check3_pin;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(Dir_check_port, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5

}
u8 Dir_value(void)
{
	u8 t,t1,t2,t3;
	t  = GPIO_ReadInputDataBit(Dir_check_port,Dir_check1_pin);
	t1 = GPIO_ReadInputDataBit(Dir_check_port,Dir_check2_pin);
	t2 = GPIO_ReadInputDataBit(Dir_check_port,Dir_check3_pin);
	t3 = (t<<2)|(t1<<1)|(t2);
	
	return  t3;
}

