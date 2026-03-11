#include "stm32f446xx_tim.h"

void TIM_ClkCtrl(TIM_RegDef_t *p_tim_reg, uint8_t status){
	if(status == ENABLE){
		switch((uint32_t) p_tim_reg){
			case((uint32_t)TIM1):
		        TIM1_EN_CLK();
		        break;

		    case((uint32_t)TIM2):
		        TIM2_EN_CLK();
		        break;

		    case((uint32_t)TIM3):
		        TIM3_EN_CLK();
		        break;

		    case((uint32_t)TIM4):
		        TIM4_EN_CLK();
		        break;

		    case((uint32_t)TIM5):
		        TIM5_EN_CLK();
		        break;

		    case((uint32_t)TIM6):
		        TIM6_EN_CLK();
		        break;

		    case((uint32_t)TIM7):
		        TIM7_EN_CLK();
		        break;

		    case((uint32_t)TIM8):
		        TIM8_EN_CLK();
		        break;

		    case((uint32_t)TIM9):
		        TIM9_EN_CLK();
		        break;

		    case((uint32_t)TIM10):
		        TIM10_EN_CLK();
		        break;

		    case((uint32_t)TIM11):
		        TIM11_EN_CLK();
		        break;

		    case((uint32_t)TIM12):
		        TIM12_EN_CLK();
		        break;

		    case((uint32_t)TIM13):
		        TIM13_EN_CLK();
		        break;

		    case((uint32_t)TIM14):
		        TIM14_EN_CLK();
		        break;

		    default:
		        break;
		}

	}else if(status == DISABLE){
		switch((uint32_t) p_tim_reg)
		{
		    case((uint32_t)TIM1):
		        TIM1_DIS_CLK();
		        break;

		    case((uint32_t)TIM2):
		        TIM2_DIS_CLK();
		        break;

		    case((uint32_t)TIM3):
		        TIM3_DIS_CLK();
		        break;

		    case((uint32_t)TIM4):
		        TIM4_DIS_CLK();
		        break;

		    case((uint32_t)TIM5):
		        TIM5_DIS_CLK();
		        break;

		    case((uint32_t)TIM6):
		        TIM6_DIS_CLK();
		        break;

		    case((uint32_t)TIM7):
		        TIM7_DIS_CLK();
		        break;

		    case((uint32_t)TIM8):
		        TIM8_DIS_CLK();
		        break;

		    case((uint32_t)TIM9):
		        TIM9_DIS_CLK();
		        break;

		    case((uint32_t)TIM10):
		        TIM10_DIS_CLK();
		        break;

		    case((uint32_t)TIM11):
		        TIM11_DIS_CLK();
		        break;

		    case((uint32_t)TIM12):
		        TIM12_DIS_CLK();
		        break;

		    case((uint32_t)TIM13):
		        TIM13_DIS_CLK();
		        break;

		    case((uint32_t)TIM14):
		        TIM14_DIS_CLK();
		        break;

		    default:
		        break;
		}
	}

}

void TIM_ITConfig(TIM_RegDef_t *p_tim_reg, uint16_t it_type, uint8_t status){
	if(status == ENABLE){
		p_tim_reg->DIER |= (1 << it_type);
	}else if(status == DISABLE){
		p_tim_reg->DIER &= ~(1 << it_type);
	}
}

