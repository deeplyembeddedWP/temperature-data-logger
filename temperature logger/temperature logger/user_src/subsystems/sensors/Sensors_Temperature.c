/*
 * Temperature_Sensor.c
 *
 * Created: 29/06/2024 6:15:10 pm
 *  Author: Vinay Divakar
 */
#include "TMP117.h"
#include "hal_delay.h"

#define SENSORS_TEMPERATURE_SUPPORTED_MAX 4

/*
sensor operating states
*/
enum sensors_status_t {
  SENSORS_TEMPERATURE_OK = 0,
  SENSORS_TEMPERATURE_FAULTY = -1,
  SENSORS_TEMPERATURE_ERRATIC = -2,
};

/*
populate the structure for the intended configuration value
*/
static TMP117_configuration_register_t configuration = {};

/*
structure to hold the state of the sensor
*/
struct sensor_temperature_t {
  int16_t address;   // address of the sensor
  bool initialized;  // indicates if sensor was found during scan
  float temperature; // holds the measurement data
};

/*
context to manage interactions with all the sensors
*/
static struct sensors_temperature_context_t {
  struct sensor_temperature_t
      sensors[SENSORS_TEMPERATURE_SUPPORTED_MAX]; // holds data unique to each
                                                  // sensor
  enum sensors_status_t status; // indicates the overall health of the sensors
} _this = {
    .sensors[0].address = TMP117_ADDRESS_0,
    .sensors[1].address = TMP117_ADDRESS_1,
    .sensors[2].address = TMP117_ADDRESS_2,
    .sensors[3].address = TMP117_ADDRESS_3,
};

/**
 * @brief scans the bus and initializes the reachable devices
 */
void Sensors_Temperature_ports_initialize(void) {
  delay_ms(TMP117_POWER_ON_TIME_MS);
  for (size_t i = 0; i < sizeof(_this.sensors) / sizeof(_this.sensors[0]);
       i++) {
    _this.sensors[i].initialized =
        TMP117_device_id_status_get(_this.sensors[i].address);
  }
}

/**
 * @brief configures all the sensors
 *
 * @return 0 success, <0 if one or more sensors failed to configure
 */
int Sensors_Temperature_configure(void) {
  int err = 0;
  for (size_t i = 0; i < sizeof(_this.sensors) / sizeof(_this.sensors[0]);
       i++) {
    if (!_this.sensors[i].initialized)
      continue;

    err = TMP117_configure(_this.sensors[i].address, configuration.value);
    if (err) { // check for errors
      _this.status = SENSORS_TEMPERATURE_FAULTY;
      // somethings not right, sensor could be unreliable, set it to false so we
      // attempt reading from it
      _this.sensors[i].initialized = false;
    }
  }
  return _this.status;
}
