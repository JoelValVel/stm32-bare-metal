/*
 * RCC_config_app.h
 *
 *  Created on: 3 mar 2026
 *      Author: erjo_
 */

#ifndef APP_INC_RCC_CONFIG_APP_H_
#define APP_INC_RCC_CONFIG_APP_H_

#include "stm32f446xx_rcc.h"

void SYSCLK_HSE_setup(void);
void SYSCLK_HSI_setup(void);
void SYSCLK_PLL_setup(void);

#endif /* APP_INC_RCC_CONFIG_APP_H_ */
