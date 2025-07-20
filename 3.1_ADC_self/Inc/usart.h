#ifndef USART_H_
#define USART_H_
#include<stdint.h>
#include "stm32f3xx.h"

void usart_tx_init(void);
void usart_rxtx_init(void);
char usart1_read(void);

#endif /* USART_H_ */
