#ifndef ADC_H_
#define ADC_H_

#include<stdint.h>

void pa0_adc_init(void);
uint32_t adc_read(void);
void start_conversion();


#endif
