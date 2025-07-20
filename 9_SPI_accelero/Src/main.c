#include "spi.h"
#include "gyro.h"
#include "stm32f3xx.h"

uint8_t data_rec[6];
#define OUT_X_L        0x28

int main(void) {
    int16_t x = 0, y = 0, z = 0;

    spi_gpio_init();
    spi1_config();
    gyro_init();

    while (1) {
        gyro_read_address(OUT_X_L, data_rec);

        x = ((data_rec[1] << 8) | data_rec[0]);
        y = ((data_rec[3] << 8) | data_rec[2]);
        z = ((data_rec[5] << 8) | data_rec[4]);

        for (uint8_t i = 0; i < 100000; i++);
    }
}
