#include "stm32f446xx_spi.h"

volatile uint8_t rx_complete = 0;
__attribute__((weak)) SPI_Handle_t SPI1_handle = {0};
__attribute__((weak)) SPI_Handle_t SPI2_handle = {0};
__attribute__((weak)) SPI_Handle_t SPI3_handle = {0};
__attribute__((weak)) SPI_Handle_t SPI4_handle = {0};

void SPI_ClkCtrl(SPI_RegDef_t *pSPIx, uint8_t status)
{
	if(status == ENABLE)
	{
	    switch((uint32_t) pSPIx)
	    {
	        case((uint32_t)SPI1):
	            SPI1_EN_CLK();
	            break;

	        case((uint32_t)SPI2):
	            SPI2_EN_CLK();
	            break;

	        case((uint32_t)SPI3):
	            SPI3_EN_CLK();
	            break;

	        case((uint32_t)SPI4):
	            SPI4_EN_CLK();
	            break;
	    }
	}else if(status == DISABLE)
	{
	    switch((uint32_t) pSPIx){
	        case((uint32_t)SPI1):
	            SPI1_DIS_CLK();
	            break;

	        case((uint32_t)SPI2):
	            SPI2_DIS_CLK();
	            break;

	        case((uint32_t)SPI3):
	            SPI3_DIS_CLK();
	            break;

	        case((uint32_t)SPI4):
	            SPI4_DIS_CLK();
	            break;
	    }
	}
}
void SPI_Init(SPI_Handle_t *SPI_Handle)
{
	uint32_t temp_CR1;

	SPI_ClkCtrl(SPI_Handle->pSPIx, ENABLE);

	SPI_Handle->pSPIx->SPI_CR1 &= ~(0x01 << SPI_CR1_SPE);

	temp_CR1 = SPI_Handle->pSPIx->SPI_CR1;
	temp_CR1 &= ~((1 << SPI_CR1_MSTR) | (0x07 << SPI_CR1_BR) | (0x01 << SPI_CR1_DFF)\
					| (0x01 << SPI_CR1_CPHA)|(0x01 << SPI_CR1_CPOL) |(0x01 << SPI_CR1_RXONLY)\
					| (0x01 << SPI_CR1_BIDIOE) | (0x01 << SPI_CR1_BIDIMODE)|(0x01 << SPI_CR1_SSM));

	temp_CR1 |= (SPI_Handle->SPIConfig.DeviceMode << SPI_CR1_MSTR);

	temp_CR1 |= (SPI_Handle->SPIConfig.DataFrmat << SPI_CR1_DFF);

	temp_CR1 |= (SPI_Handle->SPIConfig.CPHA << SPI_CR1_CPHA);

	temp_CR1 |= (SPI_Handle->SPIConfig.CPOL << SPI_CR1_CPOL);

	temp_CR1 |= (SPI_Handle->SPIConfig.Prescaler << SPI_CR1_BR);

	temp_CR1 |= (SPI_Handle->SPIConfig.NSS << SPI_CR1_SSM);

	temp_CR1 |= (0x01 << SPI_CR1_SSI);

	switch(SPI_Handle->SPIConfig.BusConfig)
	{
		case(SPI_BusConfig_FullDuplex):
			/* la configuración ya está seteada
			 * BIDIMODE = 0 RXONLY = 0 BIDIOE = 0*/
			break;
		case(SPI_BusConfig_HalfDuplex):
			temp_CR1 |= (0x01 << SPI_CR1_BIDIMODE);
			break;
		case(SPI_BusConfig_SimplexRx):
		temp_CR1 |= (0x01 << SPI_CR1_RXONLY);
		break;

	}
	SPI_Handle->pSPIx->SPI_CR1 = temp_CR1;
	//Limpia interrupciones
	SPI_Handle->pSPIx->SPI_CR2 &= ~(0x07 << SPI_CR2_ERRIE);

}

