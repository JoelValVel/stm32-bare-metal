#include <stdint.h>
#include <string.h>
#include "GPIO_BSP.h"
#include "BSP_SPI.h"
#include "led_board.h"

int main(void)
{
	char SPI_user_data[] = "Hello world";
	uint8_t test_data = 0x55;
	uint8_t receive_data = 0x00;
	LED_BOARD_init();
	SPI2_GPIO_Setup();
	SPI2_Setup();
	NVIC_IRQ_Enable(IRQ_SPI2);
	SPI_Cmd(&SPI2_handle, ENABLE);
//	SPI1->SPI_CR1 &= ~(1 << SPI_CR1_SSI);  // SSI=0 → CS activo, solo cuando ssm = 1
//	SPI_SendData(&SPI1_handle, (uint8_t *)SPI_user_data, strlen(SPI_user_data));
	SPI_SendDataIT(&SPI2_handle, &test_data, 1);
	SPI_ReceiveDataIT(&SPI2_handle, &receive_data, 1);
//	SPI1->SPI_CR1 |= (1 << SPI_CR1_SSI);   // SSI=1 → CS inactivo, solo cuando ssm = 1
	while(!rx_complete);
	rx_complete = 0;
	SPI_Cmd(&SPI2_handle, DISABLE);
	if(receive_data == test_data)
		LED_BOARD_toggle();
	while(1);
}
