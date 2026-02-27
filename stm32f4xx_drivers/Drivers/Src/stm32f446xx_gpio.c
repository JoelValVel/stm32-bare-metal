#include "stm32f446xx_gpio.h"
#include <stdint.h>

/* Funciones */

void GPIO_ClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t status){
	if(status == ENABLE){
		switch((uint32_t)pGPIOx){
			case (uint32_t) GPIOA:
				GPIOA_CLCK_EN();
				break;
			case (uint32_t) GPIOB:
				GPIOB_CLCK_EN();
				break;
			case (uint32_t) GPIOC:
				GPIOC_CLCK_EN();
				break;
			case (uint32_t) GPIOD:
				GPIOD_CLCK_EN();
				break;
			case (uint32_t) GPIOE:
				GPIOE_CLCK_EN();
				break;
			case (uint32_t) GPIOF:
				GPIOF_CLCK_EN();
				break;
			case (uint32_t) GPIOG:
				GPIOG_CLCK_EN();
				break;
			case (uint32_t) GPIOH:
				GPIOH_CLCK_EN();
				break;
		}
	}
	else if (status == DISABLE){
		switch((uint32_t)pGPIOx){
			case (uint32_t) GPIOA:
				GPIOA_CLCK_DIS();
				break;
			case (uint32_t) GPIOB:
				GPIOB_CLCK_DIS();
				break;
			case (uint32_t) GPIOC:
				GPIOC_CLCK_DIS();
				break;
			case (uint32_t) GPIOD:
				GPIOD_CLCK_DIS();
				break;
			case (uint32_t) GPIOE:
				GPIOE_CLCK_DIS();
				break;
			case (uint32_t) GPIOF:
				GPIOF_CLCK_DIS();
				break;
			case (uint32_t) GPIOG:
				GPIOG_CLCK_DIS();
				break;
			case (uint32_t) GPIOH:
				GPIOH_CLCK_DIS();
				break;
				}
	}
};

void GPIO_Init(GPIO_handle_t *pGPIO_handle){
	// 1. Habilitar el clock
	GPIO_ClkCtrl(pGPIO_handle->pGPIOx,ENABLE);

	// 2. Configurar modo (In OUT, AF, AN)
	pGPIO_handle->pGPIOx->MODER &= ~(0x03<<(pGPIO_handle->GPIO_config.GPIO_pin*2));
	pGPIO_handle->pGPIOx->MODER |= (pGPIO_handle->GPIO_config.GPIO_Mode << (pGPIO_handle->GPIO_config.GPIO_pin*2));
	// 3. Configurar speed
	pGPIO_handle->pGPIOx->OSPEEDR &= ~(0x03<<(pGPIO_handle->GPIO_config.GPIO_pin*2));
	pGPIO_handle->pGPIOx->OSPEEDR |= (pGPIO_handle->GPIO_config.GPIO_Speed<<(pGPIO_handle->GPIO_config.GPIO_pin*2));
	// 4. Configurar pu-pd
	pGPIO_handle->pGPIOx->PUPDR &= ~(0x03<<(pGPIO_handle->GPIO_config.GPIO_pin*2));
	pGPIO_handle->pGPIOx->PUPDR |= (pGPIO_handle->GPIO_config.GPIO_PuPd<<(pGPIO_handle->GPIO_config.GPIO_pin*2));

	// 5. Configurar tipo de salida, PP-open drain
	pGPIO_handle->pGPIOx->OTYPER &= ~(0x01<<pGPIO_handle->GPIO_config.GPIO_pin);
	pGPIO_handle->pGPIOx->OTYPER |= (pGPIO_handle->GPIO_config.GPIO_OType<<pGPIO_handle->GPIO_config.GPIO_pin);

	// 6. Config alt funct
	if(pGPIO_handle->GPIO_config.GPIO_Mode == GPIO_Mode_AF){
		uint8_t regidx, blkidx;
		regidx = pGPIO_handle->GPIO_config.GPIO_pin / 8;
		blkidx = pGPIO_handle->GPIO_config.GPIO_pin % 8;

		pGPIO_handle->pGPIOx->AFR[regidx] &= ~(0x0f<<(blkidx*4));
		pGPIO_handle->pGPIOx->AFR[regidx] |= ~(pGPIO_handle->GPIO_config.GPIO_AltFun<<(blkidx*4));
	}
};


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	switch((uint32_t) pGPIOx){
		case (uint32_t) GPIOA:
			GPIOA_REG_RESET();
			break;
		case (uint32_t) GPIOB:
			GPIOB_REG_RESET();
			break;
		case (uint32_t) GPIOC:
			GPIOC_REG_RESET();
			break;
		case (uint32_t) GPIOD:
			GPIOD_REG_RESET();
			break;
		case (uint32_t) GPIOE:
			GPIOE_REG_RESET();
			break;
		case (uint32_t) GPIOF:
			GPIOF_REG_RESET();
			break;
		case (uint32_t) GPIOG:
			GPIOG_REG_RESET();
			break;
		case (uint32_t) GPIOH:
			GPIOH_REG_RESET();
			break;
			}
};

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin){
	return (uint8_t) ((pGPIOx->IDR >> pin) & 0x01);
};

uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx){
	return (uint16_t)(pGPIOx->IDR & 0xFFFF);
};

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin, uint8_t data){
	pGPIOx->ODR = (pGPIOx->ODR & ~(1 << pin)) | (data << pin);
};
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t data){
	pGPIOx->ODR = data;
};

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin){
	pGPIOx->ODR ^= (1 << pin);
};

