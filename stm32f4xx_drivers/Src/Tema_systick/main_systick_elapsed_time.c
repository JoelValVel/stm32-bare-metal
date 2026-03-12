#include "RCC_config_BSP.h"
#include "button_board.h"
#include "BSP_Systick.h"
#include "usart2.h"
#include <string.h>
#include <stdio.h>

uint32_t systick_delay;
uint8_t msg[64];
uint32_t system_ticks = 0;

void delay_ms(uint32_t ms)
{
	systick_delay = ms;
	while(systick_delay);
}


int main(void){
	uint32_t last_ticks = 0;
	uint32_t current_ticks = 0;
	uint32_t elapsed_ticks = 0;
	uint8_t system_ticks_overflow = 0;
	SYSCLK_PLL_setup();
	BUTTON_BOARD_init();
	USART2_PIN_setup();
	USART2_Init();
	// Establece la frecuencia a 150 MHz
	SYSTICK_Setup();
	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);

	while(1){
		if(button_pressed_f)
		{
			current_ticks = system_ticks;
			delay_ms(100);
			button_pressed_f = 0;

			if(current_ticks >= last_ticks)
			{
				elapsed_ticks = current_ticks - last_ticks;
				system_ticks_overflow = 0;
			}else
			{
				elapsed_ticks = (SYSTICK_MAX_COUNT - last_ticks + 1) + current_ticks;
				system_ticks_overflow = 1;
			}

		}
			snprintf((char *)msg, sizeof(msg),"ET: %d [ms] (current: %d last:%d overflow: %d)\r\n", elapsed_ticks, current_ticks, last_ticks, system_ticks_overflow);
			USART2_SendData(msg, strlen((char *)msg));

			last_ticks = current_ticks;
		}
	return 1;
}


void SysTick_Handler(void)
{
	if(systick_delay > 0)
	{
		systick_delay--;
	}
	system_ticks++;
}
