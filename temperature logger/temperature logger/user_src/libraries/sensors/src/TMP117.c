/*
 * TMP117.c
 *
 * Created: 29/06/2024 1:43:06 pm
 * Author: Vinay Divakar
 * Brief: minimal lib to interact with the sensor
 * Dependencies: I2C, UART stdio drivers
 */
#include "TMP117.h"

/*
Pointer Registers
*/
#define TMP117_ID_REGISTER_ADDRESS 0x0F
#define TMP117_CONFIG_REGISTER_ADDRESS 0x01
#define TMP117_TEMPERATURE_REGISTER_ADDRESS 0x00

/*
Expected device ID and supported resolution
*/
#define TMP117_DEVICE_ID_VALUE_EXPECTED 0x0117
#define TMP117_SUPPORTED_RESOLUTION 0.0078125f

/*
Data ready bit in the configuration register
*/
#define TMP117_DATA_READY_BIT_POS 13
#define TMP117_DATA_READY_BIT (1U << TMP117_DATA_READY_BIT_POS)

/**
 * @brief writes a value to a register
 *
 * @param[in] slave_addr slave address to read from
 * @param[in] register_addr register address to be written to
 * @param[in] value value to be written to register_addr
 * @return 0 success, <0 error
 */
static int _register_write(int16_t slave_addr, uint8_t register_addr,
                           uint16_t value) {
  uint8_t commmand[2] = {((value & 0xFF00) >> 8), (value & 0x00FF)};

  int err = I2C_master_write(slave_addr, register_addr, commmand,
                             sizeof(commmand) / sizeof(commmand[0]));
  if (err) { // check for errors
    printf("%s: sl_addr:0x%02X r_addr:0x%02X val:0x%04X err:%d\r\n",
           __FUNCTION__, slave_addr, register_addr, value, err);
  }

  return err;
}

/**
 * @brief reads data from a register
 *
 * @param[in] slave_addr slave address to read from
 * @param[in] register_addr address to read from
 * @return data on success, UINT16_MAX on error
 */
static uint16_t _register_read(int16_t slave_addr, uint8_t register_addr) {
  uint8_t result[2] = {};

  int err = I2C_master_read(slave_addr, register_addr, result,
                            sizeof(result) / sizeof(result[0]));
  if (err) { // check for errors
    printf("%s: sl_addr:0x%02X r_addr:0x%02X err:%d\r\n", __FUNCTION__,
           slave_addr, register_addr, err);
    return UINT16_MAX;
  }

  // grab the data starting from ms-byte
  return ((result[0] << 8) | result[1]);
}

/**
 * @brief configures the sensors functions
 *
 * @param[in] slave_addr slave address to read from
 * @param[in] config_value value to be written to the configuration register
 * @return 0 success, <0 error
 */
int TMP117_configure(int16_t slave_addr, uint16_t config_value) {
  return _register_write(slave_addr, TMP117_CONFIG_REGISTER_ADDRESS,
                         config_value);
}

/**
 * @brief retrieves device id from the sensor
 *
 * @param[in] slave_addr slave address to read from
 * @return true on success/valid, false on error/invalid
 */
bool TMP117_device_id_status_get(int16_t slave_addr) {
  uint16_t id = _register_read(slave_addr, TMP117_ID_REGISTER_ADDRESS);
  if (id == UINT16_MAX || id != TMP117_DEVICE_ID_VALUE_EXPECTED) { // verify id
    return false;
  }

  return true;
}

/**
 * @brief retrieves data ready status
 *
 * @param[in] slave_addr slave address to read from
 * @return 1 on ready, 0 on not ready, ERR_INVALID_DATA on error
 */
int TMP117_data_ready_status_get(int16_t slave_addr) {
  uint16_t data_ready =
      _register_read(slave_addr, TMP117_CONFIG_REGISTER_ADDRESS);
  if (data_ready == UINT16_MAX) {
    return ERR_INVALID_DATA;
  }

  return (data_ready & TMP117_DATA_READY_BIT);
}

/**
 * @brief retrieves temperature in degrees celceus
 *
 * @param[in] slave_addr slave address to read from
 * @return data on success, ERR_INVALID_DATA on error
 */
float TMP117_temperature_celcius_get(int16_t slave_addr) {
  uint16_t temperature =
      _register_read(slave_addr, TMP117_TEMPERATURE_REGISTER_ADDRESS);
  if (temperature == UINT16_MAX) {
    return ERR_INVALID_DATA;
  }

  // multiply by resolution to get the temperature in degree celceus
  return ((int16_t)temperature * TMP117_SUPPORTED_RESOLUTION);
}