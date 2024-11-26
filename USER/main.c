#include "main.h"

int main(void)
{
	All_Hardware_Init();
	
	while(1)
	{
		BLDC_Motor_Test();
	}
}
