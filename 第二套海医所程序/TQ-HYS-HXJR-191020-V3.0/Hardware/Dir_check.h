#ifndef  _DIR_CHeck_H
#define  _DIR_CHeck_H

#include "stm32f10x.h"
#define  Dir_check_APB    RCC_APB2Periph_GPIOD
#define  Dir_check_port   GPIOD
#define  Dir_check3_pin   GPIO_Pin_9
#define  Dir_check2_pin   GPIO_Pin_8
#define  Dir_check1_pin   GPIO_Pin_15


u8 Dir_value(void); 
void Dir_GPIO_init(void);


#endif
