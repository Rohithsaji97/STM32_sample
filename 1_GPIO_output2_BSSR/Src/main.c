#include "stm32f3xx.h"



#define GPIOEEN				(1U << 21)
#define PIN8				(1U << 8)
#define LED_PIN				PIN8


int main(void){
	RCC -> AHBENR |= GPIOEEN;
	GPIOE -> MODER |= (1U << 16);
	GPIOE -> MODER &=~(1U << 17);

	while(1){
		GPIOE -> BSRR = LED_PIN;
		for(int i = 0; i < 100000; i++){}

		GPIOE -> BSRR = (1U << 24);
		for(int i = 0; i < 100000; i++){}
	}
}
