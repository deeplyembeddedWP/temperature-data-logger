/*
 * I2C.c
 *
 * Created: 29/06/2024 12:33:07 pm
 * Author: Vinay Divakar
 * @brief Wrappper module to access the I2C driver API's
 */

#include "I2C.h"
#include "driver_init.h"
#include <utils_assert.h>

/**
 * @brief selects the slave for the next transfer

 * @param[in] addr address of the slave for communication
 * Note: If communicating with multiple devices, update the address before any
 * transfers using this API, to ensure the right slave receives the instruction.
 */
static void _slave_address_select(int16_t addr) {
  i2c_m_sync_set_slaveaddr(&I2C_Sercom_3, addr, I2C_M_SEVEN);
}

/**
 * @brief enables the i2c hardware on sercom-3
 *
 * @return 0 success, <0 error
 */
int I2C_begin(void) {
  int err = i2c_m_sync_enable(&I2C_Sercom_3);
  ASSERT(!err);

  return err;
}

/**
 * @brief performs a write transaction

 * @param[in] addr slave address to write to
 * @param[in] reg register address to be written to
 * @param[in] buffer points to buffer containing the data to be written
 * @param[in] buffer_size size of data to be written (in bytes)
 * @return 0 success, <0 error
 */
int I2C_master_write(int16_t addr, uint8_t reg, uint8_t *buffer,
                     uint8_t buffer_size) {
  _slave_address_select(addr);
  int err = i2c_m_sync_cmd_write(&I2C_Sercom_3, reg, buffer, buffer_size);
  ASSERT(!err);

  return err;
}

/**
 * @brief performs a read transaction

 * @param[in] addr slave address to read from
 * @param[in] reg register address to start reading from
 * @param[out] buffer points to buffer to populate with read data
 * @param[in] buffer_size size of data to be read (in bytes)
 * @return 0 success, <0 error
 */
int I2C_master_read(int16_t addr, uint8_t reg, uint8_t *buffer,
                    uint8_t buffer_size) {
  _slave_address_select(addr);
  int err = i2c_m_sync_cmd_read(&I2C_Sercom_3, reg, buffer, buffer_size);
  ASSERT(!err);

  return err;
}