void TIM_TimeBaseInit(TIM_Handle_t *p_tim_handle){
	// Habilitamos el reloj
	TIM_ClkCtrl(p_tim_handle->pTIMx, ENABLE);

	p_tim_handle->pTIMx->ARR = p_tim_handle->TIM_TimeBase.TIM_Period;
	p_tim_handle->pTIMx->PSC = p_tim_handle->TIM_TimeBase.TIM_Prescaler;

	// se forza la recarga de los valores de ARR y PSC para que el
	// timer inicie con los valores correctos
	p_tim_handle->pTIMx->EGR |= (1<<TIM_EGR_UG);

	if(!(TIM_IS_BASIC_TIMER(p_tim_handle->pTIMx))){
		if(p_tim_handle->TIM_TimeBase.TIM_CounterMode == TIM_CouterMode_UP){
			p_tim_handle->pTIMx->CR1 &= ~(0x03 << TIM_CR1_CMS);
			p_tim_handle->pTIMx->CR1 &= ~(0x01 << TIM_CR1_DIR);
		}else if(p_tim_handle->TIM_TimeBase.TIM_CounterMode == TIM_CouterMode_DOWN){
			p_tim_handle->pTIMx->CR1 &= ~(0x03 << TIM_CR1_CMS);
			p_tim_handle->pTIMx->CR1 |= (0x01 << TIM_CR1_DIR);
		}else{

			p_tim_handle->pTIMx->CR1 &= ~(0x03 << TIM_CR1_CMS);
			p_tim_handle->pTIMx->CR1 |= (p_tim_handle->TIM_TimeBase.TIM_CounterMode << TIM_CR1_CMS);
		}
	}
}
void TIM_DeInit(TIM_RegDef_t *p_tim_reg){

}

void TIM_ICInit(TIM_Handle_t *p_tim_handle){
	uint16_t temp_CCMRx = 0;
	uint16_t temp_CCER = 0;

	ASSERT_FALSE(TIM_IS_BASIC_TIMER(p_tim_handle->pTIMx));


	// configuramos el prescaler y el periodo
	TIM_TimeBaseInit(p_tim_handle);

	if(p_tim_handle->TIM_InputCapture.TIM_Channel == TIM_CH1){
		// Reset bit CC1E para deshabilitar el canal
		p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC1E);

		temp_CCMRx = p_tim_handle->pTIMx->CCMR1;
		temp_CCER = p_tim_handle->pTIMx->CCER;

		// Configurar entrada en registro CCM1
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC1S);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR1_CC1S);

		temp_CCMRx &= ~(0x0F << TIM_CCMR1_IC1F);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR1_IC1F);

		temp_CCMRx &= ~(0x03 << TIM_CCMR1_IC1PSC);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR1_IC1PSC);

		temp_CCER &= ~((0x01 << TIM_CCER_CC1P) | (0x01 << TIM_CCER_CC1NP));
		if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC1NP = 0 y CC1P = 0
		} else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC1NP = 0 y CC1P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC1P);
		}else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC1NP = 1 y CC1P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC1P);
			temp_CCER |= (0x01 << TIM_CCER_CC1NP);
		}

		// Asignar valores a registros originales
		p_tim_handle->pTIMx->CCER = temp_CCER;
		p_tim_handle->pTIMx->CCMR1 = temp_CCMRx;

		// Habilitar el canal
		temp_CCER |= (0x01 << TIM_CCER_CC1E);

	}else if(p_tim_handle->TIM_InputCapture.TIM_Channel == TIM_CH2){
		ASSERT_TRUE(TIM_HAS_CH2(p_tim_handle->pTIMx));

		// Reset del bit CC1E para deshabilitar el canal
		p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC2E);

		temp_CCMRx = p_tim_handle->pTIMx->CCMR1;
		temp_CCER = p_tim_handle->pTIMx->CCER;

		// Configurar entrada en registro CCMR1
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC2S);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR1_CC2S);

		temp_CCMRx &= ~(0x0F << TIM_CCMR1_IC2F);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR1_IC2F);

		temp_CCMRx &= ~(0x03 << TIM_CCMR1_IC2PSC);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR1_IC2PSC);

		temp_CCER &= ~((0x01 << TIM_CCER_CC2P) | (0x01 << TIM_CCER_CC2NP));
		if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC1NP = 0 y CC1P = 0
		} else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC1NP = 0 y CC1P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC2P);
		}else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC1NP = 1 y CC1P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC2P);
			temp_CCER |= (0x01 << TIM_CCER_CC2NP);
		}

		// Asignar valores a registros originales
		p_tim_handle->pTIMx->CCER = temp_CCER;
		p_tim_handle->pTIMx->CCMR1 = temp_CCMRx;

		// Habilitar el canal
		temp_CCER |= (0x01 << TIM_CCER_CC2E);
	}else if(p_tim_handle->TIM_InputCapture.TIM_Channel == TIM_CH3){
		ASSERT_TRUE(TIM_HAS_CH3(p_tim_handle->pTIMx));
		// Reset del bit CC3E para deshabilitar el canal
		p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC3E);

		temp_CCMRx = p_tim_handle->pTIMx->CCMR2;
		temp_CCER = p_tim_handle->pTIMx->CCER;

		// Configurar entrada en registro CCM1
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC3S);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR2_CC3S);

		temp_CCMRx &= ~(0x0F << TIM_CCMR2_IC3F);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR2_IC3F);

		temp_CCMRx &= ~(0x03 << TIM_CCMR2_IC3PSC);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR2_IC3PSC);

		temp_CCER &= ~((0x01 << TIM_CCER_CC3P) | (0x01 << TIM_CCER_CC3NP));
		if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC3NP = 0 y CC3P = 0
		} else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC3NP = 0 y CC3P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC3P);
		}else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC3NP = 1 y CC31P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC3P);
			temp_CCER |= (0x01 << TIM_CCER_CC3NP);
		}

		// Asignar valores a registros originales
		p_tim_handle->pTIMx->CCER = temp_CCER;
		p_tim_handle->pTIMx->CCMR2 = temp_CCMRx;

		// Habilitar el canal
		temp_CCER |= (0x01 << TIM_CCER_CC3E);

	}else if(p_tim_handle->TIM_InputCapture.TIM_Channel == TIM_CH4){
		ASSERT_TRUE(TIM_HAS_CH4(p_tim_handle->pTIMx));
		// Reset del bit CC4E para deshabilitar el canal
		p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC4E);

		temp_CCMRx = p_tim_handle->pTIMx->CCMR2;
		temp_CCER = p_tim_handle->pTIMx->CCER;

		// Configurar entrada en registro CCM1
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC4S);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR2_CC4S);

		temp_CCMRx &= ~(0x0F << TIM_CCMR2_IC4F);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR2_IC4F);

		temp_CCMRx &= ~(0x03 << TIM_CCMR2_IC4PSC);
		temp_CCMRx |= (p_tim_handle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR2_IC4PSC);

		temp_CCER &= ~((0x01 << TIM_CCER_CC4P) | (0x01 << TIM_CCER_CC4NP));
		if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC3NP = 0 y CC3P = 0
		} else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC3NP = 0 y CC3P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC4P);
		}else if (p_tim_handle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC3NP = 1 y CC31P = 1
			temp_CCER |= (0x01 << TIM_CCER_CC4P);
			temp_CCER |= (0x01 << TIM_CCER_CC4NP);
		}

		// Asignar valores a registros originales
		p_tim_handle->pTIMx->CCER = temp_CCER;
		p_tim_handle->pTIMx->CCMR2 = temp_CCMRx;

		// Habilitar el canal
				temp_CCER |= (0x01 << TIM_CCER_CC4E);

	}

}

