#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "usart.h"
#include "adc.h"

uint32_t sensor_value;

int main(void){

	usart_rxtx_init();
	pa0_adc_init();
	start_conversion();


	while(1){
		sensor_value = adc_read();
		printf("Sensor Value: %d\n\r", (int)sensor_value);
	}
}
