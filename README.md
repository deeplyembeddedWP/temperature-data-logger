# Temperature-Data-Logger
**_Brief_**: 
An application that does the following
- Performs temperature measurements from multiple sensors.
- Computes the average temperature from all the measurements.
- Packetizes the temperature data and sends it to the host via a serial port.
- Monitors and indicates the current system status.

## Technical Specification for MVP
| Attribute | Description |
| --- | --- |
| **Power supply(V)** | 5V DC power | 
| **Battery(mAh)** | 6600 mAh rechargeable |
| **Battery life** | upto *x* hours/full charge |
| **No. of channels** | 4:support up to four sensors |
| **Temperature range(°C)** | -50°C to 150°C |
| **Accuracy(°C)** | +/-0.3°C |
| **Resolution(°C)** | 0.008°C |
| **Host Interface** | USB, baudrate:115200 bps, parity:none, data:8 bit, stop bits:1, flow control:none |
| **Data logging interval, seconds(s)** | DEFAULT:1s, MIN: 500ms MAX: 86400s(24 hours) |
| **Logging Protocol** | Custom protocol to provide seamless integration with external hosts |
| **LED status** | GREEN: OPERATING NORMALLY, RED: SENSOR FAULT, YELLOW: SENSOR ERRATIC READING |

**NOTE**: Increasing the logging frequency shall decrease battery life, default is set to once per second to maximize battery life.

