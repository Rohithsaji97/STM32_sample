#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
//#include "usart.h"
#include "adc.h"

int __io_putchar(int ch) {
    ITM_SendChar(ch);
    return ch;
}

uint32_t sensor_value;

int main(void){

//	usart_rxtx_init();
	//This is the new part (Enable SWO debug output)
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

	pa0_adc_init();

	while(1){
		start_conversion();
		sensor_value = adc_read();
		printf("Sensor Value: %d\n\r", (int)sensor_value);
	}
}
