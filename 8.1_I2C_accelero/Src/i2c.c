#include "i2c.h"

void I2C1_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;   // Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;  // Enable I2C1 clock

    // Configure PB6 (SCL) and PB7 (SDA)
    GPIOB->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    GPIOB->MODER |= (2 << GPIO_MODER_MODER6_Pos) | (2 << GPIO_MODER_MODER7_Pos); // AF
    GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFRL6_Pos) | (4 << GPIO_AFRL_AFRL7_Pos);     // AF4
    GPIOB->OTYPER |= GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7;                         // Open-drain
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7;
    GPIOB->PUPDR |= (1 << GPIO_PUPDR_PUPDR6_Pos) | (1 << GPIO_PUPDR_PUPDR7_Pos); // Pull-up

    // Reset I2C
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->TIMINGR = 0x00B01A4B; // Configure timing for 100kHz @ 8MHz
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_Write(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    I2C1->CR2 = (devAddr << 1) | (2 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = regAddr;
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = data;
    while (!(I2C1->ISR & I2C_ISR_TC));
    I2C1->CR2 |= I2C_CR2_STOP;
    while (I2C1->CR2 & I2C_CR2_STOP);
}

uint8_t I2C1_Read(uint8_t devAddr, uint8_t regAddr) {
    // Write register address
    I2C1->CR2 = (devAddr << 1) | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = regAddr;
    while (!(I2C1->ISR & I2C_ISR_TC));

    // Read data
    I2C1->CR2 = (devAddr << 1) | I2C_CR2_RD_WRN | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    while (!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data = I2C1->RXDR;
    while (!(I2C1->ISR & I2C_ISR_TC));
    I2C1->CR2 |= I2C_CR2_STOP;
    return data;
}

