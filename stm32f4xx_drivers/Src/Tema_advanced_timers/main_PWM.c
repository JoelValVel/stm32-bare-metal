#include "BSP_TIM_ICOC.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"
#include "button_board.h"
#include "stm32f446xx_nvic.h"

uint8_t dutycycle;
uint32_t CCR1_pulse;
void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

int main(void)
{
	BUTTON_BOARD_init();
	TIM2_CH1OC_GPIO_Init();
	TIM2_PWM_Setup();
	TIM_Cmd(h_tim2.pTIMx, ENABLE);

	while(1)
	{
		if(button_pressed_f)
		{
			delay(70000);
			button_pressed_f = 0;
			dutycycle += 25;
			(dutycycle > 100) ? (dutycycle = 0): (void)0;

		CCR1_pulse = (dutycycle *(h_tim2.TIM_TimeBase.TIM_Period + 1))/100;
		// actualiza el dutycycle al cambiar el CCRx
		TIM_SetCompare(h_tim2.pTIMx, TIM_CH1, CCR1_pulse);
		}
	}

	return 1;
}

