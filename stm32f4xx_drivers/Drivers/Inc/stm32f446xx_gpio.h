
#ifndef DRIVERS_INC_STM32F446XX_GPIO_H_
#define DRIVERS_INC_STM32F446XX_GPIO_H_

#include "stm32f446xx.h"
#include <stdint.h>
typedef enum{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
}GPIO_Pin_t;

typedef enum{
	GPIO_Mode_IN,		// Input
	GPIO_Mode_OUT,		// Output
	GPIO_Mode_AF,		// Alternative function
	GPIO_Mode_AN,		// Analog
	GPIO_Mode_INT_RE,	// Interrupt rising edge
	GPIO_Mode_INT_FE,	// Interrupt falling edge
	GPIO_Mode_INT_RFE,	// Interrupt rising-falling edge
}GPIO_Mode_t;

typedef enum{
	GPIO_ALTFUN_0,
	GPIO_ALTFUN_1,
	GPIO_ALTFUN_2,
	GPIO_ALTFUN_3,
	GPIO_ALTFUN_4,
	GPIO_ALTFUN_5,
	GPIO_ALTFUN_6,
	GPIO_ALTFUN_7,
	GPIO_ALTFUN_8,
	GPIO_ALTFUN_9,
	GPIO_ALTFUN_10,
	GPIO_ALTFUN_11,
	GPIO_ALTFUN_12,
	GPIO_ALTFUN_13,
	GPIO_ALTFUN_14,
	GPIO_ALTFUN_15,
}GPIO_AltFun_t;

typedef enum{
	GPIO_Speed_LS,	//Low speed
	GPIO_Speed_MS,	// Medium speed
	GPIO_Speed_FS,	// Fast speed
	GPIO_Speed_HS,	// High speed
}GPIO_Speed_t;

typedef enum{
	GPIO_PuPd_NONE,
	GPIO_PuPd_UP,
	GPIO_PuPd_DOWN,
}GPIO_PuPd_t;

typedef enum{
	GPIO_OType_PP,	//pull push
	GPIO_OType_OD,	// open drain

}GPIO_OType_t;
typedef struct{
	GPIO_Pin_t GPIO_pin;  // Numero de pin. Posibles valores @GPIO_Pin_t
	GPIO_Mode_t GPIO_Mode;
	GPIO_Speed_t GPIO_Speed;
	GPIO_PuPd_t GPIO_PuPd;
	GPIO_OType_t GPIO_OType;
	GPIO_AltFun_t GPIO_AltFun;
}GPIO_Config_t;

typedef struct{
	GPIO_RegDef_t *pGPIOx;
	GPIO_Config_t GPIO_config;
}GPIO_handle_t;


/* Funciones prototipo*/

void GPIO_ClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t status);
void GPIO_Init(GPIO_handle_t *pGPIO_handle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin, uint8_t data);
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t data);

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin);

void GPIO_NVIC_IRQ_Enable(uint8_t IRQ);
void GPIO_NVIC_IRQ_Disable(uint8_t IRQ);
void GPIO_NVIC_Priority(uint8_t IRQ, uint32_t priority);
void GPIO_IRQHandler(uint8_t pin);
#endif /* DRIVERS_INC_STM32F446XX_GPIO_H_ */
