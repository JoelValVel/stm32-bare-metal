#include "BSP_TIM_ICOC.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"
#include "button_board.h"
#include "stm32f446xx_nvic.h"
#include "usart2.h"

#include <string.h>
#include <stdio.h>

uint32_t tim5_cnt;
uint8_t msg[48];
uint8_t dir;


void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}


int main(void)
{
	BUTTON_BOARD_init();
	TIM5_CH1IC_GPIO_Init();
	TIM5_CH2_GPIO_Init();
	TIM5_Encoder_Setup();
	TIM_Cmd(h_tim5.pTIMx, ENABLE);
	USART2_PIN_setup();
	USART2_Init();
	while(1)
	{
		/* En modo encoder CNT no cuenta por el clock del bus sino que cada flanco
		 * de TI1/TI2 lo incrementa o decrementa directamente según la dirección.
		 * La posición actual del encoder se obtiene leyendo TIM5->CNT en cualquier
		 * momento, sin necesidad de captura ni registros CCR */
		tim5_cnt = TIM_GetCounter(h_tim5.pTIMx);
		dir = (h_tim5.pTIMx->CR1 >> TIM_CR1_DIR) & 0x01;
		snprintf((char *)msg, sizeof(msg),"CNT: %ld [%s]\r\n", tim5_cnt, dir ? "-":"+");
		USART2_SendData(msg, strlen((char *)msg));


		delay(500000);
	}

	return 1;
}

