#define GPIOAEN			(1U << 17)
#define SYSCFGEN		(1U << 0)

#include "exti.h"

void pa0_exti_init(void){
	//Disable global interrupt
	__disable_irq();

	//Enable global access GPIOA
	RCC -> AHBENR |= GPIOAEN;

	//Set PA0 as input pin
	GPIOA -> MODER &=~ (1U << 0);
	GPIOA -> MODER &=~ (1U << 1);

	//Enable clock access to SYSCFG
	RCC -> APB1ENR |= SYSCFGEN;

	//Select port A for EXTI0
	SYSCFG -> EXTICR[0] = 0;	//Since to connect pin 0 of port A we need 0000

	//Unmase EXTI0
	EXTI -> IMR |= (1U << 0);

	//Select falling edge trigger
	EXTI -> FTSR |= (1U << 0);

	//Enable EXTI0 line in NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);

	//Enable global interrupt
	__enable_irq();

}
