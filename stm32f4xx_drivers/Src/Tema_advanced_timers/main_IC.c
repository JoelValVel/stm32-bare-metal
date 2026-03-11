#include "TIM_01_basic_timer.h"
#include "BSP_TIM_ICOC.h"
#include "led_board.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"
typedef enum{
	waiting_for_cap1_st,
	waiting_for_cap2_st,
	processing_st
}freq_measurement_st_t;
freq_measurement_st_t freq_measurement = waiting_for_cap1_st;
uint32_t capture1;
uint32_t capture2;
uint32_t capture_diff;
uint32_t freq;
uint32_t CNT_CLCK_freq;
uint8_t tim6_cycle;
int main(void){

	SYSCLK_PLL_setup();

	// Configurar LSE
	RCC_LSEConfig(RCC_LSE_ON);
	RCC_WaitForCLKRDY(RCC_Clock_LSE);

	// Configurar MCO1
	RCC_MCO1Config(RCC_MCO1_Source_LSE, RCC_MCO1_Preescaler_None);

	TIM2_CH2IC_GPIO_Init();
	MCO1_GPIO_Init();
	TIM2_IC_Setup();

	TIM2_IT_ICOC_Setup();

	TIM_Cmd(h_tim2.pTIMx, ENABLE);
	CNT_CLCK_freq = RCC_GetAPB1_TimerCLK()/(h_tim2.TIM_TimeBase.TIM_Prescaler + 1);
	while(1);
	return 1;
}

void IC_StateMachine(void){
	switch(tim6_cycle){
	case(waiting_for_cap1_st):
		capture1 = TIM_GetCapture(h_tim2.pTIMx, TIM_CH2);
		break;
	case(waiting_for_cap2_st):
		capture2 = TIM_GetCapture(h_tim2.pTIMx, TIM_CH2);
		if(capture1 < capture2){
			capture_diff = capture2 - capture1;
		}else{
			capture_diff = 0xFFFFFFFF - capture1 + capture2 + 1;
		}
		freq = CNT_CLCK_freq / capture_diff;
		break;
	default:
		break;
	}

}

uint8_t tim6_cycle = 0;

void TIM_EventCallback(TIM_Handle_t *p_tim_handle, TIM_Event_t event){
	if(p_tim_handle->pTIMx == TIM6){
	        switch(event)
	        {
	            case TIM_EVENT_UI:
	                LED_BOARD_toggle();
	                break;
	            default:
	                break;
	        }
	}else if(p_tim_handle->pTIMx == TIM2){
		switch(event){
			case TIM_EVENT_CC2I:
				tim6_cycle = (tim6_cycle % 2) + 1;
				IC_StateMachine();
				break;
			default:
				break;
		}
	}
}
