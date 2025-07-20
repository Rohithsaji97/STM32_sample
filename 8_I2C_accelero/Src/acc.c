#include "stm32f3xx.h"
#include "i2c.h"
#include "acc.h"

#define LSM303_ACC_ADDR      0x19//  // 7-bit address for accelerometer
#define CTRL_REG1_A          0x20
#define OUT_X_L_A            0x28  // Auto-increment will read all axis

void acc_init(void) {

    char ctrl_reg1 = 0x47; // 0b01011	111 = 100Hz, all axes enabled
    i2c_write(LSM303_ACC_ADDR, CTRL_REG1_A, ctrl_reg1);
}

void acc_read(int16_t *x, int16_t *y, int16_t *z) {

    uint8_t xl = i2c_read(LSM303_ACC_ADDR, 0x28 | 0x80); // auto-increment
    uint8_t xh = i2c_read(LSM303_ACC_ADDR, 0x29);
    uint8_t yl = i2c_read(LSM303_ACC_ADDR, 0x2A);
    uint8_t yh = i2c_read(LSM303_ACC_ADDR, 0x2B);
    uint8_t zl = i2c_read(LSM303_ACC_ADDR, 0x2C);
    uint8_t zh = i2c_read(LSM303_ACC_ADDR, 0x2D);

    // Convert to 16-bit signed integers
    *x = (int16_t)((xh << 8) | xl);
    *y = (int16_t)((yh << 8) | yl);
    *z = (int16_t)((zh << 8) | zl);
}
