#include "BSP_Systick.h"

void SYSTICK_Setup(void)
{
	SYSTICK_Config_t SYSTICK_confg = {0};
	SYSTICK_confg.SYSTICK_Clock_Source = SYSTICK_Clk_Source_External;
	SYSTICK_confg.SYSTICK_Period = (SYSTICK_GetCalib() & 0x0FFFFFF) - 1;
	SYSTICK_Init(&SYSTICK_confg);
}

