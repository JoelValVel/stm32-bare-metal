/*
 * app_can.h
 *
 *  Created on: 28 mar 2026
 *      Author: erjo_
 */

#ifndef INC_APP_CAN_H_
#define INC_APP_CAN_H_

//#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_uart.h"
//#include "stm32f4xx_hal_def.h"

#include "can_logic.h"
#include <stdio.h>
#include <string.h>


typedef enum {
    APP_OK = 0,
    APP_ERROR,
    APP_BUSY
} APP_Status_t;

extern uint8_t can_rxdata[8];



void APP_CAN_FiltersInit(void);
APP_Status_t APP_CAN_AddTxTelemetry(const uint8_t telemetry[7], uint32_t *pTxmailbox);
void APP_CAN_SendTelemetry(float press, float temp, uint8_t humidity);
void APP_CAN_SM(void);

typedef enum
{
	CAN_IDLE,
	CAN_Telemetry_Send,
	CAN_Telemetry_Receive,
}CAN_SM_Status_t;

extern CAN_SM_Status_t sm_can_state;
extern uint16_t new_rx_telemetry;
extern uint16_t new_tx_telemetry;

#define CAN_Event	1
#endif /* INC_APP_CAN_H_ */
