#include "BSP_USART.h"

USART_Handle_t USART2_handle = {0};

void USART2_Setup(void)
{
	USART2_handle.pUSARTx = USART2;
	USART2_handle.USART_Config.Baud = USART_BAUD_9600;
	USART2_handle.USART_Config.FlowControl = USART_FLOWCONTROL_NONE;
	USART2_handle.USART_Config.Mode = USART_MODE_TXRX;
	USART2_handle.USART_Config.Over8 = USART_OVERS_8;
	USART2_handle.USART_Config.Parity = USART_PARITY_OFF;
	USART2_handle.USART_Config.StopBits = USART_STOPBIT_1;
	USART2_handle.USART_Config.WordLength = USART_8BITS_LEN;

	USART_Init(&USART2_handle);
}
