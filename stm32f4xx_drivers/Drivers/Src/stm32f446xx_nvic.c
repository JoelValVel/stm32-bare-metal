#include "stm32f446xx_nvic.h"

void NVIC_IRQ_Enable(uint8_t IRQ){
	if(IRQ<32){
		NVIC_ISER0 |= (1<<IRQ);
	}
	else if (32<=IRQ<64){
		NVIC_ISER1 |= (1<<(IRQ-32));
	}
	else if(64<=IRQ<96){
		NVIC_ISER2 |= (1<<(IRQ-64));
	}

}
void NVIC_IRQ_Disable(uint8_t IRQ){
	if(IRQ<32){
		NVIC_ICER0 |= (1<<IRQ);
	}
	else if (32<=IRQ<64){
		NVIC_ICER1 |= (1<<(IRQ-32));
	}
	else if(64<=IRQ<96){
		NVIC_ICER2 |= (1<<(IRQ-64));
	}
}
void NVIC_Priority(uint8_t IRQ, uint32_t priority){
	uint8_t regidx, blkidx;
	volatile uint32_t *pNVIC_IPR = (uint32_t *)(NVIC_IPR_BASEADDR + regidx * 4);
	regidx = IRQ / 4;
	blkidx = IRQ % 4;

	*pNVIC_IPR &= ~(0xFF << (blkidx*8));
	*pNVIC_IPR |= (priority << (blkidx * 8 + 4));

}
