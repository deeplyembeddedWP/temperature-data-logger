/*
 * Data_Logger.h
 *
 * Created: 30/06/2024 10:14:51 am
 * Author: Vinay Divakar
 * Brief: Module to manage data logging and system status.
 */ 


#ifndef DATA_LOGGER_H_
#define DATA_LOGGER_H_

#include "Sensors_Temperature.h"
#include "Sys_Status_Led.h"
#include "Json_Serial.h"

void Data_Logger_initalize(void);
void Data_Logger_measurement_get(void);
void Data_Logger_indicate_sensor_status(void);

#endif /* DATA_LOGGER_H_ */