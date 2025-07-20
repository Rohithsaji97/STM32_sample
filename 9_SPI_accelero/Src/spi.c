//#include "spi.h"
//
//#define SPI1EN			(1U << 12)
//#define GPIOAEN			(1U << 17)
//#define SR_TXE			(1U << 1)
//#define SR_BSY			(1U << 7)
//#define SR_RXNE			(1U << 0)
////PA5 - CLK
////PA6 - MISO
////PA7 - MOSI
////PA9 - SS
//
//void spi_gpio_init(void){
//	//Enable GPIOA
//	RCC -> AHBENR |= GPIOAEN;
//
//	//Enable alternate functions for PA 5, 6, 7
//	GPIOA -> MODER |= (1U << 11) | (1U << 13) | (1U << 15);
//
//	//Set PA9 as output pin
//	GPIOA -> MODER |= (1U << 18);
//
//	//Make alternate functions in AFR
//	GPIOA -> AFR[0] |= (1U << 20) | (1U << 22) | (1U << 24) | (1U <<26) | (1U <<28) | (1U << 30);
//
//}
//
//void spi1_config(void){
//	//Enable SPI1 clock
//	RCC -> APB2ENR |= SPI1EN;
//
//	//Set baud rate (peripheral clock divided speed)
//	SPI1 -> CR1 |= (1U << 3);
//
//	//Set CPOL and CPHA
//	SPI1 -> CR1 |= (1U << 0) | (1U << 1);
//
//	//Enable full duplex
//	SPI1 -> CR1 &=~ (1U << 10);
//
//	//Set MSB bit first
//	SPI1 -> CR1 &=~ (1U << 7);
//
//	//Set mode to Master configuration
//	SPI1 -> CR1 |= (1U << 2);
//
//	//Set 8 bit mode
//	SPI1 -> CR1 &=~ (1U << 11);
//
//	//Enable SSM and SSI
//	SPI1 -> CR1 |= (1U << 9) | (1U << 8);
//
//	//Enable SPI
//	SPI1 -> CR1 |= (1U << 6);
//}
//
//void spi1_transmit(uint8_t *data, uint32_t size){
//	uint32_t i = 0;
//	uint8_t temp;
//
//	while(i < size){
//		//wait for txe to set
//		while(!(SPI1 -> SR & SR_TXE)){}
//
//		//write data to the data register
//		SPI1 -> DR = data[i];
//		i++;
//	}
//	//wait for txe to set
//	while(!(SPI1 -> SR & SR_TXE)){}
//
//	//Wait for busy flag to reset
//	while((SPI1 -> SR & SR_BSY)){}
//
//	//clear ovr flag in manual shows how its done (ie to read dr register followed by reading sr register)
//	temp = SPI1 -> DR;
//	temp = SPI1 -> SR;
//}
//
//void spi1_recieve(uint8_t *data, uint32_t size){
//	while(size){
//		//Send dummy data
//		SPI1 -> DR = 0;
//
//		//wait for rxe
//		while(!(SPI1 -> SR & SR_RXNE)){}
//
//		//Read data from register
//		*data++ = SPI1 -> DR;
//		size--;
//	}
//}
//
////pull low to enable
//void cs_enable(void){
//	GPIOA -> ODR &=~ (1U << 9);
//}
//
////pull high to disable
//void cs_disable(void){
//	GPIOA -> ODR |= (1U << 9);
//}


#include "spi.h"

#define SPI1EN          (1U << 12)
#define GPIOAEN         (1U << 17)
#define SR_TXE          (1U << 1)
#define SR_BSY          (1U << 7)
#define SR_RXNE         (1U << 0)
//PA5 - CLK
//PA6 - MISO
//PA7 - MOSI
//PA9 - SS

void spi_gpio_init(void){
    // Enable GPIOA
    RCC->AHBENR |= GPIOAEN;

    // Set PA5, PA6, PA7 to alternate function mode (10)
    GPIOA->MODER &= ~((3U << 10) | (3U << 12) | (3U << 14));
    GPIOA->MODER |= ((2U << 10) | (2U << 12) | (2U << 14));

    // Set PA9 as general purpose output (01)
    GPIOA->MODER &= ~(3U << 18);
    GPIOA->MODER |= (1U << 18);

    // Set AFR for PA5, PA6, PA7 to AF5 (SPI1)
    GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 24) | (0xF << 28));
    GPIOA->AFR[0] |= ((5U << 20) | (5U << 24) | (5U << 28));
}

void spi1_config(void){
    // Enable SPI1 clock
    RCC->APB2ENR |= SPI1EN;

    // Set baud rate (peripheral clock divided speed)
    SPI1->CR1 |= (1U << 3);

    // Set CPOL and CPHA
    SPI1->CR1 |= (1U << 0) | (1U << 1);

    // Enable full duplex
    SPI1->CR1 &= ~(1U << 10);

    // Set MSB bit first
    SPI1->CR1 &= ~(1U << 7);

    // Set mode to Master configuration
    SPI1->CR1 |= (1U << 2);

    // Set 8 bit mode
    SPI1->CR1 &= ~(1U << 11);

    // Enable SSM and SSI
    SPI1->CR1 |= (1U << 9) | (1U << 8);

    // Enable SPI
    SPI1->CR1 |= (1U << 6);
}

void spi1_transmit(uint8_t *data, uint32_t size){
    uint32_t i = 0;
    uint8_t temp;

    while(i < size){
        // Wait for TXE to set
        while(!(SPI1->SR & SR_TXE)) {}

        // Write data to the data register
        SPI1->DR = data[i];
        i++;
    }
    // Wait for TXE to set
    while(!(SPI1->SR & SR_TXE)) {}

    // Wait for busy flag to reset
    while((SPI1->SR & SR_BSY)) {}

    // Clear OVR flag by reading DR then SR
    temp = SPI1->DR;
    temp = SPI1->SR;
}

void spi1_recieve(uint8_t *data, uint32_t size){
    while(size){
        // Send dummy data
        SPI1->DR = 0;

        // Wait for RXNE
        while(!(SPI1->SR & SR_RXNE)) {}

        // Read data from register
        *data++ = SPI1->DR;
        size--;
    }
}

// Pull low to enable
void cs_enable(void){
    GPIOA->ODR &= ~(1U << 9);
}

// Pull high to disable
void cs_disable(void){
    GPIOA->ODR |= (1U << 9);
}
