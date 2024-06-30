/*
 * main.c
 *
 * Created: 30/06/2024 10:15:13 am
 * Author: Vinay Divakar
 *
 * TODO: implement a timer to invoke Data_Logger_measurement_get()
 * and Data_Logger_indicate_sensor_status() at the nessesary intervals.
 */

#include <atmel_start.h>
#include "user_src/application/Data_Logger.h"

int main(void){
	atmel_start_init(); // initialize the clock
	I2C_initialize(); // initialize the I2C driver
	Data_Logger_initalize(); //initialize the data logging module
	
	while (1) {
	}
}
