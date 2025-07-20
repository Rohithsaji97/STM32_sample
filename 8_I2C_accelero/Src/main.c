#include <stdint.h>
#include "stm32f3xx.h"
#include "acc.h"
#include "i2c.h"

int16_t ax = 0, ay = 0, az = 0;

int main(void) {
	i2c_init(); // Initialize I2C peripheral
    acc_init();  // Initialize accelerometer

    while (1) {
        acc_read(&ax, &ay, &az);
        for (volatile int i = 0; i < 100000; ++i);
    }
}
