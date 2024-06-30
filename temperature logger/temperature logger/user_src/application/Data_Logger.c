/*
 * Data_Logger.c
 *
 * Created: 30/06/2024 10:15:13 am
 *  Author: Vinay Divakar
 */
#include "Sensors_Temperature.h"
#include "Sys_Status_Led.h"

// time interval between subsequent conversions i.e. minimum time to wait before
// querying data to sensors
#define DATA_LOGGER_MEASUREMENT_TIME_TOTAL_MS                                  \
  (8 * SENSORS_TEMPERATURE_CONVERSION_TIME_ONE_CYCLE_MS)
