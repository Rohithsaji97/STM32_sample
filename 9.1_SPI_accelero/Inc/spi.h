#ifndef SPI_H
#define SPI_H

#include "stm32f3xx.h"

void SPI1_Init(void);
uint8_t SPI1_TransmitReceive(uint8_t data);
void SPI1_CS_Enable(void);
void SPI1_CS_Disable(void);

#endif // SPI_H
