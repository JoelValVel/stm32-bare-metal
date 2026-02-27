#include "led_board.h"

static GPIO_handle_t LED_BOARD;

void LED_BOARD_init(void){
	LED_BOARD.pGPIOx = GPIOA;
	LED_BOARD.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	LED_BOARD.GPIO_config.GPIO_OType = GPIO_OType_PP;
	LED_BOARD.GPIO_config.GPIO_pin = GPIO_PIN_5;
	LED_BOARD.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	LED_BOARD.GPIO_config.GPIO_Speed = GPIO_Speed_LS;
	GPIO_Init(&LED_BOARD);
}

void LED_BOARD_toggle(void){
	GPIO_TogglePin(LED_BOARD.pGPIOx, LED_BOARD.GPIO_config.GPIO_pin);
}
