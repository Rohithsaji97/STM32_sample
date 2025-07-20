#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
//#define GPIOEEN				(1U << 21)

#define GPIOEEN					(1U << 21)
#define PIN8					(1U<<8)
#define LED_PIN					PIN8

char key;

int main(void){


	RCC -> AHBENR |= GPIOEEN;

	GPIOE -> MODER |= (1U << 16);
	GPIOE -> MODER &=~(1U << 17);

	usart_rxtx_init();
	usart_rxtx_interupt_init();

	while(1){
		key = usart1_read();
		if (key == '1'){
			GPIOE -> ODR |= LED_PIN;
		}
		else {
			GPIOE -> ODR |= ~LED_PIN;
		}
	}
}

void USART1_IRQHandler(){
	if(USART1 -> ISR & ISR_RXNE){
		key = USART1 -> TDR;
	}
}
