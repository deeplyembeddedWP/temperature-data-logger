/*
 * TMP117.c
 *
 * Created: 29/06/2024 1:43:06 pm
 *  Author: Vinay Divakar
 */
#include "I2C.h"
#include "TMP117.h"

/**
 * @brief configures the sensors functions

 * @param[in] slave_addr slave address to read from
 * @param[in] config_value value to be written to the configuration register
 * @return 0 success, <0 error
 */
int TMP117_configure(int16_t slave_addr, uint16_t config_value) {
  uint8_t commmand[2] = {((config_value & 0xFF00) >> 8),
                         (config_value & 0x00FF)};

  return I2C_master_write(slave_addr, TMP117_CONFIG_REGISTER_ADDRESS, commmand,
                          sizeof(commmand) / sizeof(commmand[0]));
}