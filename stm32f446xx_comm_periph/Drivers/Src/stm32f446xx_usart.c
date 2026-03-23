#include "stm32f446xx_usart.h"

__attribute__((weak)) USART_Handle_t USART1_handle = {0};
__attribute__((weak)) USART_Handle_t USART2_handle = {0};
__attribute__((weak)) USART_Handle_t USART3_handle = {0};
__attribute__((weak)) USART_Handle_t UART4_handle = {0};
__attribute__((weak)) USART_Handle_t UART5_handle = {0};
__attribute__((weak)) USART_Handle_t USART6_handle = {0};

void USART_ClkCtrl(USART_RegDef_t *pUSARTx, uint8_t status)
{
	if(status == ENABLE)
	{
		switch((uint32_t) pUSARTx)
		{
			case((uint32_t)USART1):
				USART1_EN_CLK();
				break;

			case((uint32_t)USART2):
				USART2_EN_CLK();
				break;

			case((uint32_t)USART3):
				USART3_EN_CLK();
				break;

			case((uint32_t)UART4):
				UART4_EN_CLK();
				break;

			case((uint32_t)UART5):
				UART5_EN_CLK();
				break;

			case((uint32_t)USART6):
				USART6_EN_CLK();
				break;
		}
	}
	else if(status == DISABLE)
	{
		switch((uint32_t) pUSARTx)
		{
			case((uint32_t)USART1):
				USART1_DIS_CLK();
				break;

			case((uint32_t)USART2):
				USART2_DIS_CLK();
				break;

			case((uint32_t)USART3):
				USART3_DIS_CLK();
				break;

			case((uint32_t)UART4):
				UART4_DIS_CLK();
				break;

			case((uint32_t)UART5):
				UART5_DIS_CLK();
				break;

			case((uint32_t)USART6):
				USART6_DIS_CLK();
				break;

		}
	}
}
void USART_Deinit(USART_RegDef_t *pUSARTx)
{
	switch((uint32_t) pUSARTx)
	{
		case((uint32_t)USART1):
			USART1_RESET();
			break;

		case((uint32_t)USART2):
			USART2_RESET();
			break;

		case((uint32_t)USART3):
			USART3_RESET();
			break;

		case((uint32_t)UART4):
			UART4_RESET();
			break;

		case((uint32_t)UART5):
			UART5_RESET();
			break;

		case((uint32_t)USART6):
			USART6_RESET();
			break;
	}
}


