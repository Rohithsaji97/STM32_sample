#include "acc.h"
#include "i2c.h"

#define LSM303_ACC_ADDR 0x19

void ACC_Init(void) {
    // Enable accelerometer, 50Hz, all axes
    I2C1_Write(LSM303_ACC_ADDR, 0x20, 0x47);
}

void ACC_Read(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t xl = I2C1_Read(LSM303_ACC_ADDR, 0x28 | 0x80); // auto-increment
    uint8_t xh = I2C1_Read(LSM303_ACC_ADDR, 0x29);
    uint8_t yl = I2C1_Read(LSM303_ACC_ADDR, 0x2A);
    uint8_t yh = I2C1_Read(LSM303_ACC_ADDR, 0x2B);
    uint8_t zl = I2C1_Read(LSM303_ACC_ADDR, 0x2C);
    uint8_t zh = I2C1_Read(LSM303_ACC_ADDR, 0x2D);

    *x = (int16_t)((xh << 8) | xl);
    *y = (int16_t)((yh << 8) | yl);
    *z = (int16_t)((zh << 8) | zl);
}