void TIM_Cmd(TIM_RegDef_t *p_tim_reg, uint8_t status){
	if(status == ENABLE){
		// empieza el conteo
		p_tim_reg->CR1 |= (1 << TIM_CR1_CEN);
	}else if(status == DISABLE){
		// deshabilita el conteo
		p_tim_reg->CR1 &= ~(1 << TIM_CR1_CEN);
	}
}

uint32_t TIM_GetCounter(TIM_RegDef_t *p_TIMx){
	return p_TIMx->CNT;
}
void TIM_SetCounter(TIM_RegDef_t *p_TIMx, uint32_t counter){
	p_TIMx->CNT = counter;
}
uint32_t TIM_GetCapture(TIM_RegDef_t *p_TIMx, TIM_Channels_t TIM_channel){
	ASSERT_FALSE(TIM_IS_BASIC_TIMER(p_TIMx));
	switch(TIM_channel){
		case(TIM_CH1):
			return p_TIMx->CCR1;
			break;

		case(TIM_CH2):
			ASSERT_TRUE(TIM_HAS_CH2(p_TIMx));
			return p_TIMx->CCR2;
			break;

		case(TIM_CH3):
			ASSERT_TRUE(TIM_HAS_CH3(p_TIMx));
			return p_TIMx->CCR3;
			break;

		case(TIM_CH4):
			ASSERT_TRUE(TIM_HAS_CH4(p_TIMx));
			return p_TIMx->CCR4;
			break;
	}
}