void SPI_Int_Cmd(SPI_Handle_t *SPI_Handle,SPI_Interrupts_t SPI_Int, uint8_t status)
{
	if(status == ENABLE)
	{
		switch(SPI_Int)
		{
			case(SPI_Int_Tx):
				SPI_Handle->pSPIx->SPI_CR2 |= (0x01 << SPI_CR2_TXEIE);
				break;
			case(SPI_Int_Rx):
				SPI_Handle->pSPIx->SPI_CR2 |= (0x01 << SPI_CR2_RXNEIE);
				break;
			case(SPI_Int_Err):
				SPI_Handle->pSPIx->SPI_CR2 |= (0x01 << SPI_CR2_ERRIE);
				break;

		}
	}else if(status == DISABLE)
	{
		switch(SPI_Int)
		{
		    case(SPI_Int_Tx):
		        SPI_Handle->pSPIx->SPI_CR2 &= ~(0x01 << SPI_CR2_TXEIE);
		        break;
		    case(SPI_Int_Rx):
		        SPI_Handle->pSPIx->SPI_CR2 &= ~(0x01 << SPI_CR2_RXNEIE);
		        break;
		    case(SPI_Int_Err):
		        SPI_Handle->pSPIx->SPI_CR2 &= ~(0x01 << SPI_CR2_ERRIE);
		        break;
		}

	}
}
void SPI_Deinit(SPI_Handle_t *SPI_Handle)
{
	switch((uint32_t) SPI_Handle->pSPIx)
	{
	    case((uint32_t)SPI1):
	        SPI1_RESET();
	        break;

	    case((uint32_t)SPI2):
	        SPI2_RESET();
	        break;

	    case((uint32_t)SPI3):
	        SPI3_RESET();
	        break;

	    case((uint32_t)SPI4):
	        SPI4_RESET();
	        break;
	}
}

void SPI_Cmd(SPI_Handle_t *SPI_Handle, uint8_t status)
{
	if(status == ENABLE)
		SPI_Handle->pSPIx->SPI_CR1 |= (0x01 << SPI_CR1_SPE);
	else if(status == DISABLE)
		SPI_Handle->pSPIx->SPI_CR1 &= ~(0x01 << SPI_CR1_SPE);
}
void SPI_SendData(SPI_Handle_t *SPI_Handle, uint8_t *pTxBuffer, uint32_t len)
{

	while(len)
	{
		while(!IS_SPI_TX_BUFF_EMPTY(SPI_Handle->pSPIx));

		if(SPI_Handle->SPIConfig.DataFrmat)
		{
			// 16 bits format
			SPI_Handle->pSPIx->SPI_DR = *((uint16_t *)pTxBuffer);
			len -= 2;
			pTxBuffer += 2;

		}else
		{
			// 8 bit format
			SPI_Handle->pSPIx->SPI_DR = *pTxBuffer;
			// AGREGAR: Esperar y leer RXNE

			len--;
			pTxBuffer++;
		}

	}
	while(SPI_Handle->pSPIx->SPI_SR & (1 << SPI_SR_BSY)); // SPI en comunicacion o tx no vacio

}
void SPI_ReceiveData(SPI_Handle_t *SPI_Handle, uint8_t *pRxBuffer, uint32_t len)
{

	while(len)
	{
		while(!IS_SPI_RX_BUFF_FULL(SPI_Handle->pSPIx));

		if(SPI_Handle->SPIConfig.DataFrmat)
		{
			// 16 bits format
			*((uint16_t *)pRxBuffer) = SPI_Handle->pSPIx->SPI_DR;
			len -= 2;
			pRxBuffer += 2;

		}else
		{
			// 8 bit format
			*pRxBuffer = SPI_Handle->pSPIx->SPI_DR;
			// AGREGAR: Esperar y leer RXNE
			len--;
			pRxBuffer++;
		}

	}
	while(SPI_Handle->pSPIx->SPI_SR & (1 << SPI_SR_BSY)); // SPI en comunicacion o tx no vacio

}

uint8_t SPI_SendDataIT(SPI_Handle_t *SPI_Handle, uint8_t *pTxBuffer, uint32_t len)
{
	uint8_t state = SPI_Handle->TxState;
	if(state != SPI_TX_BUSY)
	{
		SPI_Handle->pTxBuffer = pTxBuffer;

		SPI_Handle->TxLen = len;

		SPI_Handle->TxState = SPI_TX_BUSY;

		SPI_Int_Cmd(SPI_Handle, SPI_Int_Tx, ENABLE);
	}
	return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *SPI_Handle, uint8_t *pRxBuffer, uint32_t len)
{
	uint8_t state = SPI_Handle->RxState;
		if(state != SPI_RX_BUSY)
		{
			SPI_Handle->pRxBuffer = pRxBuffer;

			SPI_Handle->RxLen = len;

			SPI_Handle->RxState = SPI_RX_BUSY;

			SPI_Int_Cmd(SPI_Handle, SPI_Int_Rx, ENABLE);
		}
		return state;
}

