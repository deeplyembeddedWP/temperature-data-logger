/*
 * Temperature_Sensor.c
 *
 * Created: 29/06/2024 6:15:10 pm
 * Author: Vinay Divakar
 * Brief: subsystem to interact with an array of temperature sensors
 * Dependencies: TMP117, delay drivers
 */

#include "Sensors_Temperature.h"
#include <math.h>

// max number of channels supported
#define SENSORS_TEMPERATURE_CHANNELS_NUM_MAX 4
#define SENSORS_TEMPERATURE_STANDARD_DEVIATION_MAX 1.0f

/*
populate for the intended configuration (usually done by the application)
*/
#define SENSORS_TEMPERATURE_DEFAULT_CONFIGURATION 0x0220
static TMP117_configuration_register_t _configuration = {
    .value = SENSORS_TEMPERATURE_DEFAULT_CONFIGURATION};

/*
structure to hold the state of the sensor
*/
struct sensor_temperature_t {
  int16_t address;   // address of the sensor
  bool initialized;  // indicates if sensor was found during scan
  float temperature; // holds the measurement data
};

/*
context holding the sensor list to manage interactions with all the sensors
*/
static struct sensors_temperature_context_t {
  struct sensor_temperature_t
      sensors[SENSORS_TEMPERATURE_CHANNELS_NUM_MAX]; // holds data unique to
                                                     // each sensor
  enum sensors_status_t status; // indicates the overall health of the sensors
  float temerature_average;     // holds average temperature of all the sensors
} _this = {
    .sensors[0].address = TMP117_ADDRESS_0,
    .sensors[1].address = TMP117_ADDRESS_1,
    .sensors[2].address = TMP117_ADDRESS_2,
    .sensors[3].address = TMP117_ADDRESS_3,
};

/**
 * @brief scans the bus and initializes the reachable devices
 */
static void _ports_scan(void) {
  for (size_t i = 0; i < SENSORS_TEMPERATURE_CHANNELS_NUM_MAX; i++) {
    _this.sensors[i].initialized =
        TMP117_device_id_status_get(_this.sensors[i].address);
  }
}

/**
 * @brief configures all the sensors
 *
 * @return 0 success, <0 if one or more sensors failed to configure
 */
static int _configure(void) {
  int err = 0;
  for (size_t i = 0; i < SENSORS_TEMPERATURE_CHANNELS_NUM_MAX; i++) {
    if (!_this.sensors[i].initialized) {
      continue;
    }
    // try configuring the sensor
    err = TMP117_configure(_this.sensors[i].address, _configuration.value);
    if (err) { // check for errors
      _this.status = SENSORS_TEMPERATURE_CONFIG_ERROR;
      // somethings not right, sensor could be unreliable, set it to false
      // so we don't attempt reading from it. Will a retrying make it any
      // better?
      _this.sensors[i].initialized = false;
    }
  }
  return _this.status;
}

/**
 * @brief calculates standard deviation using the current measurements
 *
 * @return standard deviation from the mean
 */
static float _temperature_standard_deviation_get(void) {
  float sensors[SENSORS_TEMPERATURE_CHANNELS_NUM_MAX] = {};
  float value = 0.0;
  for (size_t i = 0; i < SENSORS_TEMPERATURE_CHANNELS_NUM_MAX; i++) {
    // calculate the difference between the sensors measurements and the mean
    sensors[i] = _this.sensors[i].temperature - _this.temerature_average;
    // square the differences to make all positives, so they don't cancel out
    // each other to zero.
    sensors[i] = (sensors[i] * sensors[i]);
    // sum of square of all differences
    value += sensors[i];
  }

  // now calculate the variance
  value = (value / SENSORS_TEMPERATURE_CHANNELS_NUM_MAX);

  return sqrt(value); // return the standard deviation
}

/**
 * @brief scan ports and initialize the reachable sensors
 */
void Sensors_Temperature_initialize(void) {
  delay_ms(TMP117_POWER_ON_TIME_MS);
  _ports_scan();
  _configure();
}

/**
 * @brief gets the most recent status of the sensors
 *
 * @return status
 */
int Sensors_Temperature_subsys_status_get(void) { return _this.status; }

/**
 * @brief updates the value to be applied for configuration.
 *
 * WARNING: for the new value to take effect, a system reset must be
 * invoked. Run-time configuration is not supported as of now.
 */
void Sensors_Temperature_configuration_value_update(uint16_t value) {
  _configuration.value = value;
}

/**
 * @brief iterates the sensor list, grabs measurements from each sensor
 * if available, computes and returns the average of all successful readings.
 * retrieves average temperature reading from all the sensors.
 *
 * @return average temperature reading, 0.0 if none was a success
 */
float Sensors_Temperature_reading_get(void) {
  int status = 0;
  float value = 0.0;

  // status shall be overridden if any errors occur only if there existed no
  // config errors
  _this.status = (_this.status == SENSORS_TEMPERATURE_CONFIG_ERROR)
                     ? _this.status
                     : SENSORS_TEMPERATURE_OK;

  for (size_t i = 0; i < SENSORS_TEMPERATURE_CHANNELS_NUM_MAX; i++) {
    if (!_this.sensors[i].initialized) {
      continue;
    }
    _this.sensors[i].temperature = 0.0; // reset reading

    status = TMP117_data_ready_status_get(_this.sensors[i].address);
    if (!status) { // data unavailable
      continue;
    } else if (status == true) { // data is available
      value = TMP117_temperature_celcius_get(_this.sensors[i].address);
    }

    // check for errors
    if (status == ERR_INVALID_DATA || (int)value == ERR_INVALID_DATA) {
      // somethings not right, either conversion was incomplete or measurement
      // failed for this sensor, set the fault code to indicate this error
      _this.status = SENSORS_TEMPERATURE_FAULTY;
    } else { // no errors
      _this.sensors[i].temperature = value;
    }
  }

  // compute and return the average
  for (size_t i = 0; i < SENSORS_TEMPERATURE_CHANNELS_NUM_MAX; i++) {
    value += _this.sensors[i].temperature;
  }

  _this.temerature_average = value / SENSORS_TEMPERATURE_CHANNELS_NUM_MAX;

  if (_this.status ==
      SENSORS_TEMPERATURE_OK) { // if no faults, check for unusual readings
    float cv =
        (_temperature_standard_deviation_get() / _this.temerature_average);
    _this.status = cv < SENSORS_TEMPERATURE_STANDARD_DEVIATION_MAX
                       ? _this.status
                       : SENSORS_TEMPERATURE_ERRATIC;
  }

  return _this.temerature_average;
}
