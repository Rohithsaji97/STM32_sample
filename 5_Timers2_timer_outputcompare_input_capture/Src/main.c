#include<stdio.h>
#include<stdint.h>
#include "stm32f3xx.h"
#include "tim.h"

int timestamp = 0;

//connect a jumper wire from PE9 to PA6

int main(void){

	tim1_pe9_output_compare();
	tim3_pa6_input_capture();

	while(1){
		//Wait unyill edge is captured
		while(!(TIM3 -> SR & SR_CC1IF)){}

		//Read value
		timestamp = TIM3 -> CCR1;
	}
}
