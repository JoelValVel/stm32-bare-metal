#include "app_can.h"
#include "main.h"

extern CAN_HandleTypeDef hcan1;
extern UART_HandleTypeDef huart2;
uint8_t can_rxdata[8];
uint8_t can_rxtel[8];

CAN_SM_Status_t sm_can_state = CAN_IDLE;
Telemetry_t rxTelemetry;
uint16_t new_rx_telemetry = 0;
uint16_t new_tx_telemetry = 0;
char txuart[100];
void APP_CAN_FiltersInit(void)
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

APP_Status_t APP_CAN_AddTxTelemetry(const uint8_t telemetry[7], uint32_t *pTxmailbox)
{
	HAL_StatusTypeDef status;
	CAN_TxHeaderTypeDef tel_header;

	tel_header.StdId = 0x700;// msb bits 111
	tel_header.IDE = CAN_ID_STD;
	tel_header.RTR = CAN_RTR_DATA;
	tel_header.DLC = 7;

	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
	{
		status = HAL_CAN_AddTxMessage(&hcan1, &tel_header, telemetry, pTxmailbox);
		return status;
	}
	return HAL_BUSY;
}


void APP_CAN_SendTelemetry(float press, float temp, uint8_t humidity)
{
	uint8_t tx_data[7];
	uint32_t mailbox;
	HAL_StatusTypeDef hal_status;


	TelemetryCode(press, temp, humidity, tx_data);
	hal_status = APP_CAN_AddTxTelemetry(tx_data, &mailbox);
	if(hal_status == HAL_OK)
	{
	  sprintf(txuart,"Telemetria agregada al mailbox: %lu \r\n",mailbox);
	  HAL_UART_Transmit(&huart2, txuart, strlen(txuart), HAL_MAX_DELAY);
	}
	else if(hal_status == HAL_BUSY)
	{
	  sprintf(txuart,"Mailboxes ocupados \r\n");
	  HAL_UART_Transmit(&huart2, txuart, strlen(txuart), HAL_MAX_DELAY);

	}
	else
	{
		sprintf(txuart,"Error al enviar \r\n");
		HAL_UART_Transmit(&huart2, txuart, strlen(txuart), HAL_MAX_DELAY);
	}
}

void APP_CAN_SM(void)
{
	switch(sm_can_state)
	{
		case CAN_IDLE:
			if(new_rx_telemetry)
				sm_can_state = CAN_Telemetry_Receive;
			if(new_tx_telemetry)
				sm_can_state = CAN_Telemetry_Send;
			break;
		case(CAN_Telemetry_Receive):
			TelemetryDecode(can_rxtel, &rxTelemetry);
			sprintf(txuart,"Presion: %f, Temp: %f, Humedad: %d",rxTelemetry.Preasure,rxTelemetry.Temp,rxTelemetry.Humidity);
			HAL_UART_Transmit(&huart2, txuart, strlen(txuart), HAL_MAX_DELAY);
			new_rx_telemetry--;
			sm_can_state = CAN_IDLE;
			break;
		case(CAN_Telemetry_Send):
			APP_CAN_SendTelemetry(1512.1, 80.5, 50);
			new_tx_telemetry--;
			sm_can_state = CAN_IDLE;
			break;

	}
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
