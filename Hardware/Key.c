#include "Key.h"

Queue Key_Queue;

Key_Pin Key_Value = KEY_NONE;

void Key_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = Key0_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(Key0_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = Key1_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(Key1_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = Key2_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(Key2_GPIO, &GPIO_InitStructure);
}

void Key_TIM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 8400 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE);
}

void Key_Init(void)
{
    Key_GPIO_Init();
    Key_TIM_Init();

    QueueCreate(&Key_Queue);
}

void Key_Scan(void)
{
    Key_Pin Key_Value = KEY_NONE;

    if (GPIO_ReadInputDataBit(Key0_GPIO, Key0_Pin) == 0)
    {
        Key_Value = KEY0;
            
        QueuePush(&Key_Queue, Key_Value);
    }

    if (GPIO_ReadInputDataBit(Key1_GPIO, Key1_Pin) == 0)
    {
        Key_Value = KEY1;

        QueuePush(&Key_Queue, Key_Value);
    }

    if (GPIO_ReadInputDataBit(Key2_GPIO, Key2_Pin) == 0)
    {
        Key_Value = KEY2;

        QueuePush(&Key_Queue, Key_Value);
    }

    Delay_ms(100);
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update)!= RESET)
    {
        Key_Scan();

        if(QueueSize(&Key_Queue) != 0)
        {
            Key_Value = (Key_Pin)QueueTail(&Key_Queue);
            
            QueuePop(&Key_Queue);
        }

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
