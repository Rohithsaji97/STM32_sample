#include "stm32f3xx.h"
#include "i2c.h"
#include "acc.h"

int16_t acc_x = 0, acc_y = 0, acc_z = 0;

int main(void) {
    I2C1_Init();
    ACC_Init();

    while (1) {
        ACC_Read(&acc_x, &acc_y, &acc_z);
        for (volatile int i = 0; i < 100000; ++i); // Simple delay
    }
}
