#include "stm32f446xx_rcc.h"

uint16_t AHB_prescaler[16] = {1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512};
uint16_t APB_prescaler[8] = {1,1,1,1,2,4,8,16};

/** @brief	Configura el External High Speed oscillator (HSE)
  *  @note 	Posterior a la habilitación del HSE (RCC_HSE_ON o RCC_HSE_BYPASS)
  *  		la aplicación debe esperar a que se setee el flag HSERDY antes de usarlo
  *  		como clock.
  *  @note	No se puede cambiar el estado del HSE si está siento usado (directamente o
  *  		a través del PLL) como clock del sistema. En ese caso, hay que configurar
  *  		primero otra fuente como reloj antes de configurar el HSE.
  *  @note	Esta función resetea el bit CSSON por lo que si está siendo usado, habrá
  *  		que habilitarlo después de ejecutar esta función.
  *  @param	HSE_Status: estado del HSE, cuyos valores pueden ser:
  *  			@arg	RCC_HSE_OFF: deshabilita el HSE, el flag HSERDY se resetea después
  *  					de 6 ciclos de reloj.
  *  			@arg 	RCC_HSE_ON: habilita el HSE.
  *  			@arg	RCC_HSE_BYP Habilita el HSE para ser usado por una señal de reloj ext.
  *  @retval	None
  */
void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status){
	// Limpiar los bits DEL HSE y CSS antes de configurarlo
	RCC->CR &= ~((1 << RCC_CR_CSSON)|(1 << RCC_CR_HSEON)|(1 << RCC_CR_HSEBYP));
	if(HSE_Status == RCC_HSE_ON){
		RCC->CR |= (1 << RCC_CR_HSEON);
	}
	else if(HSE_Status == RCC_HSE_BYP){
		RCC->CR |= ((1 << RCC_CR_HSEBYP)|(1 << RCC_CR_HSEON));
	}
};

/**
  * @brief  Configura el External Low Speed oscillator (LSE).
  * @note 	Como el LSE está en el dominio de Backup y, después del reset, el acceso de
  * 		escritura no está permitido en ese dominio, es necesario habilitarlo mediante
  * 		el seteo del bit DBP (Disable backup domain write protection) en el registro
  * 		PWR_CR (Power Control Register).
  * @note   Posteriormente a la habilitación del LSE (RCC_LSE_ON o RCC_LSE_Bypass),
  * 		la aplicación debe esperar a que se setee el flag LSERDY antes de usarlo
  * 		como clock para el RTC.
  * @param  LSE_Status: estado del LSE, cuyos valores pueden ser:
  *            @arg RCC_LSE_OFF: deshabilita el LSE, el flag LSERDY se resetea después de
  *            					 6 ciclos de reloj.
  *            @arg RCC_LSE_ON: habilita el LSE
  *            @arg RCC_LSE_BYP: habilita el LSE para ser usado por una señal de reloj externa
  * @retval None
  */
void RCC_LSEConfig(RCC_LSE_Status_t LSE_Status){
	// Habilitamos el reloj del registro PWR
	PWR_CLCK_EN();
	// Habilitar la escritura en el bakcup
	PWR->CR |= (1 << PWR_CR_DBP);
	// Limpiar los bits DEL LSEON, LSERDY y LSEBYP antes de configurarlo
	RCC->BDCR &= ~((1 << RCC_BDCR_LSEON)|(1 << RCC_BDCR_LSERDY)|(1 << RCC_BDCR_LSEBYP));
	if(LSE_Status == RCC_LSE_ON){
		RCC->BDCR |= (1 << RCC_BDCR_LSEON);
	}
	else if(LSE_Status == RCC_LSE_BYP){
		RCC->BDCR |= ((1 << RCC_BDCR_LSEBYP)|(1 << RCC_BDCR_LSEON));
	}
};

