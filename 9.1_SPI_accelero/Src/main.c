#include "stm32f3xx.h"
#include "spi.h"
#include "gyro.h"

GyroData gyro;

void delay(volatile uint32_t d) {
    while (d--) __NOP();
}

int main(void) {
    SPI1_Init();
    GYRO_Init();

    while (1) {
        gyro = GYRO_ReadXYZ();
        delay(50000);  // watch 'gyro' in Live Expressions
    }
}
