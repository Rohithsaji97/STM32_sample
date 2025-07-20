#ifndef ADC_H_
#define ADC_H_

#include<stdint.h>

#define SR_EOC		(1U << 2)

void pa0_adc_init(void);
uint32_t adc_read(void);
void start_conversion();
void pa0_adc_interrupt_init(void);


#endif
