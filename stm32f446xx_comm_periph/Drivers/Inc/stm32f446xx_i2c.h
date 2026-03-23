/*
 * stm32f446xx_i2c.h
 *
 *  Created on: 16 mar 2026
 *      Author: erjo_
 */

#ifndef INC_STM32F446XX_I2C_H_
#define INC_STM32F446XX_I2C_H_


#include "stm32f446xx.h"
#include "stm32f446xx_rcc.h"

#define I2C_SCLSpeed_SM			100000U
#define I2C_SCLSpeed_FM2K		200000U
#define I2C_SCLSpeed_FM4K		300000U

#define I2C_READY				0
#define I2C_BUSY_IN_RX			1
#define I2C_BUSY_IN_TX			2

#define I2C_CONFIGACK_ENABLE			1
#define I2C_CONFIGACK_DISABLE			0

#define I2C_STOP_ENABLE			1
#define I2C_STOP_DISABLE		0

#define I2C_FM_DUTYCYCLE_2		0
#define I2C_FM_DUTYCYCLE_16_9	1

#define I2C_GENERATE_START(pI2Cx)  ((pI2Cx)->I2C_CR1 |= (1 << I2C_CR1_START))
#define I2C_GENERATE_STOP(pI2Cx)   ((pI2Cx)->I2C_CR1 |= (1 << I2C_CR1_STOP))
#define I2C_ACK_DISABLE(pI2Cx)		((pI2Cx)->I2C_CR1 &= ~(0x01 << I2C_CR1_ACK))
#define I2C_ACK_ENABLE(pI2Cx)		((pI2Cx)->I2C_CR1 |= (0x01 << I2C_CR1_ACK))

#define I2C_GET_SB_FLAG			(I2C_Handle->pI2Cx->I2C_SR1 & (0x01 << I2C_SR1_SB))
#define I2C_GET_ADD_FLAG		(I2C_Handle->pI2Cx->I2C_SR1 & (0x01 << I2C_SR1_ADDR))
#define I2C_GET_TXE_FLAG		(I2C_Handle->pI2Cx->I2C_SR1 & (0x01 << I2C_SR1_TXE))
#define I2C_GET_BTF_FLAG		(I2C_Handle->pI2Cx->I2C_SR1 & (0x01 << I2C_SR1_BTF))
#define I2C_GET_RXE_FLAG		(I2C_Handle->pI2Cx->I2C_SR1 & (0x01 << I2C_SR1_RXNE))
#define I2C_GET_STOPF_FLAG		(I2C_Handle->pI2Cx->I2C_SR1 & (0x01 << I2C_SR1_STOPF))

#define I2C_GET_ITBUFEN_STATUS	(I2C_Handle->pI2Cx->I2C_CR2 & (0X01 << I2C_CR2_ITBUFEN))
#define I2C_GET_ITEVFEN_STATUS	(I2C_Handle->pI2Cx->I2C_CR2 & (0X01 << I2C_CR2_ITEVTEN))
#define I2C_GET_ITERREN_STATUS	(I2C_Handle->pI2Cx->I2C_CR2 & (0X01 << I2C_CR2_ITERREN))

#define I2C_ACTION_READ 	1
#define I2C_ACTION_WRITE	0

#define I2C_EVENT_RX_CMPLT	0
#define I2C_EVENT_TX_CMPLT	1
typedef struct{
	uint32_t I2C_SCLSpeed;
	uint8_t I2C_DevideAddress;
	uint8_t I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
} I2C_Config_t;

typedef struct{
	I2C_RegDef_t	*pI2Cx;
	I2C_Config_t	I2CConfig;
	uint8_t			*pTxBuffer;
	uint8_t 		*pRxBuffer;
	uint32_t 		TxLen;
	uint32_t 		RxLen;
	uint8_t			TxRxState;
	uint8_t 		DevAddr;
	uint32_t		RxSize;
	uint8_t			Sr;			// To store repeated start value
}I2C_Handle_t;


void I2C_ClkCtrl(I2C_RegDef_t *pI2Cx, uint8_t status);
void I2C_Init(I2C_Handle_t *I2C_Handle);
void I2C_Deinit(I2C_Handle_t *I2C_Handle);
void I2C_Cmd(I2C_Handle_t *I2C_Handle, uint8_t status);
void I2C_Int_Cmd(I2C_Handle_t *pI2CHandle, uint8_t status);
void I2C_SendData(I2C_Handle_t *I2C_Handle, uint8_t *pTxBuffer, uint32_t len, uint8_t slave_add, uint8_t i2c_stop_status);
void I2C_ReceiveData(I2C_Handle_t *I2C_Handle, uint8_t *pRxBuffer, uint32_t len, uint8_t slave_add);

int8_t I2C_MasterSendDataIT(I2C_Handle_t *I2C_Handle, uint8_t *pTxBuffer, uint32_t len, uint8_t slave_add, uint8_t i2c_stop_status);
int8_t I2C_MasterReceiveDataIT(I2C_Handle_t *I2C_Handle, uint8_t *pRxBuffer, uint32_t len, uint8_t slave_add);

void I2C_EV_IRQHandler(I2C_Handle_t *I2C_Handle);
void I2C_ER_IRQHandler(I2C_Handle_t *I2C_Handle);

void I2C_ApplicationEventCallback(I2C_Handle_t *I2C_handle, uint8_t I2C_event);

void I2C_ApplicationEventCallback(I2C_Handle_t *I2C_handle, uint8_t I2C_event);


extern I2C_Handle_t I2C1_handle;
extern I2C_Handle_t I2C2_handle;
extern I2C_Handle_t I2C3_handle;
//extern volatile uint8_t rx_complete;
#endif /* INC_STM32F446XX_I2C_H_ */
