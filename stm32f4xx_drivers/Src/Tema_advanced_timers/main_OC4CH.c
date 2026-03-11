#include "BSP_TIM_ICOC.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"

int main(void)
{
	TIM2_OC_4Channels_GPIO_Setup();
	TIM2_OC_TOGGLE_4Channels_Setup();

	TIM_Cmd(h_tim2.pTIMx, ENABLE);
	while(1);

	return 1;
}
