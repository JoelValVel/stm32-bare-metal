/*
 * stm32f446xx_spi.h
 *
 *  Created on: 13 mar 2026
 *      Author: erjo_
 */

#ifndef DRIVERS_INC_STM32F446XX_SPI_H_
#define DRIVERS_INC_STM32F446XX_SPI_H_

#include "stm32f446xx.h"
#include "stm32f446xx_nvic.h"
#include <stddef.h>

#define IS_SPI_RX_BUFF_FULL(pSPIx)  (((pSPIx)->SPI_SR >> 0) & 0x01)
#define IS_SPI_TX_BUFF_EMPTY(pSPIx)  (((pSPIx)->SPI_SR >> 1) & 0x01)

#define SPI_READY		0
#define SPI_RX_BUSY		1
#define SPI_TX_BUSY		2

#define SPI_EVENT_TX_CMPLT	1
#define SPI_EVENT_RX_CMPLT	2
#define SPI_EVENT_FRE_ERR	3
#define SPI_EVENT_OVR_ERR	4
#define SPI_EVENT_MODF_ERR	5
#define SPI_EVENT_CRC_ERR	6

typedef enum{
	SPI_DeviceMode_Slave,
	SPI_DeviceMode_Master,
}SPI_DeviceMode_t;
typedef enum{
	SPI_BusConfig_FullDuplex,
	SPI_BusConfig_HalfDuplex,
	SPI_BusConfig_SimplexRx,
}SPI_BusConfig_t;
typedef enum{
	SPI_DataFrmat_8bit,
	SPI_DataFrmat_16bit,
}SPI_DataFrmat_t;
typedef enum {
    SPI_Prescaler_2     = 0,  // fPCLK/2
    SPI_Prescaler_4     = 1,  // fPCLK/4
    SPI_Prescaler_8     = 2,  // fPCLK/8
    SPI_Prescaler_16    = 3,  // fPCLK/16
    SPI_Prescaler_32    = 4,  // fPCLK/32
    SPI_Prescaler_64    = 5,  // fPCLK/64
    SPI_Prescaler_128   = 6,  // fPCLK/128
    SPI_Prescaler_256   = 7   // fPCLK/256
} SPI_Prescaler_T;
typedef enum{
	SPI_NSS_Disable,
	SPI_NSS_Enable,
}SPI_NSS_t;

typedef enum{
	SPI_Int_Tx,
	SPI_Int_Rx,
	SPI_Int_Err
}SPI_Interrupts_t;
typedef struct{
	SPI_DeviceMode_t DeviceMode;
	SPI_BusConfig_t BusConfig;
	SPI_DataFrmat_t DataFrmat;
	uint8_t CPOL;
	uint8_t CPHA;
	SPI_Prescaler_T Prescaler;
	SPI_NSS_t	NSS;
}SPI_Config_t;

typedef struct{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPIConfig;
	uint8_t 		*pTxBuffer;
	uint8_t 		*pRxBuffer;
	uint32_t 		TxLen;
	uint32_t 		RxLen;
	uint8_t 		TxState;
	uint8_t 		RxState;
}SPI_Handle_t;

extern SPI_Handle_t SPI1_Handle;

void SPI_ClkCtrl(SPI_RegDef_t *pSPIx, uint8_t status);
void SPI_Init(SPI_Handle_t *SPI_Handle);
void SPI_Deinit(SPI_Handle_t *SPI_Handle);
void SPI_Cmd(SPI_Handle_t *SPI_Handle, uint8_t);
void SPI_Int_Cmd(SPI_Handle_t *SPI_Handle,SPI_Interrupts_t SPI_Int, uint8_t status);
void SPI_SendData(SPI_Handle_t *SPI_Handle, uint8_t *pTxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_Handle_t *SPI_Handle, uint8_t *pRxBuffer, uint32_t len);

uint8_t SPI_SendDataIT(SPI_Handle_t *SPI_Handle, uint8_t *pTxBuffer, uint32_t len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *SPI_Handle, uint8_t *pRxBuffer, uint32_t len);

void SPI_IRQHandler(SPI_Handle_t *SPI_Handle);

void SPI_ApplicationEventCallback(SPI_Handle_t *SPI_handle, uint8_t SPI_event);

extern SPI_Handle_t SPI1_handle;
extern SPI_Handle_t SPI2_handle;
extern SPI_Handle_t SPI3_handle;
extern SPI_Handle_t SPI4_handle;
extern volatile uint8_t rx_complete;
#endif /* DRIVERS_INC_STM32F446XX_SPI_H_ */
