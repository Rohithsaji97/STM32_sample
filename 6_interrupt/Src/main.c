#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "tim.h"
#include "exti.h"

#define GPIOEEN			(1U << 21)

#define PIN9			(1U << 9)
#define PIN8			(1U << 8)

static void exti_callback(void);

int main(void){

	//Enable clock access GPIOE
	RCC -> AHBENR |= GPIOEEN;

	//Set PE9 to output mode
	GPIOE -> MODER |= (1U << 18);
	GPIOE -> MODER &=~(1U << 19);

	//Set PE8 to output mode
	GPIOE -> MODER |= (1U << 16);
	GPIOE -> MODER &=~(1U << 17);

	GPIOE -> ODR ^= PIN9;

	pa0_exti_init();

	while(1){
		GPIOE -> ODR ^= PIN8;
		for (int i = 0; i < 100000; i++){}
	}
}

static void exti_callback(void){
	GPIOE -> ODR ^= PIN9;
}

void EXTI0_IRQHandler(void){
	if((EXTI -> PR & (1U << 0)) != 0){

		//clear PR flag
		EXTI -> PR |= (1U <<0);

		//Do something
		exti_callback();
	}
}
