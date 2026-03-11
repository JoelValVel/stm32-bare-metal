/*
 * APP_GPIO.h
 *
 *  Created on: 10 mar 2026
 *      Author: erjo_
 */

#ifndef INC_GPIO_BSP_H_
#define INC_GPIO_BSP_H_


#include "stm32f446xx_gpio.h"

void MCO1_GPIO_Init(void);

void TIM2_CH2IC_GPIO_Init(void);
void TIM2_CH1OC_GPIO_Init(void);
void RCC_debug_GPIO_setup(void);
void TIM2_OC_4Channels_GPIO_Setup(void);
void TIM2_CH1PWM_GPIO_Init(void);
void TIM5_CH1IC_GPIO_Init(void);
void TIM5_CH2_GPIO_Init(void);
#endif /* INC_GPIO_BSP_H_ */
