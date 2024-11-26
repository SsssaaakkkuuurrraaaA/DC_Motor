#ifndef __BLDC_MOTOR_H
#define __BLDC_MOTOR_H

#include "stm32f4xx.h"

#include "Mathematics.h"

#include "Delay.h"

#define BLDC_MOTOR_PWM_ON		(0)
#define BLDC_MOTOR_ON_PWM		(0)
#define BLDC_MOTOR_H_ON_L_PWM	(0)
#define BLDC_MOTOR_H_PWM_L_PWM	(0)
#define BLDC_MOTOR_H_PWM_L_ON	(1)

#define BLDC_Motor_EN_GPIO      (GPIOF)
#define BLDC_Motor_EN_Pin       (GPIO_Pin_10)

#define BLDC_Encoder_U_GPIO     (GPIOH)
#define BLDC_Encoder_U_Pin      (GPIO_Pin_10)
#define BLDC_Encoder_V_GPIO     (GPIOH)
#define BLDC_Encoder_V_Pin      (GPIO_Pin_11)
#define BLDC_Encoder_W_GPIO     (GPIOH)
#define BLDC_Encoder_W_Pin      (GPIO_Pin_12)

#define BLDC_PWM_CH1_GPIO       (GPIOA)
#define BLDC_PWM_CH1_Pin        (GPIO_Pin_8)
#define BLDC_PWM_CH2_GPIO       (GPIOA)
#define BLDC_PWM_CH2_Pin        (GPIO_Pin_9)
#define BLDC_PWM_CH3_GPIO       (GPIOA)
#define BLDC_PWM_CH3_Pin        (GPIO_Pin_10)

#define BLDC_LOW_U_GPIO         (GPIOB)
#define BLDC_LOW_U_Pin          (GPIO_Pin_13)
#define BLDC_LOW_V_GPIO         (GPIOB)
#define BLDC_LOW_V_Pin          (GPIO_Pin_14)
#define BLDC_LOW_W_GPIO         (GPIOB)
#define BLDC_LOW_W_Pin          (GPIO_Pin_15)

typedef enum BLDC_State {
    BLDC_STOP = 0,
    BLDC_RUN = 1,
} BLDC_State;

typedef enum BLDC_Run_Direction {
    BLDC_FORWARD = 0,
    BLDC_BACKWARD = 1,
} BLDC_Run_Direction;

typedef struct BLDC_Parameter {
    int32_t PWM_Duty;
    BLDC_State BLDC_State;
    BLDC_Run_Direction BLDC_Direction;
    uint32_t Hall_Sensor_State;
} BLDC_Parameter;

extern BLDC_Parameter BLDC_parameter;

#define BLDC_PSC  (1)
#define BLDC_ARR  (10000)

void BLDC_Parameter_Init(void);

void BLDC_Encoder_Init(void);
uint32_t Get_BLDC_Encoder(void);

void BLDC_Motor_EN_GPIO_Init(void);

void BLDC_Motor_H_PWM_L_ON_GPIO_Init(void);
void BLDC_Motor_H_PWM_L_ON_TIM_Init(uint32_t ARR, uint32_t PSC);

void BLDC_Motor_Init(void);

void BLDC_Start(void);
void BLDC_Stop(void);

void BLDC_U_high_W_low(void);
void BLDC_U_high_V_low(void);
void BLDC_V_high_U_low(void);
void BLDC_V_high_W_low(void);
void BLDC_W_high_U_low(void);
void BLDC_W_high_V_low(void);

void BLDC_Motor_Set_PWM(int32_t PWM);

void BLDC_Motor_Control(void);

void TIM1_UP_IRQHandler(void);

#endif
