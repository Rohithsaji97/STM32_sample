#ifndef USART_H_
#define USART_H_
#include<stdint.h>
#include "stm32f3xx.h"

#define ISR_RXNE				(1U << 5)


void usart_tx_init(void);
void usart_rxtx_init(void);
char usart1_read(void);
void usart_rxtx_interupt_init(void);

#endif /* USART_H_ */
