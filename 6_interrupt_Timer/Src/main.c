#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"


#define GPIOEEN				(1U << 21)
#define PIN8				(1U << 8)
#define PIN13				(1U << 13)

static void tim2_callback(void);

int main(void){

	RCC -> AHBENR |= GPIOEEN;
	GPIOE -> MODER |= (1U << 16);
	GPIOE -> MODER &=~(1U << 17);

	GPIOE -> MODER |= (1U << 26);
	GPIOE -> MODER &=~(1U << 27);

	tim2_1Hz_init();
	tim3_1Hz_interrupt_init();

	while(1){
		//wait for UIF
		while(!(TIM2 -> SR & SR_UIF)){}

		//clear UIF
		TIM2 -> SR &=~  SR_UIF;

		GPIOE -> ODR ^= PIN8;
	}
}

static void tim2_callback(void){
	GPIOE -> ODR ^= PIN13;
}

void TIM3_IRQHandler(void){
	TIM3 -> SR &=~  SR_UIF;
	tim2_callback();
}
