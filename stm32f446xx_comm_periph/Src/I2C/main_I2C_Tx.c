#include <stdint.h>
#include <string.h>
#include "GPIO_BSP.h"
#include "BSP_I2C.h"


int main(void)
{
	uint8_t txbuffer[] = {0x00, 0xAE, 0x8D, 0x14, 0xAF};
	I2C2_GPIO_Setup();
	I2C2_Setup();
	I2C_Cmd(&I2C2_handle, ENABLE);
	I2C_SendData(&I2C2_handle, txbuffer, sizeof(txbuffer), 0x3C,I2C_CONFIGACK_ENABLE);
	while(1);
}
