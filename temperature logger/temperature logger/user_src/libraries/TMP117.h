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
// single cycle takes 15.5 ms, on a safer side, use 20 ms
#define TMP117_CONVERSION_TIME_ONE_CYCLE_MS 20
#define TMP117_CONVERSION_TIME_EIGHT_CYCLES_MS                                 \
  (8 * TMP117_CONVERSION_TIME_ONE_CYCLE_MS)

// Configuration register found on page 25 Figure 26 and Table 6
typedef union {
  struct {
    uint8_t unused : 1;      // Empty bit in register
    uint8_t soft_reset : 1;  // Software reset bit
    uint8_t dr_alert : 1;    // ALERT pin select bit
    uint8_t pol : 1;         // ALERT pin polarity bit
    uint8_t t_na : 1;        // Therm/alert mode select
    uint8_t avg : 2;         // Conversion averaging modes
    uint8_t conv : 3;        // Conversion cycle bit
    uint8_t mod : 2;         // Set conversion mode
    uint8_t eeprom_busy : 1; // EEPROM busy flag
    uint8_t data_ready : 1;  // Data ready flag
    uint8_t low_alert : 1;   // Low Alert flag
    uint8_t high_alert : 1;  // High Alert flag
  } configuration_feilds;
  uint16_t value;
} TMP117_configuration_register_t;

// Device ID Register used for checking if the device ID is the same as declared
typedef union {
  struct {
    uint16_t did : 12; // Indicates the device ID
    uint8_t rev : 4;   // Indicates the revision number
  } device_id_fields;
  uint16_t device_id_register;
} TMP117_device_id_register_t;

int TMP117_configure(int16_t slave_addr, uint16_t config_value);
bool TMP117_device_id_status_get(int16_t slave_addr);
int TMP117_data_ready_status_get(int16_t slave_addr);
float TMP117_temperature_celcius_get(int16_t slave_addr);

#endif /* TMP117_H_ */