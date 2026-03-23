#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "GPIO_BSP.h"
#include "BSP_I2C.h"
#include "led_board.h"
#include "ssd1306.h"

#define APP_IDLE		0
#define I2C_TX_COMPLETE 1
#define I2C_RX_COMPLETE 2

SSD1306_Handle_t oled;
char buf[20];
uint8_t txbuffer = 0x06;
uint8_t rxbuffer[4]= {0x00};
uint8_t mode1_cmd[] = {0x00, 0x20};  // registro MODE1, valor 0x20 = AI=1
uint8_t I2C_EventTx_Status = 0 ;
uint8_t app_state;
int main(void)
{


	I2C2_GPIO_Setup();
	LED_BOARD_init();
	I2C2_Setup();
	I2C_Cmd(&I2C2_handle, ENABLE);

	SSD1306_Init(&oled, &I2C2_handle);
	SSD1306_Clear(&oled);
	SSD1306_SetCursor(&oled, 0, 0);
	NVIC_IRQ_Enable(IRQ_I2C2_EV);
	I2C_MasterSendDataIT(&I2C2_handle, mode1_cmd, 2, 0x40, I2C_STOP_ENABLE);

	while(1)
	{
		switch(app_state)
		{
			case I2C_TX_COMPLETE:
				if(I2C_EventTx_Status == 1)
				{
					I2C_MasterSendDataIT(&I2C2_handle, &txbuffer, 1, 0x40, I2C_STOP_DISABLE);
					app_state = APP_IDLE;
				}
				else if(I2C_EventTx_Status == 2)
				{
					I2C_MasterReceiveDataIT(&I2C2_handle, rxbuffer, 4, 0x40);
					app_state = APP_IDLE;
				}
				break;
			case I2C_RX_COMPLETE:

				uint16_t on_val  = rxbuffer[0] | (rxbuffer[1] << 8);  // ON_L | ON_H
				uint16_t off_val = rxbuffer[2] | (rxbuffer[3] << 8);  // OFF_L | OFF_H

				sprintf(buf, "ON:  %d \n", on_val);
				SSD1306_WriteString(&oled, buf, SSD1306_WHITE);

				sprintf(buf, "OFF: %d \n", off_val);
				SSD1306_WriteString(&oled, buf, SSD1306_WHITE);

				SSD1306_WriteString(&oled, "Com completa", SSD1306_WHITE);

				SSD1306_UpdateScreen(&oled);
				app_state = APP_IDLE;
				break;

			case APP_IDLE:
				break;
		}

	}
}

void I2C_ApplicationEventCallback(I2C_Handle_t *I2C_handle, uint8_t I2C_event)
{
	if(I2C_event == I2C_EVENT_TX_CMPLT)
	{
		I2C_EventTx_Status++;
		app_state = I2C_TX_COMPLETE;
	}
	else if(I2C_event == I2C_EVENT_RX_CMPLT)
	{
		app_state = I2C_RX_COMPLETE;
	}
}


