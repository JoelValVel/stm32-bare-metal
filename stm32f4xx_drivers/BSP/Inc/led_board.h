/*
 * led_core.h
 *
 *  Created on: 26 feb 2026
 *      Author: erjo_
 */

#ifndef BSP_INC_LED_BOARD_H_
#define BSP_INC_LED_BOARD_H_


#include "stm32f446xx_gpio.h"


//extern GPIO_handle_t LED_BOARD;

void LED_BOARD_init(void);
void LED_BOARD_toggle(void);


#endif /* BSP_INC_LED_BOARD_H_ */
