/*
 * can_wrapped.h
 *
 *  Created on: 29 mar 2026
 *      Author: erjo_
 */

#ifndef HAL_WRAPPED_INC_CAN_WRAPPED_H_
#define HAL_WRAPPED_INC_CAN_WRAPPED_H_

#include <stdint.h>
#include <string.h>

typedef enum {
    CAN_WRAPPER_OK,
    CAN_WRAPPER_BUSY,
    CAN_WRAPPER_ERROR
} CAN_Wrapper_Status_t;

typedef enum {
    CAN_BUS_1,
    CAN_BUS_2
} CAN_Bus_t;


#define WRAPPED_CAN_ID_STD                  (0x00000000U)  /*!< Standard Id */
#define WRAPPED_CAN_ID_EXT                  (0x00000004U)  /*!< Extended Id */
#define WRAPPED_CAN_RTR_DATA                (0x00000000U)  /*!< Data frame   */
#define WRAPPED_CAN_RTR_REMOTE              (0x00000002U)  /*!< Remote frame */


uint32_t Wrapped_CAN_GetTxMailboxesFreeLevel(CAN_Bus_t can_bus);
CAN_Wrapper_Status_t CAN_Wrapper_Send(CAN_Bus_t bus,
                                      uint32_t std_id,
                                      const uint8_t *data,
                                      uint8_t dlc,
                                      uint32_t *mailbox);
CAN_Wrapper_Status_t CAN_Wrapper_GetRxMessage(CAN_Bus_t bus,
                                               uint32_t fifo,
                                               uint8_t *data,
                                               uint8_t *dlc,
                                               uint32_t *std_id);
void Wrapped_CAN_FiltersInit(void);

extern uint16_t new_rx_telemetry = 0;
extern uint16_t new_tx_telemetry = 0;
#endif /* HAL_WRAPPED_INC_CAN_WRAPPED_H_ */
