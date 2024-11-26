#include "BLDC.h"

void BLDC_Motor_Test(void)
{
    int32_t PWM_Set = 3000;

	BLDC_Motor_Init();
    
    if(Key_Value == KEY0)
    {
        PWM_Set += 500;
        BLDC_Motor_Set_PWM(PWM_Set);

        BLDC_parameter.BLDC_State = BLDC_RUN;
        BLDC_parameter.BLDC_Direction = BLDC_FORWARD;
    }

    else if(Key_Value == KEY1)
    {
        PWM_Set -= 500;
        BLDC_Motor_Set_PWM(PWM_Set);

        BLDC_parameter.BLDC_State = BLDC_RUN;
        BLDC_parameter.BLDC_Direction = BLDC_BACKWARD;
    }

    else if(Key_Value == KEY2)
    {
        BLDC_parameter.BLDC_State = BLDC_STOP;
        PWM_Set = 0;
    }
}
