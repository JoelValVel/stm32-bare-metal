#include "stm32f446xx_i2c.h"
#include <stddef.h>
__attribute__((weak)) I2C_Handle_t I2C1_handle = {0};
__attribute__((weak)) I2C_Handle_t I2C2_handle = {0};
__attribute__((weak)) I2C_Handle_t I2C3_handle = {0};

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t addr,uint8_t I2C_ACTION);
static void I2C_Close_ReceiveData(I2C_Handle_t *pI2CHandle);
static void I2C_Close_SendData(I2C_Handle_t *pI2CHandle);

void I2C_ClkCtrl(I2C_RegDef_t *pI2Cx, uint8_t status)
{
	if(status == ENABLE)
	{
	    switch((uint32_t) pI2Cx)
	    {
	        case((uint32_t)I2C1):
	            I2C1_EN_CLK();
	            break;

	        case((uint32_t)I2C2):
	            I2C2_EN_CLK();
	            break;

	        case((uint32_t)I2C3):
	            I2C3_EN_CLK();
	            break;
	    }
	}
	else if(status == DISABLE)
	{
	    switch((uint32_t) pI2Cx){
	        case((uint32_t)I2C1):
	            I2C1_DIS_CLK();
	            break;

	        case((uint32_t)I2C2):
	            I2C2_DIS_CLK();
	            break;

	        case((uint32_t)I2C3):
	            I2C3_DIS_CLK();
	            break;

	    }
	}
}

void I2C_Init(I2C_Handle_t *I2C_Handle)
{
	// Al inicio de I2C_Init
	I2C_Handle->pI2Cx->I2C_CR1 |= (0x01 << I2C_CR1_SWRST);  // reset
	I2C_Handle->pI2Cx->I2C_CR1 &= ~(0x01 << I2C_CR1_SWRST); // salir de reset

	I2C_Cmd(I2C_Handle, DISABLE);
	I2C_ClkCtrl(I2C_Handle->pI2Cx, ENABLE);

	I2C_Handle->pI2Cx->I2C_CR2 &= ~(0x3F << I2C_CR2_FREQ);
	I2C_Handle->pI2Cx->I2C_CR2 |= ((RCC_GetAPB1CLK()/1000000U) << I2C_CR2_FREQ);

	I2C_Handle->pI2Cx->I2C_OAR1 &= ~(0x7F << I2C_OAR1_ADD1);
	I2C_Handle->pI2Cx->I2C_OAR1 |= (I2C_Handle->I2CConfig.I2C_DevideAddress << I2C_OAR1_ADD1);

	I2C_Handle->pI2Cx->I2C_OAR1 &= ~(0x01 << I2C_OAR1_ADDMODE);

	I2C_Handle->pI2Cx->I2C_CCR &= ~(0x01 << I2C_CCR_FS);



	uint16_t temp_ccr = 0;
	I2C_Handle->pI2Cx->I2C_CCR &= ~(0xFFF << I2C_CCR_CCR);
	if(I2C_Handle->I2CConfig.I2C_SCLSpeed <= I2C_SCLSpeed_SM)
	{
		// Standard Mode
		temp_ccr = RCC_GetAPB1CLK() / (2 * I2C_Handle->I2CConfig.I2C_SCLSpeed);

	}
	else
	{
		// Fast Mode

		I2C_Handle->pI2Cx->I2C_CCR |= (0x01 << I2C_CCR_FS);

		I2C_Handle->pI2Cx->I2C_CCR &= ~(0x01 << I2C_CCR_DUTY);
		I2C_Handle->pI2Cx->I2C_CCR |= (I2C_Handle->I2CConfig.I2C_FMDutyCycle << I2C_CCR_DUTY);

		if(I2C_Handle->I2CConfig.I2C_FMDutyCycle)
		{
			// Fm mode t_low/t_high = 16/9

			temp_ccr = RCC_GetAPB1CLK() / (25 * I2C_Handle->I2CConfig.I2C_SCLSpeed);

		}
		else
		{
			// Fm mode t_low/t_high = 2

			temp_ccr = RCC_GetAPB1CLK() / (3 * I2C_Handle->I2CConfig.I2C_SCLSpeed);

		}
	}
	I2C_Handle->pI2Cx->I2C_CCR |= (temp_ccr << I2C_CCR_CCR);
	uint8_t trise;
	if(I2C_Handle->I2CConfig.I2C_SCLSpeed <= I2C_SCLSpeed_SM)
	{
		// Standard Mode

		trise = (RCC_GetAPB1CLK() / 1000000U) + 1;

	}
	else
	{
		// FM Mode

		trise = ((RCC_GetAPB1CLK() / 1000000) * 300 / 1000) + 1;
	}
	I2C_Handle->pI2Cx->I2C_TRISE = (trise & 0x3F);
}