void USART_Init(USART_Handle_t *pUSARTHandle)
{
	USART_ClkCtrl(pUSARTHandle->pUSARTx, ENABLE);
	uint32_t CRx_temp;
	CRx_temp = pUSARTHandle->pUSARTx->CR1;

	CRx_temp &= ~((0x01 << USART_CR1_RE) | (0x01 << USART_CR1_TE) | (0x01 << USART_CR1_PS)\
				| (0x01 << USART_CR1_PCE) | (0x01 << USART_CR1_M)| (0x01 << USART_CR1_OVER8));

	if((pUSARTHandle->USART_Config.Mode == USART_MODE_TX_ONLY) || (pUSARTHandle->USART_Config.Mode == USART_MODE_TXRX))
		CRx_temp |= (0x01 << USART_CR1_TE);
	if((pUSARTHandle->USART_Config.Mode == USART_MODE_RX_ONLY) || (pUSARTHandle->USART_Config.Mode == USART_MODE_TXRX))
		CRx_temp |= (0x01 << USART_CR1_RE);

	if(pUSARTHandle->USART_Config.Parity != USART_PARITY_OFF)
	{
		CRx_temp |= (0x01 << USART_CR1_PCE);
		CRx_temp |= (pUSARTHandle->USART_Config.Parity << USART_CR1_PS);
	}
	CRx_temp |= (pUSARTHandle->USART_Config.WordLength << USART_CR1_M);

	CRx_temp |= (pUSARTHandle->USART_Config.Over8 << USART_CR1_OVER8);

	pUSARTHandle->pUSARTx->CR1 = CRx_temp;

	pUSARTHandle->pUSARTx->CR2 &= ~(0x03 << USART_CR2_STOP);
	pUSARTHandle->pUSARTx->CR2 |= (pUSARTHandle->USART_Config.StopBits << USART_CR2_STOP);

	CRx_temp = pUSARTHandle->pUSARTx->CR3;
	CRx_temp &= ~((0x01 << USART_CR3_CTSE)|(0x01 << USART_CR3_RTSE));
	if((pUSARTHandle->USART_Config.FlowControl == USART_FLOWCONTROL_CTS) || (pUSARTHandle->USART_Config.FlowControl == USART_FLOWCONTROL_RTS_CTS))
		CRx_temp |= (0x01 << USART_CR3_CTSE);
	if((pUSARTHandle->USART_Config.FlowControl == USART_FLOWCONTROL_RTS) || (pUSARTHandle->USART_Config.FlowControl == USART_FLOWCONTROL_RTS_CTS))
		CRx_temp |= (0x01 << USART_CR3_RTSE);

	pUSARTHandle->pUSARTx->CR3 = CRx_temp;

	USART_SetBaudRate(pUSARTHandle);
}
void USART_SetBaudRate(USART_Handle_t *pUSARTHandle)
{
	uint32_t pclkx;
	uint32_t usartdiv;
	uint32_t m_part;
	uint32_t f_part;

	if((pUSARTHandle->pUSARTx == USART1) || (pUSARTHandle->pUSARTx == USART6))
		pclkx = RCC_GetAPB2CLK();
	else
		pclkx = RCC_GetAPB1CLK();


	if(pUSARTHandle->USART_Config.Over8 == USART_OVERS_8)
	    usartdiv = (uint32_t)((uint64_t)pclkx * 1000 / (8 * pUSARTHandle->USART_Config.Baud));
	else if(pUSARTHandle->USART_Config.Over8 == USART_OVERS_16)
	    usartdiv = (uint32_t)((uint64_t)pclkx * 1000 / (16 * pUSARTHandle->USART_Config.Baud));

	m_part = usartdiv / 1000;
	f_part = (usartdiv % 1000) * (8*(2-pUSARTHandle->USART_Config.Over8));
	f_part = (f_part + 500) / 1000;

	pUSARTHandle->pUSARTx->BRR &= ~(0x7FFF);
	pUSARTHandle->pUSARTx->BRR |= (f_part);
	pUSARTHandle->pUSARTx->BRR |= (m_part << USART_BRR_DIV_MANT);
}
void USART_Cmd(USART_Handle_t *pUSARTHandle, uint8_t status)
{
	if(status == ENABLE)
		pUSARTHandle->pUSARTx->CR1 |= (0x01 <<USART_CR1_UE);
	else if(status == DISABLE)
		pUSARTHandle->pUSARTx->CR1 &= ~(0x01 <<USART_CR1_UE);
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t len)
{
	// Limpiar TC antes de empezar
	pUSARTHandle->pUSARTx->SR &= ~(0x01 << USART_SR_TC);
	while(len)
	{
		pUSARTHandle->pUSARTx->DR = *pTxBuffer;
		while(!USART_GET_TXE_FLAG(pUSARTHandle->pUSARTx));
		pTxBuffer++;
		len--;

	}
	while(!USART_GET_TC_FLAG(pUSARTHandle->pUSARTx));
}

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t len)
{
	while(len)
	{
		while(!USART_GET_RXNE_FLAG(pUSARTHandle->pUSARTx));

		if(pUSARTHandle->USART_Config.WordLength == USART_9BITS_LEN)
		{
			if(pUSARTHandle->USART_Config.Parity != USART_PARITY_OFF)
			{
				//paridad, ignoria el primer bit
				*(pRxBuffer) = (pUSARTHandle->pUSARTx->DR & 0x0FF);
				pRxBuffer++;
			}
			else
			{
				// no paridad
				*((uint16_t*)pRxBuffer) = (uint16_t)(pUSARTHandle->pUSARTx->DR & 0x01FF);
				pRxBuffer +=2;
			}
		}

		else
		{
			if(pUSARTHandle->USART_Config.Parity != USART_PARITY_OFF)
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0x7F);
				pRxBuffer++;
			}
			else
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0xFF);
				pRxBuffer++;
			}
		}
		len--;

	}
}
