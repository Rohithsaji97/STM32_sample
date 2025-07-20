#include "stm32f3xx.h"
#include "adc.h"

#define GPIOAEN					(1U << 17)

#define ADC1EN					(1U << 28)
#define ADC_CH1					(1U << 6)
#define CR_ADCEN				(1U << 0)
#define CE_ADSTART				(1U << 2)
#define ISR_EOC					(1U << 2)
#define CR_CONT					(1U << 13)
#define CR1_EOCIE				(1U << 2)

void pa0_adc_interrupt_init(void){
	//enable clock access to ADC pin port A
	RCC -> AHBENR |= GPIOAEN;

	//Set the mode of PA0 to analog
	GPIOA -> MODER |= (1U << 0);
	GPIOA -> MODER |= (1U << 1);

	//Enable clock access to ADC
	RCC ->AHBENR |= ADC1EN;

	//Enable EOCIE interrupt
	ADC1 -> IER |= CR1_EOCIE;

	//Enable interrupt in NVIC
	NVIC_EnableIRQ(ADC1_2_IRQn);

	//configure ADC parameters
	//conversion sequence start
	ADC1 -> SQR1 = ADC_CH1;


	//Conversion of sequence length (channel length)
	//Since in the board Sequence register one itself contains length of channel and its already configured to 0000, no further changes are made

	//Enable ADC module
	ADC1 -> CR |= CR_ADCEN;
}

void pa0_adc_init(void){
	//enable clock access to ADC pin port A
	RCC -> AHBENR |= GPIOAEN;

	//Set the mode of PA0 to analog
	GPIOA -> MODER |= (1U << 0);
	GPIOA -> MODER |= (1U << 1);

	//Enable clock access to ADC
	RCC ->AHBENR |= ADC1EN;

	//configure ADC parameters
	//conversion sequence start
	ADC1 -> SQR1 = ADC_CH1;


	//Conversion of sequence length (channel length)
	//Since in the board Sequence register one itself contains length of channel and its already configured to 0000, no further changes are made

	//Enable ADC module
	ADC1 -> CR |= CR_ADCEN;
}

void start_conversion(){
	//Enable start conversion
	ADC1 -> CFGR |= CR_CONT;

	/*Start ADC Conversion*/
	ADC1 -> CR |= CE_ADSTART;
}

uint32_t adc_read(void){
//	Wait for conversion
	while(!(ADC1 ->ISR & ISR_EOC)){}

//	read converted value
	return ADC1 -> DR;
}
