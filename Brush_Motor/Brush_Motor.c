#include "Brush_Motor.h"

void Brush_Motor_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Pin = Brush_Motor_EN_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(Brush_Motor_EN_GPIO, &GPIO_InitStruct);

    GPIO_WriteBit(Brush_Motor_EN_GPIO, Brush_Motor_EN_Pin, Bit_RESET);
}

void Brush_Motor_TIM_Init(uint16_t ARR, uint16_t PSC)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

    TIM_BDTRInitTypeDef TIM_BDTRInitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStruct.GPIO_Pin = Brush_Motor_PWM1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(Brush_Motor_PWM1_GPIO, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = Brush_Motor_PWM2_Pin;
    GPIO_Init(Brush_Motor_PWM2_GPIO, &GPIO_InitStruct);

    GPIO_PinAFConfig(Brush_Motor_PWM1_GPIO, Brush_Motor_PWM1_GPIO_PinSource, GPIO_AF_TIM1);
    GPIO_PinAFConfig(Brush_Motor_PWM2_GPIO, Brush_Motor_PWM2_GPIO_PinSource, GPIO_AF_TIM1);

    TIM_TimeBaseInitStruct.TIM_Prescaler = PSC - 1;
    TIM_TimeBaseInitStruct.TIM_Period = ARR - 1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OC1Init(TIM1, &TIM_OCInitStruct);

    TIM_BDTRInitStruct.TIM_DeadTime = 0x0F;
    TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_Low;
    TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStruct);
}

void Brush_Motor_Init(void)
{
    Brush_Motor_GPIO_Init();
    Brush_Motor_TIM_Init(8400, 0);
}

void Brush_Motor_Start(void)
{
    TIM_Cmd(TIM1, ENABLE);
    GPIO_WriteBit(Brush_Motor_EN_GPIO, Brush_Motor_EN_Pin, Bit_SET);
}

void Brush_Motor_Stop(void)
{
    TIM_Cmd(TIM1, DISABLE);
    GPIO_WriteBit(Brush_Motor_EN_GPIO, Brush_Motor_EN_Pin, Bit_RESET);
}

// Duty = CCR / ARR
void Brush_Motor_SetPWM(uint16_t Duty)
{
    uint16_t CCR_Value;

    if (Duty > 100)
    {
        TIM_SetCompare1(TIM1, TIM1->ARR); 
    }

    else if(Duty > 0 && Duty <= 100)
    {
        CCR_Value = Duty * (uint16_t)TIM1->ARR;
        TIM_SetCompare1(TIM1, CCR_Value); 
    }

    else
    {
        TIM_SetCompare1(TIM1, 0);
    }
}

void Brush_Motor_Dir(Brush_Moror_Direction Direction)
{
    TIM_CCxCmd(TIM1, TIM_Channel_1, DISABLE);
    TIM_CCxNCmd(TIM1, TIM_Channel_1, DISABLE);

    if(Direction == Brush_Motor_Dir_Forward)
    {
        TIM_CCxCmd(TIM1, TIM_Channel_1, ENABLE);
    }

    else
    {
        TIM_CCxNCmd(TIM1, TIM_Channel_1, ENABLE);
    }
}
