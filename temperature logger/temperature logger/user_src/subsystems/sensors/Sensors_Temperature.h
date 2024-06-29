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

#endif /* SENSORS_TEMPERATURE_H_ */