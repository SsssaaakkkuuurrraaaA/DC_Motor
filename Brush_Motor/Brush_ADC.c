#include "Brush_ADC.h"

uint16_t Brush_Motor_ADC_Voltage_Value[1000];
uint16_t Brush_Motor_ADC_Voltage_Average_Value;

uint16_t Brush_Motor_ADC_Current_Value[1000];
uint16_t Brush_Motor_ADC_Current_Average_Value;
uint16_t Brush_Motor_ADC_CurrentValue;

uint16_t Brush_Motor_ADC_Temperature_Value[1000];
uint16_t Brush_Motor_ADC_Temperature_Average_Value;

void Brush_Motor_Voltage_ADC_DMA_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_480Cycles);
    ADC_Cmd(ADC1, ENABLE);

    DMA_DeInit(DMA2_Stream4);
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Brush_Motor_ADC_Voltage_Value; 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 1000; 
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_Init(DMA2_Stream4, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream4, ENABLE);

    ADC_DMACmd(ADC1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

    ADC_SoftwareStartConv(ADC1);
}

void Calculate_Brush_Motor_ADC_Voltage_Average_Value(uint16_t *Address)
{
    uint32_t temp = 0;

    int i;
    
    for(i = 0; i < 1000; i++)         
    {
        temp += Brush_Motor_ADC_Voltage_Value[i];
    }
    temp /= 1000;                

    Address[0] = temp;       
}

void Calculate_Brush_Motor_ADC_Voltage_Value(void)
{

}

void Brush_Motor_Current_ADC_DMA_Init(void)
{

}

void Calculate_Brush_Motor_ADC_Current_Average_Value(uint16_t *Address)
{
    uint32_t temp = 0;

    int i;

    for(i = 0; i < 1000; i++)     
    {
        temp += Brush_Motor_ADC_Current_Value[i];
    }
    temp /= 1000;             

    Address[0] = temp;
}

void Calculate_Brush_Motor_ADC_Current_Value(void)
{

}

void Brush_Motor_Temperature_ADC_DMA_Init(void)
{

}

void Calculate_Brush_Motor_ADC_Temperature_Average_Value(uint16_t *Address)
{
    uint32_t temp = 0;

    int i;

    for(i = 0; i < 1000; i++)     
    {
        temp += Brush_Motor_ADC_Temperature_Value[i];
    }
    temp /= 1000;             

    Address[0] = temp;
}

void Calculate_Brush_Motor_ADC_Temperature_Value(void)
{

}
