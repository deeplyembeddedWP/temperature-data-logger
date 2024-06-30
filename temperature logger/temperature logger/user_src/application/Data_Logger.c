/*
 * Data_Logger.c
 *
 * Created: 30/06/2024 10:15:13 am
 * Author: Vinay Divakar
 * Brief: Module to manage data logging and system status.
 * Dependencies: sensors, sys_status, subsystems, packetizer
 */
#include "Data_Logger.h"

// time interval between subsequent conversions i.e. minimum time to wait before
// querying data to sensors
#define DATA_LOGGER_MEASUREMENT_TIME_TOTAL_MS                                  \
  (8 * SENSORS_TEMPERATURE_CONVERSION_TIME_ONE_CYCLE_MS)

/*
populate for the intended configuration & then use
Sensors_Temperature_configuration_value_update() to apply it.
For this to take effect, it should be done before invoking
Sensors_Temperature_initialize()
*/
static TMP117_configuration_register_t _configuration = {};

/**
 * @brief drives the leds based on the status input
 *
 * @param[in] status system status input
 */
static void _sensor_status_led_drive(enum sensors_status_t status) {
  switch (status) {
  case SENSORS_TEMPERATURE_OK:
    Sys_Status_Led_indicate(RGB_LED_GREEN);
    break;

  case SENSORS_TEMPERATURE_CONFIG_ERROR:
  case SENSORS_TEMPERATURE_FAULTY:
    Sys_Status_Led_indicate(RGB_LED_RED);
    break;

  case SENSORS_TEMPERATURE_ERRATIC:
    Sys_Status_Led_indicate(RGB_LED_YELLOW);
    break;

  default:
    printf("%s: should never arrive here, seems like a bug? status: %d\r\n",
           __FUNCTION__, status);
    break;
  };
};

/**
 * @brief initializes the data logger
 */
void Data_Logger_initalize(void) {
  _sensor_status_led_drive(RGB_LED_GREEN);
  Sensors_Temperature_configuration_value_update(_configuration.value);
  Sensors_Temperature_initialize();
  // give some time so the first conversion shall be completed before kicking
  // off the subsequent measurement reads.
  delay_ms(DATA_LOGGER_MEASUREMENT_TIME_TOTAL_MS);
}

/**
 * @brief indicates the system status
 */
void Data_Logger_indicate_sensor_status(void) {
  _sensor_status_led_drive(Sensors_Temperature_subsys_status_get());
}

/**
 * @brief indicates the system status
 */
void Data_Logger_measurement_log(void) {
  struct packet_t packet = {
      .type = "measurement",
      .param.name = "temperature",
      .param.value.value_float = Sensors_Temperature_reading_get(),
  };

  // log the packet to the serial terminal/port
  Json_Serial_measurement_log(&packet);
}
