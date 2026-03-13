#include "BSP_WWDG.h"

WWDG_Config_t	WWDG_config = {0};
void WWDG_Setup(void)
{
	// tiempo minimo 10ms
	// tiempo máximo 25 ms
	WWDG_config.WWDG_Counter = 0x7F;
	WWDG_config.WWDG_Prescaler = WWDG_Prescaler_4096x4;
	WWDG_config.WWDG_Window = 97; //valor maximo del contador 7 bits

	WWDG_Init(&WWDG_config);
}
