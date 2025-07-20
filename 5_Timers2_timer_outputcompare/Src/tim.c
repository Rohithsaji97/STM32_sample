#include "stm32f3xx.h"

#define TIM1_EN				(1U << 11)
#define CR1_CEN				(1U << 0)
#define OC_TOGGLE			((1U << 4) | (1U << 5))
#define CCER_EN1			(1U << 0)

#define GPIOEEN 			(1U << 21)

#define AFR_TIM				(1U << 5)

#define BDTR_MOE			(1U << 15)

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

//#include "stm32f3xx.h"
//
//#define TIM1_EN       (1U << 11)
//#define CR1_CEN       (1U << 0)
//#define OC_TOGGLE     (0x3 << 4)  // OC1M = 011: Toggle
//#define CCER_EN1      (1U << 0)
//#define GPIOEEN       (1U << 21)
//
//void tim1_pe9_output_compare(void){
//	// 1. Enable clock access to GPIOE
//	RCC->AHBENR |= GPIOEEN;
//
//	// 2. Set PE9 to alternate function mode (10)
//	GPIOE->MODER &= ~(0x3 << (2 * 9));   // Clear MODER9
//	GPIOE->MODER |=  (0x2 << (2 * 9));   // Set to AF
//
//	// 3. Set AF2 (TIM1_CH1) on PE9
//	GPIOE->AFR[1] &= ~(0xF << (4 * (9 - 8))); // Clear bits 4–7
//	GPIOE->AFR[1] |=  (0x2 << (4 * (9 - 8))); // AF2 for TIM1_CH1
//
//	// 4. Enable clock access to TIM1
//	RCC->APB2ENR |= TIM1_EN;
//
//	// 5. Set prescaler and auto-reload
//	TIM1->PSC = 800 - 1;     // 72 MHz / 800 = 90 kHz
//	TIM1->ARR = 10000 - 1;   // Period = 0.1111 s (≈9 Hz)
//
//	// 6. Set compare value
//	TIM1->CCR1 = 5000;       // Toggle when CNT = 5000
//
//	// 7. Configure output compare mode to toggle on match
//	TIM1->CCMR1 &= ~(0x7 << 4);  // Clear OC1M bits
//	TIM1->CCMR1 |= OC_TOGGLE;   // Set OC1M to toggle (011)
//
//	// 8. Enable output on CH1
//	TIM1->CCER |= CCER_EN1;
//
//	// 9. Reset counter
//	TIM1->CNT = 0;
//
//	// 10. Enable counter
//	TIM1->CR1 |= CR1_CEN;
//}
//
