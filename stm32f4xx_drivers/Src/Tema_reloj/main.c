#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_rcc.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"
void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

int main(void){
	uint32_t freq;

	RCC_debug_GPIO_setup();
	TIM2_CH2IC_GPIO_Init();
	delay(500000);

	/*********************** HSE ***********************/
	// Configurar HSE como fuente de reloj del sistema
	SYSCLK_HSE_setup();
	// Configurar MCO1 para sacar HSE por su pin
	RCC_MCO1Config(RCC_MCO1_Source_HSE, RCC_MCO1_Preescaler_4);
	// Leer frecuencia de SYSCLK
	freq = RCC_GetSYSCLK();
	// Mostrar tiempo de procesamiento de espera en PC10
	GPIO_WritePin(GPIOC, GPIO_PIN_10, ENABLE);

	delay(500000);

	GPIO_WritePin(GPIOC, GPIO_PIN_10, DISABLE);

	delay(500000);


	/*********************** HSI ***********************/
	// Configurar HSI como fuente de reloj del sistema
	SYSCLK_HSI_setup();
	// Configurar MCO1 para sacar HSE por su pin
	RCC_MCO1Config(RCC_MCO1_Source_HSI, RCC_MCO1_Preescaler_4);
	// Leer frecuencia de SYSCLK
	freq = RCC_GetSYSCLK();
	// Mostrar tiempo de procesamiento de espera en PC10
	GPIO_WritePin(GPIOC, GPIO_PIN_10, ENABLE);

	delay(500000);

	GPIO_WritePin(GPIOC, GPIO_PIN_10, DISABLE);

	delay(500000);

	/*********************** PLL  ***********************/
	// Configurar PLL como fuente de reloj del sistema
	SYSCLK_PLL_setup();
	// Configurar MCO1 para sacar HSE por su pin
	RCC_MCO1Config(RCC_MCO1_Source_PLL, RCC_MCO1_Preescaler_5);
	// Leer frecuencia de SYSCLK
	freq = RCC_GetSYSCLK();
	// Mostrar tiempo de procesamiento de espera en PC10
	GPIO_WritePin(GPIOC, GPIO_PIN_10, ENABLE);

	delay(500000);

	GPIO_WritePin(GPIOC, GPIO_PIN_10, DISABLE);

	delay(500000);




	while(1);


}
