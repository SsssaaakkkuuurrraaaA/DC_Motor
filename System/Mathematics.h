#ifndef __MATHEMATICS_H
#define __MATHEMATICS_H

#include "stm32f4xx.h"                 

#include "stdlib.h"

#include "string.h"

#include "math.h"

#define Math_PI (3.141592653589)

#define Math_e  (2.718281828459)

void int_SetPositive_Value(int* Value);
void float_SetPositive_Value(float* Value);
void double_SetPositive_Value(double* Value);

void int_Turn_Sign(int* Value);
void float_Turn_Sign(float* Value);
void double_Turn_Sign(double* Value);

void char_Swap_Value(char* Value1, char* Value2);
void int_Swap_Value(int* Value1, int* Value2);
void uint8_t_Swap_Value(uint8_t* Value1, uint8_t* Value2);
void uint16_t_Swap_Value(uint16_t* Value1, uint16_t* Value2);
void uint32_t_Swap_Value(uint32_t* Value1, uint32_t* Value2);
void float_Swap_Value(float* Value1, float* Value2);
void double_Swap_Value(double* Value1, double* Value2);

uint8_t int_Sign_Positive_Check(int Number);
uint8_t float_Sign_Positive_Check(float Number);
uint8_t double_Sign_Positive_Check(double Number);

uint8_t int_Sign_TowValue_Check(int Num1, int Num2);
uint8_t float_Sign_TowValue_Check(float Num1, float Num2);
uint8_t double_Sign_TowValue_Check(double Num1, double Num2);

uint32_t func_get_greatest_common_divisor(uint32_t num1, uint32_t num2);

int32_t func_str_to_int(char *str);
void func_int_to_str(char *str, int32_t number);
uint32_t func_str_to_uint(char *str);
void func_uint_to_str(char *str, uint32_t number);
double func_str_to_double(char *str);
void func_double_to_str(char *str, double number, uint8_t point_bit);
uint32_t func_str_to_hex(char *str);
void func_hex_to_str(char *str, uint32_t number);
uint8_t number_conversion_ASCII(uint32_t dat, int8_t *p, uint8_t neg_type, uint8_t radix);

#endif
