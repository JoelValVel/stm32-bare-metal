#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "GPIO_BSP.h"
#include "BSP_I2C.h"
#include "led_board.h"
#include "ssd1306.h"

SSD1306_Handle_t oled;
char buf[20];

int main(void)
{
	uint8_t txbuffer = 0x06;
	uint8_t rxbuffer[4]= {0x00};
	uint8_t mode1_cmd[] = {0x00, 0x20};  // registro MODE1, valor 0x20 = AI=1

	I2C2_GPIO_Setup();
	LED_BOARD_init();
	I2C2_Setup();
	I2C_Cmd(&I2C2_handle, ENABLE);

	SSD1306_Init(&oled, &I2C2_handle);
	SSD1306_Clear(&oled);
	SSD1306_SetCursor(&oled, 0, 0);

	I2C_SendData(&I2C2_handle, mode1_cmd, 2, 0x40, I2C_STOP_ENABLE);

	// Enviar registro sin STOP
	I2C_SendData(&I2C2_handle, &txbuffer, 1, 0x40, I2C_STOP_DISABLE);

	// Leer 4 bytes consecutivos
	I2C_ReceiveData(&I2C2_handle, rxbuffer, 4, 0x40);

	uint16_t on_val  = rxbuffer[0] | (rxbuffer[1] << 8);  // ON_L | ON_H
	uint16_t off_val = rxbuffer[2] | (rxbuffer[3] << 8);  // OFF_L | OFF_H

	sprintf(buf, "ON:  %d \n", on_val);
	SSD1306_WriteString(&oled, buf, SSD1306_WHITE);

	sprintf(buf, "OFF: %d", off_val);
	SSD1306_WriteString(&oled, buf, SSD1306_WHITE);

	SSD1306_UpdateScreen(&oled);
	while(1);
}
