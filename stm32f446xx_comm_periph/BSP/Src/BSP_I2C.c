#include "BSP_I2C.h"

I2C_Handle_t I2C2_handle = {0};

void I2C2_Setup(void)
{

	I2C2_handle.pI2Cx = I2C2;
	I2C2_handle.I2CConfig.I2C_ACKControl = I2C_CONFIGACK_ENABLE;
	I2C2_handle.I2CConfig.I2C_SCLSpeed = I2C_SCLSpeed_SM;
	I2C_Init(&I2C2_handle);

}
