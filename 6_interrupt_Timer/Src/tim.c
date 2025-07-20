#include "stm32f3xx.h"

#define TIM2_EN				(1U << 0)
#define CR1_CEN				(1U << 0)

#define TIM3_EN				(1U << 1)
#define DIER_UIE			(1U << 0)

void tim2_1Hz_init(void){
	//Enable clock access to tim2
	RCC -> APB1ENR |= TIM2_EN;

	//Set prescalar value
	TIM2 -> PSC = 800 - 1; // 8000 000 / 800 = 10000

	//Set auto reload value
	TIM2 -> ARR = 10000 - 1;

	//Clear counter
	TIM2 -> CNT  = 0;

	//Enable timer
	TIM2 -> CR1 = CR1_CEN;
}

void tim3_1Hz_interrupt_init(void){
	//Enable clock access to tim2
	RCC -> APB1ENR |= TIM3_EN;

	//Set prescalar value
	TIM3 -> PSC = 400 - 1; // 8000 000 / 800 = 10000

	//Set auto reload value
	TIM3 -> ARR = 10000 - 1;

	//Clear counter
	TIM3 -> CNT  = 0;

	//Enable timer
	TIM3 -> CR1 = CR1_CEN;

	//Enable TIM interrupt
	TIM3 -> DIER = DIER_UIE;

	//Enable in NVIC
	NVIC_EnableIRQ(TIM3_IRQn);
}
