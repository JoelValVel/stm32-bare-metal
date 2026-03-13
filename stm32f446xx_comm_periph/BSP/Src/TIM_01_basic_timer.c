#include "TIM_01_basic_timer.h"

TIM_Handle_t htim_led;

void TIM6_Setup(void){
	htim_led.pTIMx = TIM6;
	// Periodo de 100 ms con el HSI de 16 MHz sin prescalers en
	// AHB y APBx
	htim_led.TIM_TimeBase.TIM_Period = 63999;
	htim_led.TIM_TimeBase.TIM_Prescaler = 24;

	TIM_TimeBaseInit(&htim_led);
}

void TIM6_IT_Setup(void){
	// habilitamos la interupcion en el periferico TIMER
	TIM_ITConfig(htim_led.pTIMx, TIM_SR_UIF, ENABLE);
	// habilitamos el IRQ del ISER del nvic
	NVIC_IRQ_Enable(IRQ_TIM6_DAC);
}

void TIM6_DAC_IRQHandler(void){
	TIM_IRQHandler(&htim_led);
}