/**
 * @brief  Establece el valor de comparación para un canal del timer
 * @note   No válido para timers básicos (TIM6, TIM7)
 * @note   No todos los timers tienen todos los canales disponibles,
 *         se verificará con un assert si el canal no existe en el timer
 * @param  p_TIMx      puntero al registro base del timer
 * @param  TIM_channel canal del timer @ref TIM_Channels_t
 * @param  value       valor a cargar en el registro CCRx
 * @retval none
 */
void TIM_SetCompare(TIM_RegDef_t *p_TIMx, TIM_Channels_t TIM_channel, uint32_t value){
	ASSERT_FALSE(TIM_IS_BASIC_TIMER(p_TIMx));
	switch(TIM_channel){
		case(TIM_CH1):
			p_TIMx->CCR1 = value;
			break;

		case(TIM_CH2):
			ASSERT_TRUE(TIM_HAS_CH2(p_TIMx));
			p_TIMx->CCR2 = value;
			break;

		case(TIM_CH3):
			ASSERT_TRUE(TIM_HAS_CH3(p_TIMx));
			p_TIMx->CCR3 = value;
			break;

		case(TIM_CH4):
			ASSERT_TRUE(TIM_HAS_CH4(p_TIMx));
			p_TIMx->CCR4 = value;
			break;
	}
}

/**
 * @brief  Configura un canal del timer en modo Output Compare
 * @note   No válido para timers básicos (TIM6, TIM7)
 * @note   No todos los timers tienen todos los canales disponibles,
 *         se verificará con un assert si el canal no existe en el timer
 * @note   Esta función llama internamente a TIM_TimeBaseInit por lo que
 *         no es necesario llamarla por separado
 * @param  p_tim_handle  puntero al handle del timer, debe contener:
 *                       - pTIMx               puntero al registro base del timer
 *                       - TIM_TimeBase        configuración del prescaler y periodo
 *                       - TIM_OutputCompare   configuración del canal de salida:
 *                           - TIM_Channel     canal a configurar @ref TIM_Channels_t
 *                           - TIM_OCMode      modo de salida @ref TIM_OCMode_t
 *                           - TIM_OCPolarity  polaridad de la señal @ref TIM_OCPolarity_t
 *                           - TIM_Pulse       valor de comparacion del CCRx
 * @retval none
 */
