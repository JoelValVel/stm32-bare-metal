#include "BSP_SPI.h"

SPI_Handle_t SPI1_handle = {0};
SPI_Handle_t SPI2_handle = {0};
void SPI1_Setup(void)
{
	SPI1_handle.pSPIx = SPI1;
	SPI1_handle.SPIConfig.BusConfig = SPI_BusConfig_FullDuplex;
	SPI1_handle.SPIConfig.DeviceMode = SPI_DeviceMode_Master;
	SPI1_handle.SPIConfig.Prescaler = SPI_Prescaler_256;
	SPI1_handle.SPIConfig.DataFrmat = SPI_DataFrmat_8bit;
	SPI1_handle.SPIConfig.NSS = SPI_NSS_Disable;

	SPI_Init(&SPI1_handle);
	// un master
	SPI1->SPI_CR2 |= (0x01 << SPI_CR2_SSOE);
}

void SPI2_Setup(void)
{
	SPI2_handle.pSPIx = SPI2;
	SPI2_handle.SPIConfig.BusConfig = SPI_BusConfig_FullDuplex;
	SPI2_handle.SPIConfig.DeviceMode = SPI_DeviceMode_Master;
	SPI2_handle.SPIConfig.Prescaler = SPI_Prescaler_256;
	SPI2_handle.SPIConfig.DataFrmat = SPI_DataFrmat_8bit;
	SPI2_handle.SPIConfig.NSS = SPI_NSS_Disable;

	SPI_Init(&SPI2_handle);
	// un master
	SPI2->SPI_CR2 |= (0x01 << SPI_CR2_SSOE);
}

