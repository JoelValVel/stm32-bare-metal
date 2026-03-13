/*
 * stm32f446xx_rcc.h
 *
 *  Created on: 27 feb 2026
 *      Author: erjo_
 */

#ifndef INC_STM32F446XX_RCC_H_
#define INC_STM32F446XX_RCC_H_


#include "stm32f446xx.h"

/* RCC_HSE_Status*/
#define IS_VALID_PLLM_VAL(x)	((x < 64)&&(x > 1))
#define IS_VALID_PLLN_VAL(x)	((x < 433) && (x > 50))
#define IS_VALID_PLLP_VAL(x)	((x == 2) || (x == 4) || (x == 6) || (x == 8))
#define IS_VALID_PLLQ_VAL(x)	((x < 16) && (x > 1))
#define IS_VALID_PLLR_VAL(x)	((x < 8) && (x > 1))

typedef enum{
	RCC_HSE_ON,
	RCC_HSE_OFF,
	RCC_HSE_BYP,
}RCC_HSE_Status_t;

/* RCC_LSE_Status*/

typedef enum{
	RCC_LSE_ON,
	RCC_LSE_OFF,
	RCC_LSE_BYP,
}RCC_LSE_Status_t;

typedef enum{
	RCC_PLL_Source_HSI,
	RCC_PLL_Source_HSE,
}RCC_PLL_Source_t;

/*			MCO1			*/
typedef enum{
	RCC_MCO1_Source_HSI,
	RCC_MCO1_Source_LSE,
	RCC_MCO1_Source_HSE,
	RCC_MCO1_Source_PLL,
}RCC_MCO1_Source_t;

typedef enum{
	RCC_MCO1_Preescaler_None = 0,
	RCC_MCO1_Preescaler_2 = 4,
	RCC_MCO1_Preescaler_3 = 5,
	RCC_MCO1_Preescaler_4 = 6,
	RCC_MCO1_Preescaler_5 = 7,
}RCC_MCO_Prescaler_t;

/*			MCO2			*/
typedef enum{
	RCC_MCO2_Source_SYSCLK,
	RCC_MCO2_Source_PLLI2S,
	RCC_MCO2_Source_HSE,
	RCC_MCO2_Source_PLL,
}RCC_MCO2_Source_t;

/*			MCO2			*/
typedef enum{
	RCC_Clock_HSI,
	RCC_Clock_HSE,
	RCC_Clock_PLL,
	RCC_Clock_LSE,
}RCC_Clock_t;

typedef enum{
	RCC_SYSCLK_HSI,
	RCC_SYSCLK_HSE,
	RCC_SYSCLK_PLL_P,
	RCC_SYSCLK_PLL_R,
}RCC_SYSCLK_Source_t;

/*		APB Prescaler		*/
typedef enum{
	RCC_APB_Prescaler_None = 0,
	RCC_APB_Prescaler_2 = 4,
	RCC_APB_Prescaler_4 = 5,
	RCC_APB_Prescaler_8 = 6,
	RCC_APB_Prescaler_16 = 7,
}RCC_APB_Prescaler_t;

/*		AHB Prescaler		*/
typedef enum{
	RCC_AHB_Prescaler_None = 0,
	RCC_AHB_Prescaler_2 = 8,
	RCC_AHB_Prescaler_4 = 9,
	RCC_AHB_Prescaler_8 = 10,
	RCC_AHB_Prescaler_16 = 11,
	RCC_AHB_Prescaler_64 = 12,
	RCC_AHB_Prescaler_128 = 13,
	RCC_AHB_Prescaler_256 = 14,
	RCC_AHB_Prescaler_512 = 15,
}RCC_AHB_Prescaler_t;

/* Configuración external clocks (On, off o bypass) */
void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status);
void RCC_LSEConfig(RCC_LSE_Status_t LSE_Status);

/* Configuración PLL */
void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR);
//
/* Habilitación/Deshabilitación internal clocks y PLL */
void RCC_HSICmd(uint8_t status);
void RCC_LSICmd(uint8_t status);
void RCC_PLLCmd(uint8_t status);

/* Configuración salidas MCO1 y MCO2 */
void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO_Prescaler_t MCO1_Prescaler);
void RCC_MCO2Config(RCC_MCO2_Source_t MCO2_Source, RCC_MCO_Prescaler_t MCO2_Prescaler); //<-- se deja como ejercicio al alumno

/* Rutina para esperar a que un determinado clock esté OK */
void RCC_WaitForCLKRDY(RCC_Clock_t clk);

/* Configurar la fuente de clock del sistema */
void RCC_SYSCLKConfig(RCC_SYSCLK_Source_t SYSCLK_Source);

/* Obtener la fuente de clock del sistema */
RCC_SYSCLK_Source_t RCC_GetSYSCLKSource(void);

/* Configurar prescalers de AHB, APB1 y APB2 */
void RCC_AHBCLKConfig(RCC_AHB_Prescaler_t AHB_Prescaler);
void RCC_APB1CLKConfig(RCC_APB_Prescaler_t APB1_Prescaler);
void RCC_APB2CLKConfig(RCC_APB_Prescaler_t APB2_Prescaler);

/* Obtener frecuencia de clock del sistema y de los buses */
uint32_t RCC_GetSYSCLK(void);
uint32_t RCC_GetAHBCLK(void);
uint32_t RCC_GetAPB1CLK(void);
uint32_t RCC_GetAPB2CLK(void);
uint32_t RCC_GetAPB1_TimerCLK(void);
uint32_t RCC_GetAPB2_TimerCLK(void);



#endif /* INC_STM32F446XX_RCC_H_ */
