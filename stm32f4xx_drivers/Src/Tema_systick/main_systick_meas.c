#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"
#include "BSP_Systick.h"

#include <string.h>
#include <stdio.h>

int main(void){
	SYSCLK_PLL_setup();
	RCC_debug_GPIO_setup();
	// Establece la frecuencia a 150 MHz
	SYSTICK_Setup();
	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);
	while(1){

	}
	return 1;
}


void SysTick_Handler(void)
{
	RCC_debug_GPIO_Toggle();
}
