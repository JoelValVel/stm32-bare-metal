#include "BSP_IWDG.h"

void IWDG_Setup(void)
{
	IWDG_Config_t IWDG_config = {0};
	IWDG_config.IWDG_Prescaler = 4;
	IWDG_config.IWDG_Period = 0xFFF;

	IWDG_Init(&IWDG_config);
}
