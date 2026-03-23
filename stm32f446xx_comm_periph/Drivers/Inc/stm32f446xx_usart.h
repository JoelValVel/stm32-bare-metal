/*
 * stm32f446xx_usart.h
 *
 *  Created on: 20 mar 2026
 *      Author: erjo_
 */

#ifndef INC_STM32F446XX_USART_H_
#define INC_STM32F446XX_USART_H_

#include "stm32f446xx.h"
#include "stm32f446xx_rcc.h"

#define USART_MODE_TX_ONLY	0
#define USART_MODE_RX_ONLY	1
#define USART_MODE_TXRX		2

#define USART_PARITY_ODD	1
#define USART_PARITY_EVEN	0
#define USART_PARITY_OFF	2

#define USART_8BITS_LEN		0
#define USART_9BITS_LEN		1

#define USART_STOPBIT_1		0
#define USART_STOPBIT_0_5	1
#define USART_STOPBIT_2		2
#define USART_STOPBIT_1_5	3

#define USART_FLOWCONTROL_NONE		0
#define USART_FLOWCONTROL_CTS		1
#define USART_FLOWCONTROL_RTS		2
#define USART_FLOWCONTROL_RTS_CTS	3

#define USART_OVERS_8				1
#define USART_OVERS_16				0


#define USART_BAUD_1200         1200
#define USART_BAUD_2400         2400
#define USART_BAUD_9600         9600
#define USART_BAUD_19200        19200
#define USART_BAUD_38400        38400
#define USART_BAUD_57600        57600
#define USART_BAUD_115200       115200
#define USART_BAUD_230400       230400
#define USART_BAUD_460800       460800
#define USART_BAUD_921600       921600
#define USART_BAUD_2M			2000000
#define USART_BAUD_3M			3000000

#define USART_GET_PE_FLAG(pUSARTx)      ((pUSARTx)->SR & (0x01 << USART_SR_PE))
#define USART_GET_FE_FLAG(pUSARTx)      ((pUSARTx)->SR & (0x01 << USART_SR_FE))
#define USART_GET_NF_FLAG(pUSARTx)      ((pUSARTx)->SR & (0x01 << USART_SR_NF))
#define USART_GET_ORE_FLAG(pUSARTx)     ((pUSARTx)->SR & (0x01 << USART_SR_ORE))
#define USART_GET_IDLE_FLAG(pUSARTx)    ((pUSARTx)->SR & (0x01 << USART_SR_IDLE))
#define USART_GET_RXNE_FLAG(pUSARTx)    ((pUSARTx)->SR & (0x01 << USART_SR_RXNE))
#define USART_GET_TC_FLAG(pUSARTx)      ((pUSARTx)->SR & (0x01 << USART_SR_TC))
#define USART_GET_TXE_FLAG(pUSARTx)     ((pUSARTx)->SR & (0x01 << USART_SR_TXE))
#define USART_GET_LBD_FLAG(pUSARTx)     ((pUSARTx)->SR & (0x01 << USART_SR_LBD))
#define USART_GET_CTS_FLAG(pUSARTx)     ((pUSARTx)->SR & (0x01 << USART_SR_CTS))

typedef struct{
	uint8_t		Mode;
	uint32_t	Baud;
	uint8_t		StopBits;
	uint8_t		WordLength;
	uint8_t		Parity;
	uint8_t		FlowControl;
	uint8_t		Over8;
}USART_Config_t;


typedef struct{
	USART_Config_t	USART_Config;
	USART_RegDef_t	*pUSARTx;
}USART_Handle_t;

void USART_ClkCtrl(USART_RegDef_t *pUSARTx, uint8_t status);
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_SetBaudRate(USART_Handle_t *pUSARTHandle);
void USART_Deinit(USART_RegDef_t *pUSARTx);
void USART_Cmd(USART_Handle_t *pUSARTHandle, uint8_t status);
void USART_Int_Cmd(USART_Handle_t *pUSARTHandle, uint8_t status);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t len);

extern USART_Handle_t USART1_handle;
extern USART_Handle_t USART2_handle;
extern USART_Handle_t USART3_handle;
extern USART_Handle_t UART4_handle;
extern USART_Handle_t UART5_handle;
extern USART_Handle_t USART6_handle;
#endif /* INC_STM32F446XX_USART_H_ */
