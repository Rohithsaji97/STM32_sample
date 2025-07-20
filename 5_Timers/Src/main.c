#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"


#define GPIOEEN				(1U << 21)
#define PIN8				(1U << 8)
#define LED_PIN				PIN8


int main(void){

	RCC -> AHBENR |= GPIOEEN;
	GPIOE -> MODER |= (1U << 16);
	GPIOE -> MODER &=~(1U << 17);

	tim2_1Hz_init();

	while(1){
		//wait for UIF
		while(!(TIM2 -> SR & SR_UIF)){}

		//clear UIF
		TIM2 -> SR &=~  SR_UIF;

		GPIOE -> ODR ^= LED_PIN;
	}
}
