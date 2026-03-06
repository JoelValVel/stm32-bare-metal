#include "stm32f446xx_rcc.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx.h"
#include "RCC_config_app.h"

void assert_failed(uint8_t *file, uint8_t line)
{
    while(1);   // Queda atrapado aquí si un assert falla
}

void GPIO_setup(void){
	GPIO_handle_t PC10_debug;
	PC10_debug.pGPIOx = GPIOC;
	PC10_debug.GPIO_config.GPIO_pin = GPIO_PIN_10;
	PC10_debug.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	PC10_debug.GPIO_config.GPIO_OType = GPIO_OType_PP;
	PC10_debug.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	PC10_debug.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	GPIO_Init(&PC10_debug);

	GPIO_handle_t PA8_MCO1;
	PA8_MCO1.pGPIOx = GPIOA;
	PA8_MCO1.GPIO_config.GPIO_pin = GPIO_PIN_8;
	PA8_MCO1.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	PA8_MCO1.GPIO_config.GPIO_OType = GPIO_OType_PP;
	PA8_MCO1.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	PA8_MCO1.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	PA8_MCO1.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_0;
	GPIO_Init(&PA8_MCO1);
}
 void SYSCLK_HSE_setup(void){
	 // Habilitar HSE
	 RCC_HSEConfig(RCC_HSE_ON);

	 // ESperar a que HSE este listo
	 RCC_WaitForCLKRDY(RCC_Clock_HSE);

	 // Seleccionar HSE como fuente de reloj del sistema
	 RCC_SYSCLKConfig(RCC_SYSCLK_HSE);
 }

 void SYSCLK_HSI_setup(void){
	 // Habilitar HSE
	 RCC_HSICmd(ENABLE);

	 // ESperar a que HSE este listo
	 RCC_WaitForCLKRDY(RCC_Clock_HSI);

	 // Seleccionar HSE como fuente de reloj del sistema
	 RCC_SYSCLKConfig(RCC_SYSCLK_HSI);
 }

 void SYSCLK_PLL_setup(void){
	 uint32_t PLLM, PLLN, PLLQ, PLLR, PLLP;
	 PLLM = 8;
	 PLLN = 336;
	 PLLP = 2;
	 PLLQ = 7;
	 PLLR = 5;
	 // Habilitar HSE
	 RCC_HSEConfig(RCC_HSE_ON);

	 // Esperar a que HSE esté ok
	 RCC_WaitForCLKRDY(RCC_Clock_HSE);

	 // Configurar el PLL
	 RCC_PLLConfig(RCC_PLL_Source_HSE, PLLM, PLLN, PLLP, PLLQ, PLLR);

	 // Habilitar PLL
	 RCC_PLLCmd(ENABLE);

	 // ESperar a que esté ok
	 RCC_WaitForCLKRDY(RCC_Clock_PLL);

	 // Flash latency
	 *((volatile uint32_t *) 0x40023C00) = 0x05;

	 // Seleccionar PLL como reloj
	 RCC_SYSCLKConfig(RCC_SYSCLK_PLL_P);
 }

