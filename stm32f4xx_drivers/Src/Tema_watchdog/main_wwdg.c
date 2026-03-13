#include "RCC_config_BSP.h"
#include "button_board.h"
#include "led_board.h"
#include "BSP_Systick.h"
#include "BSP_IWDG.h"

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
	BUTTON_BOARD_init();
	LED_BOARD_init();
	// Establece la frecuencia a 150 MHz
	SYSTICK_Setup();
	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);
	WWDG_Setup();
	delay_ms(300);
	LED_BOARD_toggle();
	WWDG_cmd(ENABLE);

	while(1){
		delay_ms(20);
		WWDG_Refresh(&WWDG_config);
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
