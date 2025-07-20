//#include "gyro.h"
//#include "spi.h"
//
//#define CTRL_REG1      0x20
//#define OUT_X_L        0x28
//
//#define READ_FLAG      0x80
//#define MULTI_BYTE     0x40
//
//void gyro_init(void) {
//    uint8_t config_data[2];
//
//    cs_enable();
//
//    // CTRL_REG1: Enable all axes, normal mode, 95 Hz output rate
//    config_data[0] = CTRL_REG1 | MULTI_BYTE;
//    config_data[1] = 0x0F;  // Normal mode, X/Y/Z enabled, 95Hz ODR
//
//    spi1_transmit(config_data, 2);
//
//    cs_disable();
//}
//
//void gyro_read_address(uint8_t address, uint8_t rxdata){
//
//	address |= READ_FLAG | MULTI_BYTE;
//
//	cs_enable();
//
//	spi1_transmit(&address, 1);
//
//	spi1_recieve(rxdata, 6);
//	cs_disable();
//}
//
//void gyro_read_xyz(int16_t *x, int16_t *y, int16_t *z) {
//    uint8_t address = READ_FLAG | MULTI_BYTE | OUT_X_L;
//    uint8_t buffer[6];
//
//    cs_enable();
//
//    spi1_transmit(&address, 1);    // Send read starting address
//    spi1_recieve(buffer, 6);       // Read 6 bytes (X, Y, Z low/high)
//
//    cs_disable();
//
//    *x = (int16_t)(buffer[1] << 8 | buffer[0]);
//    *y = (int16_t)(buffer[3] << 8 | buffer[2]);
//    *z = (int16_t)(buffer[5] << 8 | buffer[4]);
//}


#include "gyro.h"
#include "spi.h"

#define CTRL_REG1      0x20
#define OUT_X_L        0x28

#define READ_FLAG      0x80
#define MULTI_BYTE     0x40

void gyro_init(void) {
	cs_disable();
    uint8_t config_data[2];

    cs_enable();

    // CTRL_REG1: Enable all axes, normal mode, 95 Hz output rate
    config_data[0] = CTRL_REG1 | MULTI_BYTE;
    config_data[1] = 0x0F;  // Normal mode, X/Y/Z enabled, 95Hz ODR

    spi1_transmit(config_data, 2);

    cs_disable();
}

void gyro_read_address(uint8_t address, uint8_t *rxdata){

    address |= READ_FLAG | MULTI_BYTE;

    cs_enable();

    spi1_transmit(&address, 1);

    spi1_recieve(rxdata, 6);
    cs_disable();
}

void gyro_read_xyz(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t address = READ_FLAG | MULTI_BYTE | OUT_X_L;
    uint8_t buffer[6];

    cs_enable();

    spi1_transmit(&address, 1);    // Send read starting address
    spi1_recieve(buffer, 6);       // Read 6 bytes (X, Y, Z low/high)

    cs_disable();

    *x = (int16_t)(buffer[1] << 8 | buffer[0]);
    *y = (int16_t)(buffer[3] << 8 | buffer[2]);
    *z = (int16_t)(buffer[5] << 8 | buffer[4]);
}
