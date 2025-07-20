#include "gyro.h"
#include "spi.h"

// L3GD20 registers
#define WHO_AM_I_REG    0x0F
#define CTRL_REG1       0x20
#define OUT_X_L         0x28

#define WHO_AM_I_ID     0xD4

static uint8_t GYRO_ReadReg(uint8_t reg) {
    uint8_t val;
    SPI1_CS_Enable();
    SPI1_TransmitReceive(0x80 | reg);
    val = SPI1_TransmitReceive(0x00);
    SPI1_CS_Disable();
    return val;
}

static void GYRO_WriteReg(uint8_t reg, uint8_t val) {
    SPI1_CS_Enable();
    SPI1_TransmitReceive(reg & 0x7F);
    SPI1_TransmitReceive(val);
    SPI1_CS_Disable();
}

void GYRO_Init(void) {
    uint8_t id = GYRO_ReadReg(WHO_AM_I_REG);
    if (id != WHO_AM_I_ID) {
        while (1);  // halt if device not found
    }

    // Enable X, Y, Z axes, 200 Hz output data rate
    GYRO_WriteReg(CTRL_REG1, 0x0F | (2 << 6));  // 0x8F
}

GyroData GYRO_ReadXYZ(void) {
    GyroData data;
    uint8_t buf[6];

    SPI1_CS_Enable();
    SPI1_TransmitReceive(0xC0 | OUT_X_L);  // Auto-increment + Read
    for (int i = 0; i < 6; ++i) {
        buf[i] = SPI1_TransmitReceive(0x00);
    }
    SPI1_CS_Disable();

    data.x = (int16_t)(buf[1] << 8 | buf[0]);
    data.y = (int16_t)(buf[3] << 8 | buf[2]);
    data.z = (int16_t)(buf[5] << 8 | buf[4]);

    return data;
}
