#include "BLDC_Motor.h"

#if (BLDC_MOTOR_H_PWM_L_ON)

BLDC_Parameter BLDC_parameter;

void BLDC_Parameter_Init(void)
{
    BLDC_parameter.BLDC_Direction = BLDC_FORWARD;
    BLDC_parameter.PWM_Duty = 0;
    BLDC_parameter.BLDC_State = BLDC_STOP;
    BLDC_parameter.Hall_Sensor_State = 0;
}

void BLDC_Encoder_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

    GPIO_InitStructure.GPIO_Pin = BLDC_Encoder_U_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BLDC_Encoder_U_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_Encoder_V_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BLDC_Encoder_V_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_Encoder_W_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BLDC_Encoder_W_GPIO, &GPIO_InitStructure);
}

uint32_t Get_BLDC_Encoder(void)
{
    uint32_t State;

    if(GPIO_ReadInputDataBit(BLDC_Encoder_U_GPIO, BLDC_Encoder_U_Pin) == 1)
    {
        State |= 0x01;
    }

    if(GPIO_ReadInputDataBit(BLDC_Encoder_V_GPIO, BLDC_Encoder_V_Pin) == 1)
    {
        State |= 0x02;
    }

    if(GPIO_ReadInputDataBit(BLDC_Encoder_W_GPIO, BLDC_Encoder_W_Pin) == 1)
    {
        State |= 0x04;
    }

    return State;
}

void BLDC_Motor_EN_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_InitStructure.GPIO_Pin = BLDC_Motor_EN_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_Motor_EN_GPIO, &GPIO_InitStructure);
}

void BLDC_Motor_H_PWM_L_ON_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = BLDC_LOW_U_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_LOW_U_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_LOW_V_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_LOW_V_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_LOW_W_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_LOW_W_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_PWM_CH1_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_PWM_CH1_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_PWM_CH2_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_PWM_CH2_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BLDC_PWM_CH3_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(BLDC_PWM_CH3_GPIO, &GPIO_InitStructure);  
}

void BLDC_Motor_H_PWM_L_ON_TIM_Init(uint32_t ARR, uint32_t PSC)
{
    NVIC_InitTypeDef NVIC_InitStructure;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = ARR - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = PSC - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_Cmd(TIM1, ENABLE);        
    
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void BLDC_Motor_Init(void)
{
	BLDC_Motor_EN_GPIO_Init();

    BLDC_Motor_H_PWM_L_ON_GPIO_Init();
    BLDC_Motor_H_PWM_L_ON_TIM_Init(BLDC_ARR, BLDC_PSC);

    BLDC_Parameter_Init();

    BLDC_Encoder_Init();
}

void BLDC_Start(void)
{
    GPIO_WriteBit(BLDC_Motor_EN_GPIO, BLDC_Motor_EN_Pin, Bit_SET);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    BLDC_parameter.BLDC_State = BLDC_RUN;
}

void BLDC_Stop(void)
{
    GPIO_WriteBit(BLDC_Motor_EN_GPIO, BLDC_Motor_EN_Pin, Bit_RESET);

    TIM_CtrlPWMOutputs(TIM1, DISABLE);

    TIM_SetCompare1(TIM1, 0);
    TIM_SetCompare2(TIM1, 0);
    TIM_SetCompare3(TIM1, 0);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_RESET);

    BLDC_parameter.BLDC_State = BLDC_STOP;
}

void BLDC_U_high_W_low(void)
{
    TIM_SetCompare1(TIM1, BLDC_parameter.PWM_Duty);
    TIM_SetCompare2(TIM1, 0);
    TIM_SetCompare3(TIM1, 0);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_SET);
}

void BLDC_U_high_V_low(void)
{
    TIM_SetCompare1(TIM1, BLDC_parameter.PWM_Duty);
    TIM_SetCompare2(TIM1, 0);
    TIM_SetCompare3(TIM1, 0);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_SET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_RESET);
}

void BLDC_V_high_U_low(void)
{
    TIM_SetCompare1(TIM1, 0);
    TIM_SetCompare2(TIM1, BLDC_parameter.PWM_Duty);
    TIM_SetCompare3(TIM1, 0);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_SET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_RESET);
}

void BLDC_V_high_W_low(void)
{
    TIM_SetCompare1(TIM1, 0);
    TIM_SetCompare2(TIM1, BLDC_parameter.PWM_Duty);
    TIM_SetCompare3(TIM1, 0);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_SET);
}

void BLDC_W_high_U_low(void)
{
    TIM_SetCompare1(TIM1, 0);
    TIM_SetCompare2(TIM1, 0);
    TIM_SetCompare3(TIM1, BLDC_parameter.PWM_Duty);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_SET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_RESET);
}

void BLDC_W_high_V_low(void)
{
    TIM_SetCompare1(TIM1, 0);
    TIM_SetCompare2(TIM1, 0);
    TIM_SetCompare3(TIM1, BLDC_parameter.PWM_Duty);

    GPIO_WriteBit(BLDC_LOW_U_GPIO, BLDC_LOW_U_Pin, Bit_RESET);
    GPIO_WriteBit(BLDC_LOW_V_GPIO, BLDC_LOW_V_Pin, Bit_SET);
    GPIO_WriteBit(BLDC_LOW_W_GPIO, BLDC_LOW_W_Pin, Bit_RESET);
}

void BLDC_Motor_Set_PWM(int32_t PWM)
{
    if(PWM > BLDC_ARR)
    {
        PWM = BLDC_ARR;
    }

    if (PWM < 0)
    {
        PWM = 0;
    }
    
    BLDC_parameter.PWM_Duty = PWM;
}

void BLDC_Motor_Control(void)
{
    if(BLDC_parameter.BLDC_State == BLDC_RUN)
    {
        BLDC_Start();

        BLDC_parameter.Hall_Sensor_State = Get_BLDC_Encoder();

        if(BLDC_parameter.BLDC_Direction == BLDC_FORWARD)
        {
            switch(BLDC_parameter.Hall_Sensor_State)
            {
                case 0x01: 
                {
                    BLDC_U_high_W_low();
                    break;
                }
                case 0x02:
                {
                    BLDC_V_high_U_low();
                    break;
                }
                case 0x03:
                {
                    BLDC_V_high_W_low();
                    break;
                }
                case 0x04:
                {
                    BLDC_W_high_V_low();
                    break;
                }
                case 0x05:
                {
                    BLDC_U_high_V_low();
                    break;
                }
                case 0x06:
                {
                    BLDC_W_high_U_low();
                    break;
                }
            }
        }
        else
        {
            switch(BLDC_parameter.Hall_Sensor_State)
            {
                case 0x01:
                {
                    BLDC_W_high_U_low();
                    break;
                }
                case 0x02:
                {
                    BLDC_U_high_V_low();
                    break;
                }
                case 0x03:
                {
                    BLDC_W_high_V_low();
                    break;
                }
                case 0x04:
                {
                    BLDC_V_high_W_low();
                    break;
                }
                case 0x05:
                {
                    BLDC_V_high_U_low();
                    break;
                }
                case 0x06:
                {
                    BLDC_U_high_W_low();
                    break;
                }
            }
        }
    }
    else
    {
        BLDC_Stop();
    }
}

void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
        BLDC_Motor_Control();
        
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

#endif

#if (BLDC_MOTOR_PWM_ON)
#endif
#if (BLDC_MOTOR_ON_PWM)
#endif
#if (BLDC_MOTOR_H_ON_L_PWM)
#endif
#if (BLDC_MOTOR_H_PWM_L_PWM)
#endif
