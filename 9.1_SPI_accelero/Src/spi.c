#include "spi.h"

#define SPI_CS_PIN   (1U << 6)   // PB6 as Chip Select
#define SPI_CS_PORT  GPIOB

void SPI1_Init(void) {
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // PA5=SCK, PA6=MISO, PA7=MOSI set to AF5
    GPIOA->MODER &= ~((3 << 10)|(3 << 12)|(3 << 14));
    GPIOA->MODER |=  ((2 << 10)|(2 << 12)|(2 << 14));
    GPIOA->AFR[0] |= (5 << 20)|(5 << 24)|(5 << 28);

    // PB6 as CS output, push-pull, high speed, no pull-up/down
    GPIOB->MODER &= ~(3 << 12);
    GPIOB->MODER |=  (1 << 12);
    GPIOB->OTYPER &= ~SPI_CS_PIN;
    GPIOB->OSPEEDR |= (3 << 12);
    GPIOB->PUPDR &= ~(3 << 12);
    GPIOB->ODR |= SPI_CS_PIN;

    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;
}

uint8_t SPI1_TransmitReceive(uint8_t data) {
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_RXNE));
    return (uint8_t)SPI1->DR;
}

void SPI1_CS_Enable(void) {
    SPI_CS_PORT->ODR &= ~SPI_CS_PIN;
}

void SPI1_CS_Disable(void) {
    SPI_CS_PORT->ODR |= SPI_CS_PIN;
}
