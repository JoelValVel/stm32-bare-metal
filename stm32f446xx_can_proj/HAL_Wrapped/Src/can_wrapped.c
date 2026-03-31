#include "can_wrapped.h"
#include "stm32f4xx_hal_can.h"

extern CAN_HandleTypeDef hcan1;
//extern CAN_HandleTypeDef hcan2;

uint16_t new_rx_telemetry = 0;
uint16_t new_tx_telemetry = 0;

static CAN_HandleTypeDef *get_handle(CAN_Bus_t bus)
{
    switch(bus)
    {
        case CAN_BUS_1: return &hcan1;
//        case CAN_BUS_2: return &hcan2;
        default:        return NULL;
    }
}
/* ── Traducción interna de HAL_StatusTypeDef ── */
static CAN_Wrapper_Status_t translate_status(HAL_StatusTypeDef s)
{
    switch(s)
    {
        case HAL_OK:    return CAN_WRAPPER_OK;
        case HAL_BUSY:  return CAN_WRAPPER_BUSY;
        default:        return CAN_WRAPPER_ERROR;
    }
}
uint32_t Wrapped_CAN_GetTxMailboxesFreeLevel(CAN_Bus_t can_bus)
{
	CAN_HandleTypeDef *hcan = get_handle(can_bus);

	return HAL_CAN_GetTxMailboxesFreeLevel(hcan);
}

CAN_Wrapper_Status_t CAN_Wrapper_Send(CAN_Bus_t bus,
                                      uint32_t std_id,
                                      const uint8_t *data,
                                      uint8_t dlc,
                                      uint32_t *mailbox)
{
    CAN_HandleTypeDef *hcan = get_handle(bus);
    if(hcan == NULL) return CAN_WRAPPER_ERROR;

    CAN_TxHeaderTypeDef hdr;
    hdr.StdId = std_id;
    hdr.IDE   = CAN_ID_STD;
    hdr.RTR   = CAN_RTR_DATA;
    hdr.DLC   = dlc;

    return translate_status(HAL_CAN_AddTxMessage(hcan, &hdr, data, mailbox));
}

CAN_Wrapper_Status_t CAN_Wrapper_GetRxMessage(CAN_Bus_t bus,
                                               uint32_t fifo,
                                               uint8_t *data,
                                               uint8_t *dlc,
                                               uint32_t *std_id)
{
    CAN_HandleTypeDef *hcan = get_handle(bus);
    if(hcan == NULL) return CAN_WRAPPER_ERROR;

    CAN_RxHeaderTypeDef rxheader;
    HAL_StatusTypeDef s = HAL_CAN_GetRxMessage(hcan, fifo, &rxheader, data);

    if(s == HAL_OK)
    {
        *dlc    = rxheader.DLC;
        *std_id = rxheader.StdId;
        return CAN_WRAPPER_OK;
    }
    return translate_status(s);
}
void Wrapped_CAN_FiltersInit(void)
{
	CAN_FilterTypeDef filter;
	filter.FilterIdHigh = 0xE000; // msb bits 111
	filter.FilterIdLow = 0;
	filter.FilterFIFOAssignment = CAN_FILTER_FIFO1;
	filter.FilterBank = 0;
	filter.FilterMode = CAN_FILTERMODE_IDLIST;
	filter.FilterScale = CAN_FILTERSCALE_16BIT;
	filter.FilterActivation = CAN_FILTER_ENABLE;

	HAL_CAN_ConfigFilter(&hcan1, &filter);

	filter.FilterIdHigh = 0;
	filter.FilterIdLow = 0;
	filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	filter.FilterBank = 1;
	filter.FilterMode = CAN_FILTERMODE_IDLIST;
	filter.FilterScale = CAN_FILTERSCALE_16BIT;
	filter.FilterActivation = CAN_FILTER_ENABLE;
	HAL_CAN_ConfigFilter(&hcan1, &filter);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rxheader;

	HAL_CAN_GetRxMessage(hcan, (uint32_t)CAN_RX_FIFO1, &rxheader, can_rxdata);

	if((rxheader.IDE == 0) && (rxheader.StdId == 0x700))
	{
		new_rx_telemetry++;
		memcpy(can_rxtel,can_rxdata,rxheader.DLC);
	}
}