## Functional Specification
![sensor-node-hlbd](https://github.com/deeplyembeddedWP/temperature-data-logger/assets/23131959/2e08672b-ddc1-4e7c-989f-e0380bc36687)

1. **_Temperature Data Logger_**: This constitutes the controller responsible for interacting and driving all the subsystems i.e. Battery Management, Channels, System Status Indicator, and the Host.
2. **_Channels_**: These physical ports connect the sensors for temperature measurements.
3. **_System Status Indicator_**: It consists of an RGB LED which the controller uses to indicate the state of the system.
4. **_DC Power Supply_**: An external USB port to charge the battery using a 5V DC power supply adaptor.
5. **_Battery Management_**: The controller can enable or disable charging. If enabled, safe charging of the battery is ensured when connected to an external 5V DC power supply.
6. **_Host_**: This is a physical port that allows connecting external hosts via USB to receive and log temperature measurements.

### ASSUMPTIONS
- Since there was no maximum number of sensors support specified, we shall assume supporting a maximum of 4 sensors since the TMP117 sensor can support only up to 4 unique channel/i2c addresses.
- To support more than 4 sensors, we could use an i2c multiplexer. However, this will increase the BOM cost and hence, for MVP we shall stick to the above specs.
- Since no precedence was mentioned for the occurrence of more than one fault, by default SENSOR FAULT shall always take precedence over other faults.
- Since power requirements were not specified, we assume this would be a battery-operated device and hence shall apply the best practices to maximize battery life while providing optimal performance.
- Since the logging interval wasn't specified, we shall assume a min of 500 ms to a max of 24 hrs. Since we are using a wired serial port to log data and are not limited by data costs, we shall log data in JSON format.
- This will make integration easier for external hosts considering there's massive support for processing JSON data.

## Software Architecture 
![software-stack](https://github.com/deeplyembeddedWP/temperature-data-logger/assets/23131959/f26e7f37-03c8-4d09-ac1a-86ac1b8c1574)
1. **_Hardware Abstraction Layer (HAL)_**: It exposes the APIs used to directly interact with the hardware while abstracting the underlying details of the controller architecture. These are usually provided as part of the vendor's SDK or framework.
2. **_Drivers_**: It uses the HAL APIs to expose the features of the controller to the user while abstracting the complex intricacies of the peripherals.
3. **_Libraries_**: It uses the driver APIs to interact with external devices and expose the external device functions/features to the application. 
4. **_Subsystems_**: It uses the libraries to build functional blocks. It abstracts all the complexities providing access to simplified interface/APIs to develop the business logic. In certain cases, these are also termed middleware.
5. **_Application_**: It uses the subsystems ' APIs to build the solution that meets the requirements.

### Project Structure
```bash
├── temperature logger
│   ├── ...
│   ├── hal
│   ├── ...
│   ├── usr_src
│   │   ├── drivers
│   │   	├── include
│   │   		├── I2C.h
│   │   		├── WDT.h
│   │   	├── src
│   │   		├── I2C.c
│   │   		├── WDT.c
│   │   ├── libraries
│   │   	├── RGB_LED.h
│   │   	├── RGB_LED.c
│   │   	├── TMP117.h
│   │   	├── TMP117.c
│   │   ├── subsystems
│   │   	├── packetizer
│   │   		├── JSON_Serial.h
│   │   		├── JSON_Serial.c
│   │   		├── Packet.h
│   │   	├── sys_status
│   │   		├── Sys_Status_Led.h
│   │   		├── Sys_Status_Led.c
│   │   	├── power_management
│   │   		├── Battery.h
│   │   		├── Battery.c
│   │   	├── sensors
│   │   		├── Sensors_Temperature.h
│   │   		├── Sensors_Temperature.c
│   │   ├── application
│   │   	├── Data_Logger.h
│   │   	├── Data_Logger.c
├── ...
├── main.c
├── ...
```
The above project structure correlates to the described software architecture with all the user-implemented source files in the **_usr_src_** directory.

## Data Logging Protocol
The data is logged to the serial terminal using a normal JSON format. The following structure has been used to make the packet as generic as possible so it can support logging different data types. Please see _Packet.h_ in the packetizers subsystem for more details.
Below shows an JSON example of logged packet.
```bash
{
  "Type": "sensor",
  "temperature(C)": {
    "value": "17.6748",
    "timestamp": "1719726801",
    "error": "0"
  }
}
```
**_NOTE_**: Timestamps aren't supported as of now, but can be extended to do so in the future with an RTC. As of now, errors field is unused and just being used as a place-holder for future use.

## Factors for Customazing the Application
Below describes some factors to consider when customizing the application for changing requirements.

The configuration register in the data logger has been configured as below by default. At present this is a hardcorded configuration and cannot be changed via any external stimuli. The below also describes the reasoning for this configuration in the application _Data_Logger.c_ file.
```bash
// Configure for the following:
// AVG[1:0] = 01 i.e. 8 Averaged conversions, total active conversion time = 8
// x 15.5ms = 124ms, MOD[1:0] = 11 i.e. One-shot conversion. sensors remains
// shutdown until data is read before starting the next conversion. This seems
// like the best possible setting to meet low power requirements since sensor
// will remain shutdown until the data has been read from temperature register.
// So if we perform logging every second, the sensor will remain shutdown for
// 80% of the logging interval. Reducing the logging interval will reduce the
// sensor's shutdown duration which will increase the power consumption due to
// more frequent conversions, minimizing battery life.
static TMP117_configuration_register_t _configuration = {
	.configuration_feilds.avg = 0x01,
	.configuration_feilds.mod = 0x03,
};
```
Below describes some things to consider.
```bash
  // Use a periodic timer to invoke Data_Logger_measurement_log()
  // and Data_Logger_indicate_sensor_status() at the nessesary intervals. Invoke
  // Data_Logger_indicate_sensor_status() atleast 2x faster than
  // Data_Logger_measurement_log() to ensure intermittent faults are caught. The
  // timer interval for Data_Logger_measurement_log() depends on the configured
  // number of conversion cycles and conversion mode. For e.g. a single
  // conversion cycle takes 15.5ms and if sensor is configured to take an average
  // of 8 measurements, then the conversion time shall be 15.5 x 8 = 124ms,
  // hence Data_Logger_measurement_log() must be invoked with a minimum interval
  // of 125ms hoping the data to be ready for measurement. see the TMP117 datasheet
  // for more details
``` 