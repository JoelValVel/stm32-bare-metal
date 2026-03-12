#include "RCC_config_BSP.h"

void assert_failed(uint8_t *file, uint32_t line)
{
    while(1);   // Queda atrapado aquí si un assert falla
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

 /*	180 MHz*/
// void SYSCLK_PLL_setup(void){
//	 uint32_t PLLM, PLLN, PLLQ, PLLR, PLLP;
//	 PLLM = 8;
//	 PLLN = 336;
//	 PLLP = 2;
//	 PLLQ = 7;
//	 PLLR = 5;
//
//	 //Configurar el APB1 y APB2
//	 RCC_APB1CLKConfig(RCC_APB_Prescaler_4);
//	 RCC_APB2CLKConfig(RCC_APB_Prescaler_2);
//	 // Habilitar HSE
//	 RCC_HSEConfig(RCC_HSE_ON);
//
//	 // Esperar a que HSE esté ok
//	 RCC_WaitForCLKRDY(RCC_Clock_HSE);
//
//	 // Configurar el PLL
//	 RCC_PLLConfig(RCC_PLL_Source_HSE, PLLM, PLLN, PLLP, PLLQ, PLLR);
//
//	 // Habilitar PLL
//	 RCC_PLLCmd(ENABLE);
//
//	 // ESperar a que esté ok
//	 RCC_WaitForCLKRDY(RCC_Clock_PLL);
//
//	 // Flash latency
//	 *((volatile uint32_t *) 0x40023C00) = 0x05;
//
//	 // Seleccionar PLL como reloj
//	 RCC_SYSCLKConfig(RCC_SYSCLK_PLL_P);
// }

 /*	150 MHz*/
 void SYSCLK_PLL_setup(void){
 	 uint32_t PLLM, PLLN, PLLQ, PLLR, PLLP;
 	 PLLM = 4;
 	 PLLN = 150;
 	 PLLP = 2;
 	 PLLQ = 8;
 	 PLLR = 2;

 	 //Configurar el APB1 y APB2
 	 RCC_APB1CLKConfig(RCC_APB_Prescaler_4);
 	 RCC_APB2CLKConfig(RCC_APB_Prescaler_2);
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
 	 *((volatile uint32_t *) 0x40023C00) = 0x04;

 	 // Seleccionar PLL como reloj
 	 RCC_SYSCLKConfig(RCC_SYSCLK_PLL_P);
  }
