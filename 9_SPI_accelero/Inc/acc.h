#ifndef ACC_H_
#define ACC_H_

#include "stm32f3xx.h"

void ACC_Init(void);
void ACC_Read(int16_t *x, int16_t *y, int16_t *z);

#endif
