#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
#include "adc.h"

uint32_t sensor_value;

static void adc_callback(void);

#define GPIOEEN			(1U << 21)

#define PIN9			(1U << 9)
#define PIN8			(1U << 8)

int main(void){

	usart_rxtx_init();
	pa0_adc_interrupt_init();
	start_conversion();

	//Enable clock access GPIOE
	RCC -> AHBENR |= GPIOEEN;

	//Set PE9 to output mode
	GPIOE -> MODER |= (1U << 18);
	GPIOE -> MODER &=~(1U << 19);

	//Set PE8 to output mode
	GPIOE -> MODER |= (1U << 16);
	GPIOE -> MODER &=~(1U << 17);

	GPIOE -> ODR ^= PIN9;

	while(1){
		GPIOE -> ODR ^= PIN8;
		for (int i = 0; i < 100000; i++){}
	}
}

static void adc_callback(void){
	GPIOE -> ODR ^= PIN9;
}

void ADC1_2_IRQHandler(void){
	//check for EOC status register
	if((ADC1 -> ISR &  SR_EOC) != 0){
		//Clear EOC
		ADC1 -> ISR |= SR_EOC;

		adc_callback();
	}

}
