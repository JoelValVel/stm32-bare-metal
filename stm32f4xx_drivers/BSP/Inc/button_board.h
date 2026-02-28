/*
 * button_board.h
 *
 *  Created on: 27 feb 2026
 *      Author: erjo_
 */

#ifndef INC_BUTTON_BOARD_H_
#define INC_BUTTON_BOARD_H_

#include "stm32f446xx_gpio.h"


void BUTTON_BOARD_init(void);
uint8_t BUTTON_BOARD_read(void);
extern uint8_t button_pressed_f;
void EXTI15_10_IRQHandler(void);

#endif /* INC_BUTTON_BOARD_H_ */
