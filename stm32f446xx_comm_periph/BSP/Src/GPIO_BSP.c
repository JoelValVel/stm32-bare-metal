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

void SPI1_GPIO_Setup(void)
{
	GPIO_handle_t SPI1_PIN = {0};
	SPI1_PIN.pGPIOx = GPIOA;
	SPI1_PIN.GPIO_config.GPIO_pin = GPIO_PIN_7;
	SPI1_PIN.GPIO_config.GPIO_OType = GPIO_OType_PP;
	SPI1_PIN.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	SPI1_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	SPI1_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	SPI1_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_5;

	// SPI1 MOSI
	GPIO_Init(&SPI1_PIN);

	// SPI1 MISO
	SPI1_PIN.GPIO_config.GPIO_pin = GPIO_PIN_6;
	GPIO_Init(&SPI1_PIN);

	// SPI1 SCK
	SPI1_PIN.GPIO_config.GPIO_pin = GPIO_PIN_5;
	GPIO_Init(&SPI1_PIN);

	// SPI1 NSS
	SPI1_PIN.GPIO_config.GPIO_pin = GPIO_PIN_4;
	GPIO_Init(&SPI1_PIN);

}
void SPI2_GPIO_Setup(void)
{
	GPIO_handle_t SPI2_PIN = {0};
	SPI2_PIN.pGPIOx = GPIOB;
	SPI2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_15;
	SPI2_PIN.GPIO_config.GPIO_OType = GPIO_OType_PP;
	SPI2_PIN.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	SPI2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	SPI2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	SPI2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_5;

	// SPI2 MOSI
	GPIO_Init(&SPI2_PIN);

	// SPI2 MISO
	SPI2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_14;
	GPIO_Init(&SPI2_PIN);

	// SPI2 SCK
	SPI2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_13;
	GPIO_Init(&SPI2_PIN);

	// SPI2 NSS
	SPI2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_12;
	GPIO_Init(&SPI2_PIN);

}
void I2C2_GPIO_Setup(void)
{
	GPIO_handle_t I2C2_PIN = {0};
	I2C2_PIN.pGPIOx = GPIOB;
	I2C2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_10;
	I2C2_PIN.GPIO_config.GPIO_OType = GPIO_OType_OD;
	I2C2_PIN.GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
	I2C2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	I2C2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	I2C2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_4;

	// I2C SCL
	GPIO_Init(&I2C2_PIN);

	// SPI2 SDA
	I2C2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_3;
	GPIO_Init(&I2C2_PIN);
}

void USART2_GPIO_Setup(void)
{
	GPIO_handle_t USART2_PIN = {0};

	USART2_PIN.pGPIOx = GPIOA;
	USART2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_2;
	USART2_PIN.GPIO_config.GPIO_OType = GPIO_OType_PP;
	USART2_PIN.GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;
	USART2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	USART2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FS;
	USART2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_7;

	// USART2 TX
	GPIO_Init(&USART2_PIN);

	// USART2 RX
	USART2_PIN.GPIO_config.GPIO_pin = GPIO_PIN_3;
	GPIO_Init(&USART2_PIN);

}