void TIM_OC_Init(TIM_Handle_t *p_tim_handle)
{
    uint16_t temp_CCMRx = 0;
    uint16_t temp_CCER = 0;

    ASSERT_FALSE(TIM_IS_BASIC_TIMER(p_tim_handle->pTIMx));

    // configura el prescaler y el periodo
    TIM_TimeBaseInit(p_tim_handle);

    switch(p_tim_handle->TIM_OutputCompare.TIM_Channel)
    {
        case TIM_CH1:
            // deshabilitar el canal antes de configurar
            p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC1E);

            // leer registros en variables temporales
            temp_CCMRx = p_tim_handle->pTIMx->CCMR1;
            temp_CCER = p_tim_handle->pTIMx->CCER;

            // configurar canal 1 como salida (CC1S = 00)
            temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC1S);

            // limpiar y configurar el modo de salida OC1M
            temp_CCMRx &= ~(0x07 << TIM_CCMR1_OC1M);
            temp_CCMRx |= (p_tim_handle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR1_OC1M);

            // limpiar y configurar la polaridad del canal 1
            temp_CCER &= (0x01 << TIM_CCER_CC1P);
            temp_CCER &= (p_tim_handle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC1P);

            // habilitar el canal 1
            temp_CCER |= (0x01 << TIM_CCER_CC1E);

            // cargar el valor de comparacion
            p_tim_handle->pTIMx->CCR1 = p_tim_handle->TIM_OutputCompare.TIM_Pulse;

            // escribir los registros
            p_tim_handle->pTIMx->CCMR1 = temp_CCMRx;
            p_tim_handle->pTIMx->CCER = temp_CCER;
            break;
	    case TIM_CH2:
	    	ASSERT_TRUE(TIM_HAS_CH2(p_tim_handle->pTIMx));
	    	// deshabilitar el canal antes de configurar
			p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC2E);

			// leer registros en variables temporales
			temp_CCMRx = p_tim_handle->pTIMx->CCMR1;
			temp_CCER = p_tim_handle->pTIMx->CCER;

			// configurar canal 2 como salida (CC2S = 00)
			temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC2S);

			// limpiar y configurar el modo de salida OC2M
			temp_CCMRx &= ~(0x07 << TIM_CCMR1_OC2M);
			temp_CCMRx |= (p_tim_handle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR1_OC2M);

			// limpiar y configurar la polaridad del canal 2
			temp_CCER &= (0x01 << TIM_CCER_CC2P);
			temp_CCER &= (p_tim_handle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC2P);

			// habilitar el canal 2
			temp_CCER |= (0x01 << TIM_CCER_CC2E);

			// cargar el valor de comparacion
			p_tim_handle->pTIMx->CCR2 = p_tim_handle->TIM_OutputCompare.TIM_Pulse;

			// escribir los registros
			p_tim_handle->pTIMx->CCMR1 = temp_CCMRx;
			p_tim_handle->pTIMx->CCER = temp_CCER;
	        break;

	    case TIM_CH3:
	    	ASSERT_TRUE(TIM_HAS_CH3(p_tim_handle->pTIMx));
	    	ASSERT_TRUE(TIM_HAS_CH2(p_tim_handle->pTIMx));
			// deshabilitar el canal antes de configurar
			p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC3E);

			// leer registros en variables temporales
			temp_CCMRx = p_tim_handle->pTIMx->CCMR2;
			temp_CCER = p_tim_handle->pTIMx->CCER;

			// configurar canal 3 como salida (CC2S = 00)
			temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC3S);

			// limpiar y configurar el modo de salida OC3M
			temp_CCMRx &= ~(0x07 << TIM_CCMR2_OC3M);
			temp_CCMRx |= (p_tim_handle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR2_OC3M);

			// limpiar y configurar la polaridad del canal 2
			temp_CCER &= (0x01 << TIM_CCER_CC3P);
			temp_CCER &= (p_tim_handle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC3P);

			// habilitar el canal 3
			temp_CCER |= (0x01 << TIM_CCER_CC3E);

			// cargar el valor de comparacion
			p_tim_handle->pTIMx->CCR3 = p_tim_handle->TIM_OutputCompare.TIM_Pulse;

			// escribir los registros
			p_tim_handle->pTIMx->CCMR2 = temp_CCMRx;
			p_tim_handle->pTIMx->CCER = temp_CCER;
	        break;

	    case TIM_CH4:
	    	ASSERT_TRUE(TIM_HAS_CH4(p_tim_handle->pTIMx));
	    	ASSERT_TRUE(TIM_HAS_CH2(p_tim_handle->pTIMx));
			// deshabilitar el canal antes de configurar
			p_tim_handle->pTIMx->CCER &= ~(0x01 << TIM_CCER_CC4E);

			// leer registros en variables temporales
			temp_CCMRx = p_tim_handle->pTIMx->CCMR2;
			temp_CCER = p_tim_handle->pTIMx->CCER;

			// configurar canal 4 como salida (CC2S = 00)
			temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC4S);

			// limpiar y configurar el modo de salida OC2M
			temp_CCMRx &= ~(0x07 << TIM_CCMR2_OC4M);
			temp_CCMRx |= (p_tim_handle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR2_OC4M);

			// limpiar y configurar la polaridad del canal 4
			temp_CCER &= (0x01 << TIM_CCER_CC4P);
			temp_CCER &= (p_tim_handle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC4P);

			// habilitar el canal 4
			temp_CCER |= (0x01 << TIM_CCER_CC4E);

			// cargar el valor de comparacion
			p_tim_handle->pTIMx->CCR4 = p_tim_handle->TIM_OutputCompare.TIM_Pulse;

			// escribir los registros
			p_tim_handle->pTIMx->CCMR2 = temp_CCMRx;
			p_tim_handle->pTIMx->CCER = temp_CCER;
	        break;

	    default:
	        break;
	}
}


