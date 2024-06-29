/*
 * I2C.h
 *
 * Created: 29/06/2024 12:32:37 pm
 * Author: Vinay Divakar
 * @brief Wrappper module to access the I2C driver API's
 */

#ifndef I2C_H_
#define I2C_H_

int I2C_begin(void);
void I2C_slave_address_select(int16_t addr);
int I2C_master_write(uint8_t reg, uint8_t* buffer, uint8_t buffer_size);
int I2C_master_read(uint8_t reg, uint8_t* buffer, uint8_t buffer_size);

#endif /* I2C_H_ */