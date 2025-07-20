#include "stm32f3xx.h"

#define TIM1_EN				(1U << 11)
#define TIM3_EN				(1U << 1)

#define CR1_CEN				(1U << 0)
#define OC_TOGGLE			((1U << 4) | (1U << 5))
#define CCER_EN1			(1U << 0)

#define GPIOEEN 			(1U << 21)
#define GPIOAEN				(1U << 17)


#define AFR_TIM				(1U << 5)
#define AFR6_TIM			(1U << 25)

#define BDTR_MOE			(1U << 15)
#define CCER_CC1S			(1U << 0)

void tim1_pe9_output_compare(void){
	//Enable clock access to GPIOE
	RCC -> AHBENR |= GPIOEEN;

	//Set alternative function to PE9
	GPIOE -> MODER |= (1U <<19);
	GPIOE -> MODER &=~ (1U <<18);

	//Set PE8 to TIM1_CH1 configuration
	GPIOE -> AFR[1] = AFR_TIM;

	//Enable clock access to tim1
	RCC -> APB2ENR |= TIM1_EN;

	//Set prescalar value
	TIM1 -> PSC = 800 - 1; // 8000 000 / 800 = 10000

	//Set auto reload value
	TIM1 -> ARR = 10000 - 1;

	//////////Set output compare toggle
	TIM1 -> CCMR1 |= OC_TOGGLE;

	//Enable tim1 ch1 in compare mode
	TIM1 -> CCER |= CCER_EN1;

	//Enable main output (MOE) in BDTR (required for advanced timers)
	TIM1-> BDTR |= BDTR_MOE;

	//Clear counter
	TIM1 -> CNT  = 0;

	//Enable timer
	TIM1 -> CR1 = CR1_CEN;
}

void tim3_pa6_input_capture(void){
	//Enable clock access
	RCC -> AHBENR |= GPIOAEN;

	//Set PA6 to alternate function
	GPIOA -> MODER |= (1U << 13);
	GPIOA -> MODER &=~ (1U << 12);

	//Set alternate function to AF2
	GPIOA -> AFR[0] |= AFR6_TIM;

	//Enable clock access to TIM3
	RCC -> APB1ENR |= TIM3_EN;

	//Set prescalar
	TIM3 -> PSC = 8000 - 1;

	//Set CH1 to capture at every edges
	TIM3 -> CCMR1 = CCER_CC1S;

	//Set CH1 to capture at rising stage
	TIM3 -> CCER = CCER_EN1;

	//Enable TIM3
	TIM3 -> CR1 = CR1_CEN;

}