void I2C_Deinit(I2C_Handle_t *I2C_Handle)
{
	switch((uint32_t) I2C_Handle->pI2Cx)
	{
		case((uint32_t)I2C1):
			I2C1_RESET();
			break;

		case((uint32_t)I2C2):
			I2C2_RESET();
			break;

		case((uint32_t)I2C3):
			I2C3_RESET();
			break;
	}
}

void I2C_Cmd(I2C_Handle_t *I2C_Handle, uint8_t status)
{
	if(status == ENABLE)
	{
		I2C_Handle->pI2Cx->I2C_CR1 |= (0x01 << I2C_CR1_PE);
		I2C_ACK_ENABLE(I2C_Handle->pI2Cx);
	}
	else if(status == DISABLE)
		I2C_Handle->pI2Cx->I2C_CR1 &= ~(0x01 << I2C_CR1_PE);
}
void I2C_Int_Cmd(I2C_Handle_t *I2C_Handle, uint8_t status)
{
	if(status == ENABLE)
	{
		// enable ITBUFEN Control Bit
		I2C_Handle->pI2Cx->I2C_CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		// enable ITEVFEN Control Bit
		I2C_Handle->pI2Cx->I2C_CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		// enable ITERREN Control Bit
		I2C_Handle->pI2Cx->I2C_CR2 |= ( 1 << I2C_CR2_ITERREN);
	}
	else if(status == DISABLE)
	{
		// enable ITBUFEN Control Bit
		I2C_Handle->pI2Cx->I2C_CR2 &= ~( 1 << I2C_CR2_ITBUFEN);

		// enable ITEVFEN Control Bit
		I2C_Handle->pI2Cx->I2C_CR2 &= ~( 1 << I2C_CR2_ITEVTEN);

		// enable ITERREN Control Bit
		I2C_Handle->pI2Cx->I2C_CR2 &= ~( 1 << I2C_CR2_ITERREN);
	}

}

void I2C_SendData(I2C_Handle_t *I2C_Handle, uint8_t *pTxBuffer, uint32_t len, uint8_t slave_add, uint8_t i2c_stop_status)
{
	uint32_t dummy;
	// Generate start condition
	I2C_GENERATE_START(I2C_Handle->pI2Cx);

	/*	2. confirm that start generation is completed by checking the SB flag in the SR1
		Note: Until SB is cleared SCL will be stretched (pulled to LOW) */
	while(!I2C_GET_SB_FLAG); // Lectura de SR1

	//	3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits)
	I2C_ExecuteAddressPhase(I2C_Handle->pI2Cx, slave_add, I2C_ACTION_WRITE);

	//	4. Confirm that address phase is completed by checking the ADDR flag in teh SR1
	while(!I2C_GET_ADD_FLAG);

	/* 	5. clear the ADDR flag according to its software sequence
	 	Note: Until ADDR is cleared SCL will be stretched (pulled to LOW) */
	dummy = I2C_Handle->pI2Cx->I2C_SR2;
	(void) dummy;

	//6. send the data until Len becomes 0
	while(len)
	{
		while(!I2C_GET_TXE_FLAG);
		I2C_Handle->pI2Cx->I2C_DR = *pTxBuffer;
		// Esperar y leer RXNE
		len--;
		pTxBuffer++;
	}


	/*7. when Len becomes zero wait for TXE-1 and BTF-1 before generating the STOP condition
	 Note: TXE-1, BTF-1, means that both SR and DR are empty and next transmission should begin
	 when BTF-1 SCL will be stretched (pulled to LOW) */
	while(!(I2C_GET_TXE_FLAG) || !(I2C_GET_BTF_FLAG));

	/* 8. Generate STOP condition and master need not to wait for the completion of stop condition.
 	   Note: generating STOP, automatically clears the BTF 11 */
	if(i2c_stop_status)
		I2C_GENERATE_STOP(I2C_Handle->pI2Cx);
}