uint8_t TIM_GetITStatus(TIM_RegDef_t *p_reg_def, uint16_t tim_it){
	uint16_t it_status = 0;
	uint16_t it_enable = 0;

	// Verifica que la bandera esté en 1
	it_status = (p_reg_def->SR & (1 << tim_it));

	// verifica que la interrupción esté habilitada
	it_enable = (p_reg_def->DIER & (1 << tim_it));

	if(it_status && it_enable){
		return ENABLE;
	}else{
		return DISABLE;
	}
}

/**
 * @brief  Selecciona la fuente de trigger de entrada (ITR) para el timer en modo esclavo.
 *
 * @details
 * Configura el campo TS (Trigger Selection) del registro SMCR. Este campo
 * determina qué señal actúa como disparador externo o interno para sincronizar
 * el timer cuando opera como esclavo.
 *
 * Operación sobre el registro SMCR:
 * @code
 *   SMCR[6:4] (TS) = trigger
 * @endcode
 *
 * @param[in]  pTIMx    Puntero al timer. Debe soportar funcionalidad Master/Slave.
 * @param[in]  trigger  Fuente de trigger deseada (@ref TIM_Trigger_t).
 *                      Valores típicos:
 *                      - ITR0..ITR3 : trigger interno desde otro timer
 *                      - TI1F_ED    : flanco del canal 1 filtrado
 *                      - TI1FP1/2   : señal filtrada de canal 1 o 2
 *                      - ETRF       : trigger externo filtrado
 *
 * @pre  El timer referenciado por @p pTIMx debe tener funcionalidad
 *       Master/Slave (verificado por ASSERT_TRUE).
 *
 * @note  Esta función solo configura la fuente; el modo esclavo debe
 *        activarse por separado con TIM_SlaveMode().
 *
 * @see  TIM_SlaveMode()
 * @see  STM32F446RE Reference Manual — registro SMCR, bits TS[6:4]
 */

void TIM_InputTrigger(TIM_RegDef_t *pTIMx, TIM_Trigger_t trigger)
{
	uint16_t temp_smcr;

	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));

	temp_smcr = pTIMx->SMCR;

	temp_smcr &= ~(0x07 << TIM_SMCR_TS);
	temp_smcr |= (trigger << TIM_SMCR_TS);

	 pTIMx->SMCR = temp_smcr;
}

/**
 * @brief  Configura el modo de operación esclavo del timer.
 *
 * @details
 * Escribe el campo SMS (Slave Mode Selection) del registro SMCR para
 * definir cómo reacciona el timer ante la señal de trigger seleccionada
 * con TIM_InputTrigger().
 *
 * Operación sobre el registro SMCR:
 * @code
 *   SMCR[2:0] (SMS) = mode
 * @endcode
 *
 * @param[in]  pTIMx  Puntero al timer. Debe soportar funcionalidad Master/Slave.
 * @param[in]  mode   Modo esclavo deseado (@ref TIM_Slave_t).
 *                    Valores típicos:
 *                    - SMS_DISABLED   : modo esclavo deshabilitado (timer libre)
 *                    - SMS_ENCODER1/2/3 : modos de interfaz encoder
 *                    - SMS_RESET      : el trigger reinicia el contador (CNT = 0)
 *                    - SMS_GATED      : el contador corre solo mientras trigger=HIGH
 *                    - SMS_TRIGGER    : el trigger habilita el contador una vez
 *                    - SMS_EXTERNAL   : clock externo desde el pin trigger
 *
 * @pre  El timer referenciado por @p pTIMx debe tener funcionalidad
 *       Master/Slave (verificado por ASSERT_TRUE).
 * @pre  Configurar previamente la fuente de trigger con TIM_InputTrigger().
 *
 * @see  TIM_InputTrigger()
 * @see  STM32F446RE Reference Manual — registro SMCR, bits SMS[2:0]
 */
void TIM_SlaveMode(TIM_RegDef_t *pTIMx, TIM_Slave_t mode)
{
	uint16_t temp_smcr;
	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));

	temp_smcr = pTIMx->SMCR;

	temp_smcr &= ~(0x07 << TIM_SMCR_SMS);
	temp_smcr |= (mode << TIM_SMCR_SMS);

	pTIMx->SMCR = temp_smcr;
}

