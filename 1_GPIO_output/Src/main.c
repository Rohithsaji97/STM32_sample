#include "stm32f3xx.h"



#define GPIOEEN				(1U << 21)
#define PIN8				(1U << 9)
#define LED_PIN				PIN8


int main(void){
	RCC -> AHBENR |= GPIOEEN;
	GPIOE -> MODER |= (1U << 18);
	GPIOE -> MODER &=~(1U << 19);

	while(1){
		GPIOE -> ODR ^= LED_PIN;
		for(int i = 0; i < 100000; i++){}
	}
}
