/*
 * BSP_Systick.h
 *
 *  Created on: 11 mar 2026
 *      Author: erjo_
 */

#ifndef INC_BSP_SYSTICK_H_
#define INC_BSP_SYSTICK_H_

#include "stm32f445xx_systick.h"

extern uint8_t button_pressed_f;
void SYSTICK_Setup(void);
#endif /* INC_BSP_SYSTICK_H_ */
