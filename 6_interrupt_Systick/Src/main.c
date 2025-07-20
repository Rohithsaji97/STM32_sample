#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"


#define GPIOEEN				(1U << 21)
#define PIN9				(1U << 9)
#define PIN11				(1U << 11)

static void systick_callback(void);


int main(void){

	RCC -> AHBENR |= GPIOEEN;
	GPIOE -> MODER |= (1U << 18);
	GPIOE -> MODER &=~(1U << 19);

	GPIOE -> MODER |= (1U << 22);
	GPIOE -> MODER &=~(1U << 23);

	systick_1hz_interrupt();


	while(1){
		GPIOE -> ODR ^= PIN9;
		for (int i = 0; i < 100000; i++){}
	}
}

static void systick_callback(void){
	GPIOE -> ODR ^= PIN11;
}

void SysTick_Handler(void){
	systick_callback();
}
