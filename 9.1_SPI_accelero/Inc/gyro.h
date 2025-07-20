#ifndef GYRO_H
#define GYRO_H

#include <stdint.h>

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} GyroData;

void GYRO_Init(void);
GyroData GYRO_ReadXYZ(void);

#endif // GYRO_H
