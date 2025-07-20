#include "stm32f3xx.h"

#define GPIOBEN				(1U << 18)
#define I2C1EN				(1U << 21)

#define ISR_BUSY			(1U << 15)
#define CR2_START			(1U << 13)
#define CR2_STOP			(1U << 14)
#define ISR_ADDR			(1U << 3)
#define ISR_TXE				(1U << 0)
#define ISR_TC				(1U << 6)
#define CR2_AUTOEND			(1U << 25)
#define ISR_RXNE			(1U << 2)

void i2c_init(void){
	//Enable clock access GPIOB
	RCC -> AHBENR |= GPIOBEN;

	//Enable clock access i2c1
	RCC -> APB1ENR |= I2C1EN;

	//Change PB6 and PB7 to alternative function mode
	GPIOB -> MODER |= (1U << 13);
	GPIOB -> MODER &=~ (1U << 12);

	GPIOB -> MODER |= (1U << 15);
	GPIOB -> MODER &=~ (1U << 14);

	//Set Alternative low function register
	GPIOB->AFR[0] &= ~((0xF << 24) | (0xF << 28));
	GPIOB -> AFR[0] |= (4U << 24) | (4U << 28);

	//Set Pin8 and Pin9 to output drain
	GPIOB -> OTYPER |= (1U << 6) | (1U << 7);

	//Enable pull up register
	GPIOB -> PUPDR |= (1U << 12);
	GPIOB -> PUPDR &=~ (1U << 13);

	GPIOB -> PUPDR |= (1U << 14);
	GPIOB -> PUPDR &=~ (1U << 15);

	// Disable I2C
    I2C1->CR1 &=~ (1U << 0);
    // 100kHz @ 8 MHz clock
    I2C1->TIMINGR = 0x2000090E;
    // Enable I2C
    I2C1->CR1 |= (1U << 0);
}

uint8_t i2c_read(char saddr, char maddr){

	//Transmit slave address and write
	//start i2c
	I2C1->CR2 = (saddr << 1) | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;


	//Wait for transfer buffer to be empty
	while(!(I2C1 -> ISR & ISR_TXE)){}

	//Send memory address
	I2C1 -> TXDR = maddr;

	//Wait for transfer to complete
	while(!(I2C1 -> ISR & ISR_TC)){}

	//transfer slave address and read
	//Start again
	I2C1->CR2 = (saddr << 1) | I2C_CR2_RD_WRN | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;


	//Wait till receive
	while(!(I2C1 -> ISR & ISR_RXNE)){}

	//Read data
	uint8_t data = I2C1 -> RXDR;
	while (!(I2C1->ISR & I2C_ISR_TC));
	I2C1->CR2 |= I2C_CR2_STOP;
	return data;
}

void i2c_burstRead(char saddr, char maddr, int n, char *data){
	//wait until bus is free
	while((I2C1 -> ISR & ISR_BUSY)){}

	//Transmit slave address and write
	I2C1 -> CR2 |= (saddr << 1);
	I2C1->CR2 |= (1U << 16);

	//start i2c
	I2C1 -> CR2 |= CR2_START;

//	//Wait until flag is set
//	while(!(I2C1 -> ISR & ISR_ADDR)){}

	//Wait for transfer buffer to be empty
	while(!(I2C1 -> ISR & ISR_TXE)){}

	//Send memory address
	I2C1 -> TXDR = maddr;

	//Wait for transfer to complete
	while(!(I2C1 -> ISR & ISR_TC)){}

	//transfer slave address and read
	I2C1 -> CR2 = (saddr << 1) | 1;
	I2C1->CR2 |= (1U << 16);

	//Start again and autoreset
	I2C1 -> CR2 |= (CR2_START | CR2_AUTOEND);

	while(n > 0U){
		//if one byte
		if (n == 1U){
			//Stop bus
//			I2C1 -> CR2 |= CR2_STOP;

			//Wait till receive
			while(!(I2C1 -> ISR & ISR_RXNE)){}
			*data++ = I2C1 -> RXDR;
			break;
		}
		else{
			while(!(I2C1 -> ISR & ISR_RXNE)){}
			*data++ = I2C1 -> RXDR;
			n--;
		}
	}
}

void i2c_burstWrite(char saddr, char maddr, int n, char *data) {
    // Wait until bus is free
    while (I2C1->ISR & I2C_ISR_BUSY) {}

    // Total bytes: memory address + n data bytes
    int total_bytes = n + 1;

    // Configure CR2 from scratch
    I2C1->CR2 = (saddr << 1)         // 7-bit slave address, write mode (bit 0 = 0)
               | (total_bytes << 16) // NBYTES[7:0]
               | I2C_CR2_START       // Generate START condition
               | I2C_CR2_AUTOEND;    // Generate STOP after transfer complete

    // Send memory address
    while (!(I2C1->ISR & I2C_ISR_TXE)) {}
    I2C1->TXDR = maddr;

    // Send data bytes
    for (int i = 0; i < n; i++) {
        while (!(I2C1->ISR & I2C_ISR_TXE)) {}
        I2C1->TXDR = *data++;
    }

    // Wait for transfer to complete (optional safety)
    while (!(I2C1->ISR & I2C_ISR_TC)) {}
}

void i2c_write(char saddr, char maddr, char data) {

    // Configure CR2 for write (2 bytes: 1 register address + 1 data)
    I2C1->CR2 = (saddr << 1)        // Slave address, write mode
              | (2 << 16)           // NBYTES = 2
              | I2C_CR2_START;       // Generate START

    // Wait for TXIS (transmit interrupt status)
    while (!(I2C1->ISR & I2C_ISR_TXE)) {}
    I2C1->TXDR = maddr; // Send memory/register address

    while (!(I2C1->ISR & I2C_ISR_TXE)) {}
    I2C1->TXDR = data;  // Send the data byte

    // Wait for transfer complete (optional, ensures STOP is sent)
    while (!(I2C1->ISR & I2C_ISR_TC)) {}

    I2C1->CR2 |= I2C_CR2_STOP;
    //    while (I2C1->CR2 & I2C_CR2_STOP);
}
