#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "GPIO_BSP.h"
#include "BSP_USART.h"
#include "BSP_I2C.h"
#include "led_board.h"
#include "ssd1306.h"

SSD1306_Handle_t oled;
char buf[6];

int main(void)
{
	uint8_t txbuffer[] = "hola";
	uint8_t rxbuffer[4] = {0};

	I2C2_GPIO_Setup();
	LED_BOARD_init();
	I2C2_Setup();
	I2C_Cmd(&I2C2_handle, ENABLE);

	SSD1306_Init(&oled, &I2C2_handle);
	SSD1306_Clear(&oled);
	SSD1306_SetCursor(&oled, 0, 0);
	SSD1306_WriteString(&oled, "Envio de dato...\n", SSD1306_WHITE);

	USART2_GPIO_Setup();
	USART2_Setup();
	USART_Cmd(&USART2_handle, ENABLE);


	USART_SendData(&USART2_handle, txbuffer, sizeof(txbuffer));


	SSD1306_WriteString(&oled, "Enviado", SSD1306_WHITE);
	SSD1306_UpdateScreen(&oled);
	while(1)
	{
		USART_ReceiveData(&USART2_handle, rxbuffer, 4);
		memcpy(buf, rxbuffer, 4);
		buf[4] = '\0';  // agregar terminador
		SSD1306_WriteString(&oled, buf, SSD1306_WHITE);
		SSD1306_UpdateScreen(&oled);
	}
}
