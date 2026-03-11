#include "led_board.h"
#include "TIM_01_basic_timer.h"

void main(void){
	// Inicializa el led de la placa
	LED_BOARD_init();
	// Inicializa el timer 6 con T=100ms
	TIM_Setup();
	// Inicializa la interrupcion por Update
	TIM_IT_Setup();
	// Inicia el conteo
	TIM_Cmd(htim_led.pTIMx, ENABLE);

	while(1);
}
