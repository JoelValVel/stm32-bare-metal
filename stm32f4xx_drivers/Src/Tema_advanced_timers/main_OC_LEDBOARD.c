#include "BSP_TIM_ICOC.h"
#include "RCC_config_BSP.h"
#include "GPIO_BSP.h"

int main(void){
	TIM2_CH2OC_GPIO_Init();
	TIM2_OC_TOGGLE_Setup();
	TIM_Cmd(h_tim2.pTIMx, ENABLE);
	while(1);
	return 1;
}
