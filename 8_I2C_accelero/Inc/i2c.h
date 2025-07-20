	#ifndef I2C_H_
	#define I2C_H_

	void i2c_init(void);
	void i2c_write(char saddr, char maddr, char data);
	void i2c_burstWrite(char saddr, char maddr, int n, char *data);
	void i2c_burstRead(char saddr, char maddr, int n, char *data);
	uint8_t i2c_read(char saddr, char maddr);

	#endif /* I2C_H_ */
