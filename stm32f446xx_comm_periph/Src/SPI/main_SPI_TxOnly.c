#include <stdint.h>
#include <string.h>
#include "GPIO_BSP.h"
#include "BSP_SPI.h"


int main(void)
{
	char SPI_user_data[] = "Hello world";
	SPI1_GPIO_Setup();
	SPI1_Setup();
	SPI_Cmd(&SPI1_handle, ENABLE);
//	SPI1->SPI_CR1 &= ~(1 << SPI_CR1_SSI);  // SSI=0 → CS activo, solo cuando ssm = 1
	SPI_SendData(&SPI1_handle, (uint8_t *)SPI_user_data, strlen(SPI_user_data));
//	SPI1->SPI_CR1 |= (1 << SPI_CR1_SSI);   // SSI=1 → CS inactivo, solo cuando ssm = 1
	SPI_Cmd(&SPI1_handle, DISABLE);
	while(1);
}
