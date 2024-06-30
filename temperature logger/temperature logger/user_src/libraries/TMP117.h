/*
 * TMP117.h
 *
 * Created: 29/06/2024 1:42:42 pm
 * Author: Vinay Divakar
 * Brief: minimal lib to interact with the sensor
 */
#include "I2C.h"
#include "err_codes.h"
#include "stdio_start.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef TMP117_H_
#define TMP117_H_

#define TMP117_ADDRESS_0 0x48 // ADD0 connected to GND
#define TMP117_ADDRESS_1 0x49 // ADD0 connected to Vcc
#define TMP117_ADDRESS_2 0x4A // ADD0 connected to SDA
#define TMP117_ADDRESS_3 0x4B // ADD0 connected to SCL

// device take 1.5 ms to power up, on a safer side, use 5 ms
#define TMP117_POWER_ON_TIME_MS 5

int TMP117_configure(int16_t slave_addr, uint16_t config_value);
bool TMP117_device_id_status_get(int16_t slave_addr);
int TMP117_data_ready_status_get(int16_t slave_addr);
float TMP117_temperature_celcius_get(int16_t slave_addr);

#endif /* TMP117_H_ */