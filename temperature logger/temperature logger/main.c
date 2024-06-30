/*
 * main.c
 *
 * Created: 30/06/2024 10:15:13 am
 * Author: Vinay Divakar
 */

#include "user_src/application/Data_Logger.h"
#include "user_src/drivers/include/I2C.h"
#include "user_src/drivers/include/WDT.h"
#include <atmel_start.h>

int main(void) {
  atmel_start_init();                   // initialize the system clock
  WDT_init();                           // initialize the watchdog timer
  I2C_initialize();                     // initialize the I2C driver
  Data_Logger_initalize();              // initialize the data logging module
  Data_Logger_measurement_log();        // log a temperature data measurement
  Data_Logger_indicate_sensor_status(); // indicate if any faults occurred

  // TODO: implement a periodic timer to invoke Data_Logger_measurement_log()
  // and Data_Logger_indicate_sensor_status() at the nessesary intervals. Invoke
  // Data_Logger_indicate_sensor_status() atleast 2x faster than
  // Data_Logger_measurement_log() to ensure intermittent faults are caught. The
  // timer interval for Data_Logger_measurement_log() depends on the configured
  // number of conversion cycles and conversion mode. For e.g. a single
  // conversion cycle take 15.5ms and if sensor is configured to take an average
  // of 8 measurements, then the conversion time shall be 15.5 x 8 = 124ms,
  // hence Data_Logger_measurement_log() must be invoked with a minimum interval
  // of 125ms hoping the data to be ready for measurement. see the TMP117 datasheet 
  //for more details

  while (1) {
    WDT_feed(); // feed to prevent it from firing
  }
}
