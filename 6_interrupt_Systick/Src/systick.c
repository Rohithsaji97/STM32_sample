#include "stm32f3xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VAL		8000
#define CTRL_ENABLE				(1U << 0)
#define CTRL_CLKSRC				(1U << 2)
#define CTRL_COUNTFLAG			(1U << 16)
#define CTRL_TICKINT			(1U << 1)

#define ONE_SEC_LOAD			8000000

void systickDelaysMs(int delay){
	//Configure systick
	//Reload with number of clocks per millisecond
	SysTick -> LOAD = SYSTICK_LOAD_VAL;

	//Clear current systick value register
	SysTick -> CTRL = 0;

	//Enable systick and select clock source (AHB or AHB/8)
	SysTick -> CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for (int i = 0; i < delay; i++){
//		Wait until count flag is set
		while((SysTick -> CTRL & CTRL_COUNTFLAG) == 0){}
	}
	SysTick -> CTRL = 0;
}

void systick_1hz_interrupt(void){
	//Reload with number of clocks
	SysTick -> LOAD = ONE_SEC_LOAD - 1;

	//Clear systick current value
	SysTick -> VAL = 0;

	//Enable systick and select clock source (AHB or AHB/8)
	SysTick -> CTRL = CTRL_ENABLE | CTRL_CLKSRC;

//	Enable systick interrupt
	SysTick -> CTRL |= CTRL_TICKINT;
}