/**
 * @brief  Configura la señal de salida del trigger maestro (TRGO).
 *
 * @details
 * Escribe el campo MMS (Master Mode Selection) del registro CR2 para
 * definir qué evento interno del timer se enruta hacia la salida TRGO.
 * Esta señal puede utilizarse para sincronizar otros timers esclavos,
 * disparar conversiones ADC o activar el DAC.
 *
 * Operación sobre el registro CR2:
 * @code
 *   CR2[6:4] (MMS) = output
 * @endcode
 *
 * @param[in]  pTIMx   Puntero al timer. Debe soportar funcionalidad Master/Slave.
 * @param[in]  output  Evento a enrutar como TRGO (@ref TIM_MasterOutput_t).
 *                     Valores típicos:
 *                     - MMS_RESET      : UG (update generation) como TRGO
 *                     - MMS_ENABLE     : CNT_EN (habilitación del contador)
 *                     - MMS_UPDATE     : evento Update (UEV) — útil para ADC/DAC
 *                     - MMS_OC1        : pulso en toggle del canal 1
 *                     - MMS_OC1REF/2/3/4 : señal de referencia de cada canal
 *
 * @pre  El timer referenciado por @p pTIMx debe tener funcionalidad
 *       Master/Slave (verificado por ASSERT_TRUE).
 *
 * @see  TIM_SlaveMode()
 * @see  TIM_InputTrigger()
 * @see  STM32F446RE Reference Manual — registro CR2, bits MMS[6:4]
 */
void TIM_MasterTriggerOutput(TIM_RegDef_t *pTIMx, TIM_MasterOutput_t output)
{
	uint16_t temp_cr2;

	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));

	temp_cr2 = pTIMx->CR2;

	temp_cr2 &= ~(0x07 << TIM_CR2_MMS);
	temp_cr2 |= (output << TIM_CR2_MMS);

	pTIMx->CR2 = temp_cr2;
}



void TIM_ClearITPendingBit(TIM_RegDef_t *p_reg_def, uint16_t tim_it){
	// limpia la bandera, no afecta los 1 porque las banderas se activan
	// por hardware
	p_reg_def->SR = ~(1 << tim_it);
}
void TIM_IRQHandler(TIM_Handle_t *p_tim_handle){
	if(TIM_GetITStatus(p_tim_handle->pTIMx,TIM_SR_UIF)){
		// limpia la bandera
		TIM_ClearITPendingBit(p_tim_handle->pTIMx, TIM_SR_UIF);
		// evento de aplicacion
		TIM_EventCallback(p_tim_handle, TIM_EVENT_UI);
	}else if(TIM_GetITStatus(p_tim_handle->pTIMx,TIM_SR_CC1IF)){
		// limpia la bandera
		TIM_ClearITPendingBit(p_tim_handle->pTIMx, TIM_SR_CC1IF);
		// evento de aplicacion
		TIM_EventCallback(p_tim_handle, TIM_EVENT_CC1I);
	}else if(TIM_GetITStatus(p_tim_handle->pTIMx,TIM_SR_CC2IF)){
		// limpia la bandera
		TIM_ClearITPendingBit(p_tim_handle->pTIMx, TIM_SR_CC2IF);
		// evento de aplicacion
		TIM_EventCallback(p_tim_handle, TIM_EVENT_CC2I);
	}else if(TIM_GetITStatus(p_tim_handle->pTIMx,TIM_SR_CC3IF)){
		// limpia la bandera
		TIM_ClearITPendingBit(p_tim_handle->pTIMx, TIM_SR_CC3IF);
		// evento de aplicacion
		TIM_EventCallback(p_tim_handle, TIM_EVENT_CC3I);
	}else if(TIM_GetITStatus(p_tim_handle->pTIMx,TIM_SR_CC4IF)){
		// limpia la bandera
		TIM_ClearITPendingBit(p_tim_handle->pTIMx, TIM_SR_CC4IF);
		// evento de aplicacion
		TIM_EventCallback(p_tim_handle, TIM_EVENT_CC4I);
	}

}

__attribute__ ((weak)) void TIM_EventCallback(TIM_Handle_t *p_tim_handle, TIM_Event_t event){

}