void I2C_ReceiveData(I2C_Handle_t *I2C_Handle, uint8_t *pRxBuffer, uint32_t len, uint8_t slave_add)
{
	uint32_t dummy;
	// 1. Generar START condition
	I2C_GENERATE_START(I2C_Handle->pI2Cx);

	/* 2. Confirmar el START revisando la bandera SB
	 * Nota: hasta que se limpie la bandera el SCL se queda en LOW */
	while(!I2C_GET_SB_FLAG);
	I2C_ExecuteAddressPhase(I2C_Handle->pI2Cx, slave_add, I2C_ACTION_READ);

	while(!I2C_GET_ADD_FLAG);

	if(len == 1)
	{
		// Desactiva el ACK para recibir un solo byte
		I2C_ACK_DISABLE(I2C_Handle->pI2Cx);

		// Limpia ADD FLAG
		dummy = I2C_Handle->pI2Cx->I2C_SR2;
		(void) dummy;

		// Esperar a RxE flag
		while(!I2C_GET_RXE_FLAG);

		// Generar STOP condition
		I2C_GENERATE_STOP(I2C_Handle->pI2Cx);

		// Leer byte
		*pRxBuffer = I2C_Handle->pI2Cx->I2C_DR;
	}
	else if(len > 1)
	{
		// Limpia ADD FLAG
		dummy = I2C_Handle->pI2Cx->I2C_SR2;
		(void) dummy;

		// Leer los datos hasta len == 0
		for(uint32_t i = len; i > 0; i--)
		{
			// Esperar a RxE flag
			while(!I2C_GET_RXE_FLAG);
			if(i == 2) // ultimos dos bytes restantes
			{
				I2C_ACK_DISABLE(I2C_Handle->pI2Cx);
			}
			if(i == 1)
			{
				I2C_GENERATE_STOP(I2C_Handle->pI2Cx);
			}
			// Leer el dato
			*pRxBuffer = I2C_Handle->pI2Cx->I2C_DR;
			pRxBuffer++;
		}

	}
	// Re-habilitar el ACK
	I2C_ACK_ENABLE(I2C_Handle->pI2Cx);
}
void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t addr,uint8_t I2C_ACTION)
{
	uint8_t dr_temp;
	dr_temp = (addr << 1);
	if(I2C_ACTION == I2C_ACTION_READ)
		dr_temp |= 0x01;
	else if(I2C_ACTION == I2C_ACTION_WRITE)
		dr_temp &= ~(0x01);

	pI2Cx->I2C_DR = dr_temp;
}

int8_t I2C_MasterSendDataIT(I2C_Handle_t *I2C_Handle, uint8_t *pTxBuffer, uint32_t len, uint8_t slave_add, uint8_t i2c_stop_status)
{
	uint8_t busystate = I2C_Handle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		I2C_Handle->pTxBuffer = pTxBuffer;
		I2C_Handle->TxLen = len;
		I2C_Handle->TxRxState = I2C_BUSY_IN_TX;
		I2C_Handle->DevAddr = slave_add;
		I2C_Handle->Sr = i2c_stop_status;

		// Generate START Condition
		I2C_GENERATE_START(I2C_Handle->pI2Cx);

		I2C_Int_Cmd(I2C_Handle, ENABLE);

	}

	return busystate;

}
int8_t I2C_MasterReceiveDataIT(I2C_Handle_t *I2C_Handle, uint8_t *pRxBuffer, uint32_t len, uint8_t slave_add)
{
	uint8_t busystate = I2C_Handle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		I2C_Handle->pRxBuffer = pRxBuffer;
		I2C_Handle->RxLen = len;
		I2C_Handle->TxRxState = I2C_BUSY_IN_RX;
		I2C_Handle->DevAddr = slave_add;
//		I2C_Handle->Sr = Sr;

		// Generate START Condition
		I2C_GENERATE_START(I2C_Handle->pI2Cx);

		I2C_Int_Cmd(I2C_Handle, ENABLE);

	}

	return busystate;

}

