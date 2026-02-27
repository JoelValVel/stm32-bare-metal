/*
 * button_board.c
 *
 *  Created on: 27 feb 2026
 *      Author: erjo_
 */

#include "button_board.h"

static GPIO_handle_t BUTTON_BOARD;

void BUTTON_BOARD_init(void){
		BUTTON_BOARD.pGPIOx = GPIOC;
		BUTTON_BOARD.GPIO_config.GPIO_Mode = GPIO_Mode_IN;
		BUTTON_BOARD.GPIO_config.GPIO_pin = GPIO_PIN_13;
		BUTTON_BOARD.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
		BUTTON_BOARD.GPIO_config.GPIO_Speed = GPIO_Speed_LS;
		GPIO_Init(&BUTTON_BOARD);
};
uint8_t BUTTON_BOARD_read(void){
	return GPIO_ReadPin(BUTTON_BOARD.pGPIOx, BUTTON_BOARD.GPIO_config.GPIO_pin);
};
