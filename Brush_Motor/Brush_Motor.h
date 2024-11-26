#ifndef __BRUSH_MOTOR_H
#define __BRUSH_MOTOR_H

#include "stm32f4xx.h"

#include "Mathematics.h"

#include "Delay.h"

#define Brush_Motor_EN_GPIO	                (GPIOF)
#define Brush_Motor_EN_Pin		            (GPIO_Pin_10)

#define Brush_Motor_PWM1_GPIO	            (GPIOA)
#define Brush_Motor_PWM1_Pin		        (GPIO_Pin_8)
#define Brush_Motor_PWM1_GPIO_PinSource     (GPIO_PinSource8)

#define Brush_Motor_PWM2_GPIO	            (GPIOB)
#define Brush_Motor_PWM2_Pin		        (GPIO_Pin_13)
#define Brush_Motor_PWM2_GPIO_PinSource     (GPIO_PinSource13)

typedef enum Brush_Moror_Direction {
    Brush_Motor_Dir_Forward = 0,
    Brush_Motor_Dir_Backward = 1,
} Brush_Moror_Direction;

void Brush_Motor_GPIO_Init(void);
void Brush_Motor_TIM_Init(uint16_t ARR, uint16_t PSC);
void Brush_Motor_Init(void);

void Brush_Motor_Start(void);
void Brush_Motor_Stop(void);
void Brush_Motor_SetPWM(uint16_t Duty);
void Brush_Motor_Dir(Brush_Moror_Direction Direction);

#endif
