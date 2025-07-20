#include "stm32f3xx.h"

#define TIM2_EN				(1U << 0)
#define CR1_CEN				(1U << 0)

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