void SPI_IRQHandler(SPI_Handle_t *SPI_Handle)
{
	// Int por tx
	if((SPI_Handle->pSPIx->SPI_CR2 & (0x01 << SPI_CR2_TXEIE)) && \
			(SPI_Handle->pSPIx->SPI_SR & (0x01 << SPI_SR_TXE)))
	{
		if(SPI_Handle->SPIConfig.DataFrmat)
		{
			// 16 bits format
			SPI_Handle->pSPIx->SPI_DR = *((uint16_t *)SPI_Handle->pTxBuffer);
			SPI_Handle->TxLen -= 2;
			SPI_Handle->pTxBuffer += 2;

		}else
		{
			// 8 bit format
			SPI_Handle->pSPIx->SPI_DR = *SPI_Handle->pTxBuffer;
			SPI_Handle->TxLen --;
			SPI_Handle->pTxBuffer++;
		}
		if(SPI_Handle->TxLen == 0)
		{
			// Close SPI communication and inform app that tx is over
			SPI_Int_Cmd(SPI_Handle, SPI_Int_Tx, DISABLE);
			SPI_Handle->pTxBuffer = NULL;
			SPI_Handle->TxLen = 0;
			SPI_Handle->TxState =  SPI_READY;

			SPI_ApplicationEventCallback(SPI_Handle,SPI_EVENT_TX_CMPLT);
		}
	}
	// Int por rx
	else if((SPI_Handle->pSPIx->SPI_CR2 & (0x01 << SPI_CR2_RXNEIE)) && \
				(SPI_Handle->pSPIx->SPI_SR & (0x01 << SPI_SR_RXNE)))
	{
		if(SPI_Handle->SPIConfig.DataFrmat)
		{
			// 16 bits format
			*((uint16_t *)SPI_Handle->pRxBuffer) = SPI_Handle->pSPIx->SPI_DR;
			SPI_Handle->RxLen -= 2;
			SPI_Handle->pRxBuffer += 2;

		}else
		{
			// 8 bit format
			*SPI_Handle->pRxBuffer = SPI_Handle->pSPIx->SPI_DR;
			// AGREGAR: Esperar y leer RXNE
			SPI_Handle->RxLen--;
			SPI_Handle->pRxBuffer++;
		}
		if(SPI_Handle->RxLen == 0)
		{
			// Close SPI communication and inform app that tx is over
			SPI_Int_Cmd(SPI_Handle, SPI_Int_Rx, DISABLE);
			SPI_Handle->pRxBuffer = NULL;
			SPI_Handle->RxLen = 0;
			SPI_Handle->RxState =  SPI_READY;

			SPI_ApplicationEventCallback(SPI_Handle,SPI_EVENT_RX_CMPLT);
		}

	}
	else if((SPI_Handle->pSPIx->SPI_CR2 & (0x01 << SPI_CR2_ERRIE)))
	{
		uint32_t sr = SPI_Handle->pSPIx->SPI_SR;

		// Frame error (bit 8)
		if(sr & (0x01 << 8))
		{
			// Se limpia solo al leer SR
			volatile uint8_t dummy = SPI_Handle->pSPIx->SPI_SR;
			(void)dummy;
			SPI_ApplicationEventCallback(SPI_Handle,SPI_EVENT_FRE_ERR);
		}

		// Overrun error (bit 6)
		if(sr & (0x01 << 6))
		{
			if(SPI_Handle->TxState != SPI_TX_BUSY)
			{
				// se limpia leyendo DR y despues leyendo SR
				volatile uint8_t dummy = SPI_Handle->pSPIx->SPI_DR;
				dummy = SPI_Handle->pSPIx->SPI_SR;
				(void)dummy;
				SPI_ApplicationEventCallback(SPI_Handle,SPI_EVENT_OVR_ERR);
			}
		}

		// Mode fault (bit 5)
		if(sr & (0x01 << 5))
		{
			// limpiar leyendo SR luego escribir SPE=0
			volatile uint8_t dummy = SPI_Handle->pSPIx->SPI_SR;
			(void)dummy;
			SPI_Handle->pSPIx->SPI_CR1 &= ~(0x01 << SPI_CR1_SPE);
			SPI_ApplicationEventCallback(SPI_Handle,SPI_EVENT_MODF_ERR);
		}

		// CRC error (bit 4)
		if(sr & (0x01 << 4))
		{
			// limpiar escribiendo CRCERR=0 directamente
			SPI_Handle->pSPIx->SPI_SR &= ~(0x01 << 4);
			SPI_ApplicationEventCallback(SPI_Handle,SPI_EVENT_CRC_ERR);
		}

	}
}

void SPI1_IRQHandler(void)
{
	SPI_IRQHandler(&SPI1_handle);
}

void SPI2_IRQHandler(void)
{
	SPI_IRQHandler(&SPI2_handle);
}

void SPI3_IRQHandler(void)
{
	SPI_IRQHandler(&SPI3_handle);
}

void SPI4_IRQHandler(void)
{
	SPI_IRQHandler(&SPI4_handle);
}
__attribute__((weak)) void SPI_ApplicationEventCallback(SPI_Handle_t *SPI_handle, uint8_t SPI_event)
{
	if(SPI_event == SPI_EVENT_RX_CMPLT)
	{
		rx_complete = 1;
	}

}

