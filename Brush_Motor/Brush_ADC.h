#ifndef __BRUSH_ADC_H
#define __BRUSH_ADC_H

#include "stm32f4xx.h"

#include "Mathematics.h"

#include "Delay.h"

void Brush_Motor_Voltage_ADC_DMA_Init(void);
void Calculate_Brush_Motor_ADC_Voltage_Average_Value(uint16_t *Address);
void Calculate_Brush_Motor_ADC_Voltage_Value(void);

void Brush_Motor_Current_ADC_DMA_Init(void);
void Calculate_Brush_Motor_ADC_Current_Average_Value(uint16_t *Address);
void Calculate_Brush_Motor_ADC_Current_Value(void);

void Brush_Motor_Temperature_ADC_DMA_Init(void);
void Calculate_Brush_Motor_ADC_Temperature_Average_Value(uint16_t *Address);
void Calculate_Brush_Motor_ADC_Temperature_Value(void);

#endif
