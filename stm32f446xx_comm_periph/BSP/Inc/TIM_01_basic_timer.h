
#ifndef INC_TIM_01_BASIC_TIMER_H_
#define INC_TIM_01_BASIC_TIMER_H_

#include "stm32f446xx_tim.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_nvic.h"
#include "led_board.h"

extern TIM_Handle_t htim_led;

void TIM_Setup(void);
/*	INTERRUPCIONES 	*/
void TIM_IT_Setup(void);
void TIM6_DAC_IRQHandler(void);
void TIM_EventCallback(TIM_Handle_t *p_tim_handle, TIM_Event_t event);
#endif /* INC_TIM_01_BASIC_TIMER_H_ */
