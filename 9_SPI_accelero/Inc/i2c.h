#ifndef I2C_H_
#define I2C_H_


#include "stm32f3xx.h"

void I2C1_Init(void);
void I2C1_Write(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C1_Read(uint8_t devAddr, uint8_t regAddr);

#endif