void I2C_EV_IRQHandler(I2C_Handle_t *I2C_Handle)
{
	//Interrupt handling for both master and slave mode of a device

	uint32_t dummy;
	//1. Handle For interrupt generated by SB event
	//	Note : SB flag is only applicable in Master mode
	if((I2C_GET_SB_FLAG) && (I2C_GET_ITEVFEN_STATUS))
	{
		// Ejecuta el address phase
		if(I2C_Handle->TxRxState == I2C_BUSY_IN_RX)
			I2C_ExecuteAddressPhase(I2C_Handle->pI2Cx, I2C_Handle->DevAddr, I2C_ACTION_READ);
		else if(I2C_Handle->TxRxState == I2C_BUSY_IN_TX)
			I2C_ExecuteAddressPhase(I2C_Handle->pI2Cx, I2C_Handle->DevAddr, I2C_ACTION_WRITE);
	}
	//2. Handle For interrupt generated by ADDR event
	//Note : When master mode : Address is sent
	//		 When Slave mode   : Address matched with own address
	if((I2C_GET_ADD_FLAG) && (I2C_GET_ITEVFEN_STATUS))
	{
		if((I2C_Handle->TxRxState == I2C_BUSY_IN_RX) && (I2C_Handle->RxLen == 1))
		{
			// Desactiva el ACK para recibir un solo byte
			I2C_ACK_DISABLE(I2C_Handle->pI2Cx);
		}
		dummy = I2C_Handle->pI2Cx->I2C_SR1;
		dummy = I2C_Handle->pI2Cx->I2C_SR2;
		(void) dummy;
	}
	//3. Handle For interrupt generated by BTF(Byte Transfer Finished) event
	if((I2C_GET_BTF_FLAG) && (I2C_GET_ITEVFEN_STATUS))
	{
		if(I2C_Handle->TxRxState == I2C_BUSY_IN_TX)
		{
			if(I2C_Handle->TxLen == 0)
			{
				if(I2C_Handle->Sr == I2C_STOP_ENABLE)
				{
					I2C_GENERATE_STOP(I2C_Handle->pI2Cx);
				}
				I2C_Handle->TxRxState = I2C_READY;
				I2C_ApplicationEventCallback(I2C_Handle, I2C_EVENT_TX_CMPLT);
				// Deshabilitar interrupts
				I2C_Int_Cmd(I2C_Handle, DISABLE);
				I2C_Close_SendData(I2C_Handle);

			}
		}
	}
	//4. Handle For interrupt generated by STOPF event
	// Note : Stop detection flag is applicable only slave mode . For master this flag will never be set
	if((I2C_GET_STOPF_FLAG) && (I2C_GET_ITEVFEN_STATUS))
	{
		dummy = I2C_Handle->pI2Cx->I2C_SR1;
		I2C_Handle->pI2Cx->I2C_CR1 |= (0x01 << I2C_CR1_STOP);
	}
	//5. Handle For interrupt generated by TXE event
	if((I2C_GET_TXE_FLAG) && (I2C_GET_ITEVFEN_STATUS) && (I2C_GET_ITBUFEN_STATUS))
	{
		if(I2C_Handle->TxRxState == I2C_BUSY_IN_TX)
		{
			if(I2C_Handle->TxLen > 0)
			{
				I2C_Handle->pI2Cx->I2C_DR = *(I2C_Handle->pTxBuffer);
				I2C_Handle->TxLen--;
				I2C_Handle->pTxBuffer++;
			}

		}

	}
	//6. Handle For interrupt generated by RXNE event
	if((I2C_GET_RXE_FLAG) && (I2C_GET_ITEVFEN_STATUS) && (I2C_GET_ITBUFEN_STATUS))
	{
		if(I2C_Handle->TxRxState == I2C_BUSY_IN_RX)
		{
			if(I2C_Handle->RxLen == 1)
			{
				// Generar STOP condition
				I2C_GENERATE_STOP(I2C_Handle->pI2Cx);

				// Leer byte
				*(I2C_Handle->pRxBuffer) = I2C_Handle->pI2Cx->I2C_DR;

				// Re-habilitar el ACK
				I2C_ACK_ENABLE(I2C_Handle->pI2Cx);
				// Deshabilitar interrupts
				I2C_Int_Cmd(I2C_Handle, DISABLE);
				I2C_Close_ReceiveData(I2C_Handle);
				I2C_ApplicationEventCallback(I2C_Handle, I2C_EVENT_RX_CMPLT);

			}
			else if(I2C_Handle->RxLen > 1)
			{
				if(I2C_Handle->RxLen == 2)
					I2C_ACK_DISABLE(I2C_Handle->pI2Cx);

				*(I2C_Handle->pRxBuffer) = I2C_Handle->pI2Cx->I2C_DR;
				I2C_Handle->pRxBuffer++;
				I2C_Handle->RxLen--;
			}
		}
	}
}

void I2C_Close_ReceiveData(I2C_Handle_t *I2C_Handle)
{
	I2C_Handle->pRxBuffer = NULL;
	I2C_Handle->RxLen = 0;
	I2C_Handle->TxRxState = I2C_READY;
	I2C_Handle->DevAddr = 0;
}

void I2C_Close_SendData(I2C_Handle_t *I2C_Handle)
{
	I2C_Handle->pTxBuffer = NULL;
	I2C_Handle->TxLen = 0;
	I2C_Handle->TxRxState = I2C_READY;
	I2C_Handle->DevAddr = 0;
	I2C_Handle->Sr = 0;
}
__attribute__((weak)) void I2C_ApplicationEventCallback(I2C_Handle_t *I2C_handle, uint8_t I2C_event)
{

}

void I2C1_EV_IRQHandler(void)
{
	I2C_EV_IRQHandler(&I2C1_handle);
}
void I2C1_ER_IRQHandler(void)
{
	I2C_EV_IRQHandler(&I2C1_handle);
}
void I2C2_EV_IRQHandler(void)
{
	I2C_EV_IRQHandler(&I2C2_handle);
}
void I2C2_ER_IRQHandler (void)
{
	I2C_EV_IRQHandler(&I2C2_handle);
}