void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR){
	uint32_t temp_RCC_PLLCFGR;
	ASSERT_TRUE(IS_VALID_PLLM_VAL(PLLM));
	ASSERT_TRUE(IS_VALID_PLLN_VAL(PLLN));
	ASSERT_TRUE(IS_VALID_PLLP_VAL(PLLP));
	ASSERT_TRUE(IS_VALID_PLLQ_VAL(PLLQ));
	ASSERT_TRUE(IS_VALID_PLLR_VAL(PLLR));

	temp_RCC_PLLCFGR = PLLM | (PLLN << RCC_PLLCFGR_PLLN) | (((PLLP >> 1)-1) << RCC_PLLCFGR_PLLP) |
						(PLLQ << RCC_PLLCFGR_PLLQ) | (PLLR << RCC_PLLCFGR_PLLR);
	RCC->PLLCFGR = temp_RCC_PLLCFGR;
};

void RCC_HSICmd(uint8_t status){
	if (status == ENABLE){
		RCC->CR |= (1 << RCC_CR_HSION);
	}else if (status == DISABLE){
		RCC->CR &= ~(1 << RCC_CR_HSION);
	}

};
void RCC_LSICmd(uint8_t status){
	if (status == ENABLE){
		RCC->CSR |= (1 << RCC_CSR_LSION);
	}else if (status == DISABLE){
		RCC->CSR &= ~(1 << RCC_CSR_LSION);
	}
};
void RCC_PLLCmd(uint8_t status){
	if (status == ENABLE){
		RCC->CR |= (1 << RCC_CR_PLLON);
	} else if (status == DISABLE){
		RCC->CR &= ~(1 << RCC_CR_PLLON);
	}
};
void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO_Prescaler_t MCO1_Prescaler){
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiamos los bits del source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_MCO1);
	// Limpiamos los bits del preescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_MCO1PRE);

	// Seteamos los bits del source
	temp_RCC_CFGR |= (MCO1_Source << RCC_CFGR_MCO1);
	// Setemos los bits del prescaler
	temp_RCC_CFGR |= (MCO1_Prescaler << RCC_CFGR_MCO1PRE);

	RCC->CFGR = temp_RCC_CFGR;

};

void RCC_MCO2Config(RCC_MCO2_Source_t MCO2_Source, RCC_MCO_Prescaler_t MCO2_Prescaler){
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiamos los bits del source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_MCO2);
	// Limpiamos los bits del preescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_MCO2PRE);

	// Seteamos los bits del source
	temp_RCC_CFGR |= (MCO2_Source << RCC_CFGR_MCO2);
	// Setemos los bits del prescaler
	temp_RCC_CFGR |= (MCO2_Prescaler << RCC_CFGR_MCO2PRE);

	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_WaitForCLKRDY(RCC_Clock_t clk){
	switch(clk){
		case (RCC_Clock_HSI):
			while(!(RCC->CR & (1 << RCC_CR_HSIRDY)));
			break;
		case (RCC_Clock_HSE):
			while(!(RCC->CR & (1 << RCC_CR_HSERDY)));
			break;
		case (RCC_Clock_LSE):
			while(!(RCC->BDCR & (1 << RCC_BDCR_LSERDY)));
			break;
		case (RCC_Clock_PLL):
			while(!(RCC->CR & (1 << RCC_CR_PLLRDY)));
			break;
	}

}
void RCC_SYSCLKConfig(RCC_SYSCLK_Source_t SYSCLK_Source){
	// Limpiamos los bits del source
	RCC->CFGR &= ~(0x03 << RCC_CFGR_SW);
	// Seteamos los bits del source
	RCC->CFGR |= (SYSCLK_Source << RCC_CFGR_SW);
}

RCC_SYSCLK_Source_t RCC_GetSYSCLKSource(void){
	uint8_t temp_SYSCLK_Source;
	temp_SYSCLK_Source = ((RCC->CFGR >> RCC_CFGR_SWS) & (0x03));
	return (RCC_SYSCLK_Source_t) temp_SYSCLK_Source;
}

