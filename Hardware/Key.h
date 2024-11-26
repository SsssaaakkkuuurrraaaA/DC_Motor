#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

#include "Mathematics.h"

#include "Delay.h"

#include "DataStructure.h"

#define Key0_GPIO	(GPIOE)
#define Key1_GPIO	(GPIOE)
#define Key2_GPIO	(GPIOE)

#define Key0_Pin	(GPIO_Pin_2)
#define Key1_Pin	(GPIO_Pin_3)
#define Key2_Pin	(GPIO_Pin_4)

typedef enum Key_Pin {
	KEY_NONE = 0,
    
	KEY0 = 1,
	KEY1 = 2,
	KEY2 = 3,
} Key_Pin;

extern Key_Pin Key_Value;

void Key_GPIO_Init(void);
void Key_TIM_Init(void);
void Key_Init(void);

void Key_Scan(void);

void TIM3_IRQHandler(void);

#endif
