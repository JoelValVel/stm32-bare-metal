#include "RCC_config_BSP.h"
#include "led_board.h"
#include "BSP_Systick.h"

#include <string.h>
#include <stdio.h>

uint32_t systick_delay;

void delay_ms(uint32_t ms)
{
	systick_delay = ms;
	while(systick_delay);
}


int main(void){
	SYSCLK_PLL_setup();
	LED_BOARD_init();
	// Establece la frecuencia a 150 MHz
	SYSTICK_Setup();
	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);
	while(1){
		LED_BOARD_toggle();
		delay_ms(500);
	}
	return 1;
}


void SysTick_Handler(void)
{
	if(systick_delay > 0)
	{
		systick_delay--;
	}

}
