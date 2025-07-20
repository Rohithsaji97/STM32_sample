#ifndef GYRO_H_
#define GYRO_H_

#include <stdint.h>

void gyro_init(void);
void gyro_read_xyz(int16_t *x, int16_t *y, int16_t *z);
void gyro_read_address(uint8_t address, uint8_t *rxdata);

#endif /* GYRO_H_ */
