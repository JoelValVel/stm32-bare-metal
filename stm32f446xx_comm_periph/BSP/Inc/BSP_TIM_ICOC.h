/*
 * TIM_IC.h
 *
 *  Created on: 9 mar 2026
 *      Author: erjo_
 */

#ifndef INC_BSP_TIM_ICOC_H_
#define INC_BSP_TIM_ICOC_H_

#include "stm32f446xx_tim.h"
#include "stm32f446xx_rcc.h"
#include "stm32f446xx_nvic.h"

extern TIM_Handle_t h_tim2;
extern TIM_Handle_t h_tim5;

void TIM2_IT_ICOC_Setup(void);
void TIM2_IC_Setup(void);
void TIM2_IRQHandler(void);
void TIM2_OC_TOGGLE_Setup(void);
void TIM2_OC_TOGGLE_4Channels_Setup(void);
void TIM2_PWM_Setup(void);
void TIM5_PWM_M_Setup(void);
void TIM5_Encoder_Setup(void);

#endif /* INC_BSP_TIM_ICOC_H_ */
