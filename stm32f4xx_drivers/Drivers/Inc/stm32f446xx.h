/*
 * stm32f446xx.h
 *
 *  Created on: 26 feb 2026
 *      Author: erjo_
 */

#ifndef DRIVERS_INC_STM32F446XX_H_
#define DRIVERS_INC_STM32F446XX_H_
#include <stdint.h>

#define ENABLE 1
#define DISABLE 0

#define AHB1PERIPH_BASEADDR			0x40020000UL
#define APB2PERIPH_BASEADDR			0x40010000UL

/*----------------------- GPIO ----------------------------------*/
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)

/*------------------------- RCC ----------------------------------*/
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)


/*----------------------- Interrupt ----------------------------------*/
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)



/* ---------------------- REGISTROS GPIO --------------------------*/
typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_RegDef_t;


/* ---------------------- REGISTROS RCC --------------------------*/
typedef struct{
	volatile uint32_t CR;            // 0x00 - Clock control register
	    volatile uint32_t PLLCFGR;       // 0x04 - PLL configuration register
	    volatile uint32_t CFGR;          // 0x08 - Clock configuration register
	    volatile uint32_t CIR;           // 0x0C - Clock interrupt register
	    volatile uint32_t AHB1RSTR;      // 0x10 - AHB1 peripheral reset register
	    volatile uint32_t AHB2RSTR;      // 0x14 - AHB2 peripheral reset register
	    volatile uint32_t AHB3RSTR;      // 0x18 - AHB3 peripheral reset register
	    uint32_t          RESERVED0;     // 0x1C - Reservado
	    volatile uint32_t APB1RSTR;      // 0x20 - APB1 peripheral reset register
	    volatile uint32_t APB2RSTR;      // 0x24 - APB2 peripheral reset register
	    uint32_t          RESERVED1[2];  // 0x28, 0x2C - Reservado
	    volatile uint32_t AHB1ENR;       // 0x30 - AHB1 peripheral clock enable register
	    volatile uint32_t AHB2ENR;       // 0x34 - AHB2 peripheral clock enable register
	    volatile uint32_t AHB3ENR;       // 0x38 - AHB3 peripheral clock enable register
	    uint32_t          RESERVED2;     // 0x3C - Reservado
	    volatile uint32_t APB1ENR;       // 0x40 - APB1 peripheral clock enable register
	    volatile uint32_t APB2ENR;       // 0x44 - APB2 peripheral clock enable register
	    uint32_t          RESERVED3[2];  // 0x48, 0x4C - Reservado
	    volatile uint32_t AHB1LPENR;     // 0x50 - AHB1 peripheral clock enable in low power mode register
	    volatile uint32_t AHB2LPENR;     // 0x54 - AHB2 peripheral clock enable in low power mode register
	    volatile uint32_t AHB3LPENR;     // 0x58 - AHB3 peripheral clock enable in low power mode register
	    uint32_t          RESERVED4;     // 0x5C - Reservado
	    volatile uint32_t APB1LPENR;     // 0x60 - APB1 peripheral clock enable in low power mode register
	    volatile uint32_t APB2LPENR;     // 0x64 - APB2 peripheral clock enable in low power mode register
	    uint32_t          RESERVED5[2];  // 0x68, 0x6C - Reservado
	    volatile uint32_t BDCR;          // 0x70 - Backup domain control register
	    volatile uint32_t CSR;           // 0x74 - Clock control & status register
	    uint32_t          RESERVED6[2];  // 0x78, 0x7C - Reservado
	    volatile uint32_t SSCGR;         // 0x80 - Spread spectrum clock generation register
	    volatile uint32_t PLLI2SCFGR;    // 0x84 - PLLI2S configuration register
	    volatile uint32_t PLLSAICFGR;    // 0x88 - PLLSAI configuration register
	    volatile uint32_t DCKCFGR;       // 0x8C - Dedicated clocks configuration register
	    volatile uint32_t CKGATENR;      // 0x90 - Clock gating enable register
	    volatile uint32_t DCKCFGR2;      // 0x94 - Dedicated clocks configuration register 2
}RCC_Reg_Def_t;

/* ---------------------- REGISTROS EXTI --------------------------*/
typedef struct{
	volatile uint32_t	IMR;
	volatile uint32_t 	EMR;
	volatile uint32_t	RTSR;
	volatile uint32_t	FTSR;
	volatile uint32_t	SWIER;
	volatile uint32_t	PR;
}EXTI_Reg_Def_t;

/* ---------------------- REGISTROS SYSCFG --------------------------*/
typedef struct{
	volatile uint32_t	MEMRMP;
	volatile uint32_t	PMC;
	volatile uint32_t	EXTICR1;
	volatile uint32_t	EXTICR2;
	volatile uint32_t	EXTICR3;
	volatile uint32_t	EXTICR4;
	uint32_t 			RES0[2];
	volatile uint32_t	CMPCR;
	uint32_t 			RES1[2];
	volatile uint32_t	CFGR;
}SYSCFG_Reg_Def_t;


/* --------------- Definición de periféricos -------------------*/
/*								GPIO							*/
#define GPIOA			((GPIO_RegDef_t * ) GPIOA_BASEADDR)
#define GPIOB			((GPIO_RegDef_t * ) GPIOB_BASEADDR)
#define GPIOC			((GPIO_RegDef_t * ) GPIOC_BASEADDR)
#define GPIOD			((GPIO_RegDef_t * ) GPIOD_BASEADDR)
#define GPIOE			((GPIO_RegDef_t * ) GPIOE_BASEADDR)
#define GPIOF			((GPIO_RegDef_t * ) GPIOF_BASEADDR)
#define GPIOG			((GPIO_RegDef_t * ) GPIOG_BASEADDR)
#define GPIOH			((GPIO_RegDef_t * ) GPIOH_BASEADDR)


/*								RCC							*/
#define RCC				((RCC_Reg_Def_t *) RCC_BASEADDR)

/*								EXTI							*/
#define EXTI			((EXTI_Reg_Def_t *) EXTI_BASEADDR)

/*								SYSCFG							*/
#define SYSCFG			((SYSCFG_Reg_Def_t *) SYSCFG_BASEADDR)


/* Habilitar clock de perifericos */
#define GPIOA_CLCK_EN()		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_CLCK_EN()		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_CLCK_EN()		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_CLCK_EN()		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_CLCK_EN()		(RCC->AHB1ENR |= (1<<4))
#define GPIOF_CLCK_EN()		(RCC->AHB1ENR |= (1<<5))
#define GPIOG_CLCK_EN()		(RCC->AHB1ENR |= (1<<6))
#define GPIOH_CLCK_EN()		(RCC->AHB1ENR |= (1<<7))

#define SYSCFG_CLCK_EN()	(RCC->APB2ENR |= (1<<14))


/* Deshabilitar clock perifericos */
#define GPIOA_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLCK_DIS()    (RCC->AHB1ENR &= ~(1 << 7))

#define SYSCFG_CLCK_DIS()	(RCC->APB2ENR &= ~(1<<14))

#define GPIOA_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); } while(0)
#define GPIOB_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); } while(0)
#define GPIOC_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); } while(0)
#define GPIOD_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); } while(0)
#define GPIOE_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); } while(0)
#define GPIOF_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); } while(0)
#define GPIOG_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); } while(0)
#define GPIOH_REG_RESET()    do { (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); } while(0)

#define SYSCFG_REG_RESET()	 do { (RCC->APB2RSTR |= (1 << 14)); (RCC->APB2RSTR &= ~(1 << 14); }while(0);
#endif /* DRIVERS_INC_STM32F446XX_H_ */
