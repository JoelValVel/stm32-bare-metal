#include "BSP_TIM_ICOC.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"
#include "button_board.h"
#include "stm32f446xx_nvic.h"
#include "usart2.h"

#include <string.h>
#include <stdio.h>

uint8_t dutycycle;
uint32_t CCR1_pulse;
uint32_t cc1r;
uint32_t PWM_T;
uint8_t msg[48];
float PWM_DC;


void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}


int main(void)
{
	BUTTON_BOARD_init();
	TIM2_CH1PWM_GPIO_Init();
	TIM5_CH1IC_GPIO_Init();
	TIM2_PWM_Setup();
	TIM5_PWM_M_Setup();
	TIM_Cmd(h_tim2.pTIMx, ENABLE);
	TIM_Cmd(h_tim5.pTIMx, ENABLE);
	USART2_PIN_setup();
	USART2_Init();
	while(1)
	{
		if(button_pressed_f)
		{
			delay(70000);
			button_pressed_f = 0;
			dutycycle += 25;
			(dutycycle > 100) ? (dutycycle = 0): (void)0;

		CCR1_pulse = (dutycycle *(h_tim2.TIM_TimeBase.TIM_Period + 1))/100;
		TIM_SetCompare(h_tim2.pTIMx, TIM_CH1, CCR1_pulse);
		}
		cc1r = TIM_GetCapture(h_tim5.pTIMx, TIM_CH1);

		if(cc1r > 0)
		{
			PWM_T = (cc1r + 1)*1000/(RCC_GetAPB1_TimerCLK()/(h_tim5.TIM_TimeBase.TIM_Prescaler + 1));
			PWM_DC = 100.0*(TIM_GetCapture(h_tim5.pTIMx, TIM_CH2) + 1)/(cc1r + 1);
		}else
		{
			PWM_T = 0;
			PWM_DC = 0;
		}
		snprintf((char *)msg, sizeof(msg),"T: %ldms  DC: %.2f%%\r\n", PWM_T, PWM_DC);
		USART2_SendData(msg, strlen((char *)msg));

		delay(500000);
	}

	return 1;
}

