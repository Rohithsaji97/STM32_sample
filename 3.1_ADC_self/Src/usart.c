#include "usart.h"

#define GPIOAEN					(1U << 17)
#define USART1EN				(1U << 14)
#define SYS_FREQ				16000000
#define APB1_CLK				SYS_FREQ
#define USART_BAUDRATE			115200

#define CR1_TE					(1U << 3)
#define CR1_RE					(1U << 2)
#define CR1_UE					(1U << 0)
#define ISR_TXE					(1U << 7)
#define ISR_RXNE				(1U << 5)

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void usart1_write(int ch);

//int __io_putchar(int ch){
//	usart1_write(ch);
//	return ch;
//}

void usart_rxtx_init(void){
	//Configuring USART GPIO Pins
	//Enable clock access
	RCC ->AHBENR |= GPIOAEN;

	//Set PA9 to alternate function mode
	GPIOA -> MODER |= (1U <<19);
	GPIOA -> MODER &=~(1U <<18);

	//Set PA9 alternate function to (AF7)
	GPIOA -> AFR[1] |= (1U << 4);
	GPIOA -> AFR[1] |= (1U << 5);
	GPIOA -> AFR[1] |= (1U << 6);
	GPIOA -> AFR[1] &=~(1U << 7);

	//Set PA10 to alternate function mode
	GPIOA -> MODER |= (1U <<21);
	GPIOA -> MODER &=~(1U <<20);

	//Set PA10 to alternate function
	GPIOA -> AFR[1] |= (1U << 8);
	GPIOA -> AFR[1] |= (1U << 9);
	GPIOA -> AFR[1] |= (1U << 10);
	GPIOA -> AFR[1] &=~(1U << 11);

	//Configure UART module
	//Enable clock access to USART1
	RCC -> APB2ENR |= USART1EN;

	//Configure Baud rate
	uart_set_baudrate(USART1, APB1_CLK, USART_BAUDRATE);

	//configure the transfer direction and Receiver direction
	USART1 -> CR1 = (CR1_TE | CR1_RE);

	//Enable USART module
	USART1 -> CR1 |= CR1_UE;

}

void usart_tx_init(void){
	//Configuring USART GPIO Pins
	//Enable clock access
	RCC ->AHBENR |= GPIOAEN;

	//Set PA9 to alternate function mode
	GPIOA -> MODER |= (1U <<19);
	GPIOA -> MODER &=~(1U <<18);

	//Set PA9 alternate function to (AF7)
	GPIOA -> AFR[1] |= (1U << 4);
	GPIOA -> AFR[1] |= (1U << 5);
	GPIOA -> AFR[1] |= (1U << 6);
	GPIOA -> AFR[1] &=~(1U << 7);

	//Configure UART module
	//Enable clock access to USART1
	RCC -> APB2ENR |= USART1EN;

	//Configure Baud rate
	uart_set_baudrate(USART1, APB1_CLK, USART_BAUDRATE);

	//configure the transfer direction
	USART1 -> CR1 = CR1_TE;

	//Enable USART module
	USART1 -> CR1 |= CR1_UE;

}

char usart1_read(void){
	//Make sure the receiver data register is not empty
	while(!(USART1 -> ISR & ISR_RXNE)){}

	//Read data
	return USART1 -> TDR;
}


void usart1_write(int ch){
	//Make sure the transmit data register is empty
	while(!(USART1 -> ISR & ISR_TXE)){}

	//Write to transmit data
	USART1 -> TDR = (ch && 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate){
	USARTx -> BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
