/*
 * Sensors_Temperature.h
 *
 * Created: 29/06/2024 6:12:57 pm
 * Author: Vinay Divakar
 * Brief: subsystem to interact with an array of temperature sensors
 */ 


#ifndef SENSORS_TEMPERATURE_H_
#define SENSORS_TEMPERATURE_H_

#include "TMP117.h"
#include "hal_delay.h"
#include "TMP117_register.h"

// single cycle takes 15.5 ms, on a safer side, use 20 ms
#define SENSORS_TEMPERATURE_CONVERSION_TIME_ONE_CYCLE_MS 20

/*
sensor operating states
*/
enum sensors_status_t {
	SENSORS_TEMPERATURE_OK = 0,
	SENSORS_TEMPERATURE_CONFIG_ERROR = -1,
	SENSORS_TEMPERATURE_FAULTY = -1,
	SENSORS_TEMPERATURE_ERRATIC = -2,
};

void Sensors_Temperature_initialize(void);
float Sensors_Temperature_reading_get(void);
int Sensors_Temperature_subsys_status_get(void);
void Sensors_Temperature_configuration_value_update(uint16_t value);

#endif /* SENSORS_TEMPERATURE_H_ */