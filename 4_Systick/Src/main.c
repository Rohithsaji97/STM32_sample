#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
#include "adc.h"
#include "systick.h"


#define GPIOEEN				(1U << 21)
#define PIN8				(1U << 9)
#define LED_PIN				PIN8


int main(void){

	RCC -> AHBENR |= GPIOEEN;
	GPIOE -> MODER |= (1U << 18);
	GPIOE -> MODER &=~(1U << 19);


	while(1){
		GPIOE -> ODR ^= LED_PIN;
		systickDelaysMs(2000);
	}
}
