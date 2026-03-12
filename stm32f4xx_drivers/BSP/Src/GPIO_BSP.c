#include "GPIO_BSP.h"

void MCO1_GPIO_Init(void)
{
	GPIO_handle_t MCO1_pin;
	MCO1_pin.pGPIOx = GPIOA;
	MCO1_pin.GPIO_config.GPIO_pin = GPIO_PIN_8;
	MCO1_pin.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	MCO1_pin.GPIO_config.GPIO_OType = GPIO_OType_PP;
	MCO1_pin.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	MCO1_pin.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	MCO1_pin.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_0;
	GPIO_Init(&MCO1_pin);
}

void TIM5_CH1IC_GPIO_Init(void)
{
GPIO_handle_t TIM5_CH1 = {0};
TIM5_CH1.pGPIOx = GPIOA;
TIM5_CH1.GPIO_config.GPIO_pin = GPIO_PIN_0;
TIM5_CH1.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
TIM5_CH1.GPIO_config.GPIO_OType = GPIO_OType_PP;
TIM5_CH1.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
TIM5_CH1.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_2;
GPIO_Init(&TIM5_CH1);
}



void TIM5_CH2_GPIO_Init(void)
{
	GPIO_handle_t TIM2_CH2 = {0};
	TIM2_CH2.pGPIOx = GPIOA;
	TIM2_CH2.GPIO_config.GPIO_pin = GPIO_PIN_1;
	TIM2_CH2.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM2_CH2.GPIO_config.GPIO_OType = GPIO_OType_PP;
	TIM2_CH2.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	TIM2_CH2.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
	GPIO_Init(&TIM2_CH2);
}

void TIM2_CH1OC_GPIO_Init(void)
{
GPIO_handle_t TIM2_CH1 = {0};
TIM2_CH1.pGPIOx = GPIOA;
TIM2_CH1.GPIO_config.GPIO_pin = GPIO_PIN_5;
TIM2_CH1.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
TIM2_CH1.GPIO_config.GPIO_OType = GPIO_OType_PP;
TIM2_CH1.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
TIM2_CH1.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
GPIO_Init(&TIM2_CH1);
}

void TIM2_CH1PWM_GPIO_Init(void)
{
GPIO_handle_t TIM2_CH1 = {0};
TIM2_CH1.pGPIOx = GPIOA;
TIM2_CH1.GPIO_config.GPIO_pin = GPIO_PIN_5;
TIM2_CH1.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
TIM2_CH1.GPIO_config.GPIO_OType = GPIO_OType_PP;
TIM2_CH1.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
TIM2_CH1.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
GPIO_Init(&TIM2_CH1);
}


GPIO_handle_t PC10_debug = {0};
void RCC_debug_GPIO_setup(void)
{
	PC10_debug.pGPIOx = GPIOC;
	PC10_debug.GPIO_config.GPIO_pin = GPIO_PIN_10;
	PC10_debug.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	PC10_debug.GPIO_config.GPIO_OType = GPIO_OType_PP;
	PC10_debug.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	PC10_debug.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	GPIO_Init(&PC10_debug);
}
void RCC_debug_GPIO_Toggle(void)
{
	GPIO_TogglePin(PC10_debug.pGPIOx, PC10_debug.GPIO_config.GPIO_pin);
}

void TIM2_OC_4Channels_GPIO_Setup(void)
{
	GPIO_handle_t TIM2_PIN = {0};
	TIM2_PIN.pGPIOx = GPIOA;
	TIM2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_0;
	TIM2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	TIM2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
	GPIO_Init(&TIM2_PIN);

	TIM2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_1;
	GPIO_Init(&TIM2_PIN);

	TIM2_PIN.pGPIOx = GPIOB;
	TIM2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_10;
	GPIO_Init(&TIM2_PIN);

	TIM2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_2;
	GPIO_Init(&TIM2_PIN);
}