void RCC_AHBCLKConfig(RCC_AHB_Prescaler_t AHB_Prescaler){
	// Limpiamos los bits del prescaler AHB
	RCC->CFGR &= ~(0x0F << RCC_CFGR_HPRE);
	// Seteamos los bits del prescaler AHB
	RCC->CFGR |= (AHB_Prescaler << RCC_CFGR_HPRE);
}
void RCC_APB1CLKConfig(RCC_APB_Prescaler_t APB1_Prescaler){
	// Limpiamos los bits del prescaler APB1
	RCC->CFGR &= ~(0x07 << RCC_CFGR_PPRE1);
	// Seteamos los bits del prescaler APB1
	RCC->CFGR |= (APB1_Prescaler << RCC_CFGR_PPRE1);
}
void RCC_APB2CLKConfig(RCC_APB_Prescaler_t APB2_Prescaler){
	// Limpiamos los bits del prescaler APB2
	RCC->CFGR &= ~(0x07 << RCC_CFGR_PPRE2);
	// Seteamos los bits del prescaler APB2
	RCC->CFGR |= (APB2_Prescaler << RCC_CFGR_PPRE2);
}

uint32_t RCC_GetSYSCLK(void){
	uint32_t PLL_src;
	uint32_t PLL_M;
	uint32_t PLL_N;
	uint32_t PLL_VCO;
	uint32_t PLL_P;
	uint32_t PLL_R;
	uint32_t freq;
	uint32_t rcc_cfgr_sws;

	rcc_cfgr_sws = ((RCC->CFGR>>RCC_CFGR_SWS) & (0x03));
	switch(rcc_cfgr_sws){
	case(RCC_SYSCLK_HSI):
		freq = HSI_FREQ;
		break;
	case(RCC_SYSCLK_HSE):
		freq = HSE_FREQ;
		break;
	case(RCC_SYSCLK_PLL_P):
		/********************** PLL P **********************
		*  PLL_VCO = (PLL_src / PLLM) * PLLN
		*  SYSCLK = PLL_VCO / PLLP
		***************************************************/
		PLL_src = ((RCC->PLLCFGR>>RCC_PLLCFGR_PLLSRC) & 0x01);
		PLL_M = RCC->PLLCFGR & 0x3F;
		PLL_N = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x1FF);
		if(PLL_src){
			PLL_VCO = (HSE_FREQ / PLL_M) * PLL_N;
		}else{
			PLL_VCO = (HSI_FREQ / PLL_M) * PLL_N;
		}
		PLL_P = (((RCC->PLLCFGR >> RCC_PLLCFGR_PLLP) & 0x03) << 1)+2;
		freq = PLL_VCO / PLL_P;
		break;
	case(RCC_SYSCLK_PLL_R):
		/********************** PLL R **********************
		 *  PLL_VCO = (PLL_src / PLLM) * PLLN
		 *  SYSCLK = PLL_VCO / PLLR
		 ***************************************************/
		PLL_src = ((RCC->PLLCFGR>>RCC_PLLCFGR_PLLSRC) & 0x01);
		PLL_M = RCC->PLLCFGR & 0x3F;
		PLL_N = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x1FF);
		if(PLL_src){
			PLL_VCO = (HSE_FREQ / PLL_M) * PLL_N;
		}else{
			PLL_VCO = (HSI_FREQ / PLL_M) * PLL_N;
		}
		PLL_R = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLR) & 0x07);
		freq = PLL_VCO / PLL_R;
		break;
	}
	return freq;
}
uint32_t RCC_GetAHBCLK(void){
	uint32_t AHB_prescaler_bits;
	uint32_t AHB_prescaler_value;
	AHB_prescaler_bits = ((RCC->CFGR >> RCC_CFGR_HPRE) & 0x0F);
	AHB_prescaler_value = AHB_prescaler[AHB_prescaler_bits];
	return RCC_GetSYSCLK()/AHB_prescaler_value;
}
uint32_t RCC_GetAPB1CLK(void){
	uint32_t APB1_prescaler_bits;
	uint32_t APB1_prescaler_value;
	APB1_prescaler_bits = ((RCC->CFGR >> RCC_CFGR_PPRE1) & 0x07);
	APB1_prescaler_value = APB_prescaler[APB1_prescaler_bits];
	return RCC_GetAHBCLK()/APB1_prescaler_value;
}
uint32_t RCC_GetAPB2CLK(void){
	uint32_t APB2_prescaler_bits;
	uint32_t APB2_prescaler_value;
	APB2_prescaler_bits = ((RCC->CFGR >> RCC_CFGR_PPRE2) & 0x07);
	APB2_prescaler_value = APB_prescaler[APB2_prescaler_bits];
	return RCC_GetAHBCLK()/APB2_prescaler_value;
}

