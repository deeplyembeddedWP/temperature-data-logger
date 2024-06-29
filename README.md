# Temperature-Data-Logger
Brief: An application that does the following
- performs temperature measurements from multiple sensors.
- computes the average temperature from all the measurements.
- packetizes the temperature data and sends it to the host via a serial port.

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
| **Host Interface** | USB, baudrate:115200bps, parity:none, data:8 bit, stop bits:1, flow control:none |
| **Data logging interval, seconds(s)** | DEFAULT:1s, MIN:100s MAX:86400s(24 hours) |
| **Logging Protocol** | Custom protocol to provide seamless integration with external hosts |
| **LED status** | GREEN: OPERATING NORMALLY, RED: SENSOR FAULT, YELLOW: SENSOR ERRATIC DATA |

**NOTE**: Increasing the logging frequency shall decrease battery life, default is set to once per second to maximize battery life.

## Functional Specification
**_Temperature Data Logger_**: This constitutes the controller responsible for interacting and driving all the subsystems i.e. Battery Management, Channels, System Status Indicator, and the Host.
**_Channels_**: These physical ports connect the sensors for temperature measurements. 
**_System Status Indicator_**: It consists of an RGB LED which the controller uses to indicate the state of the system. 
**_DC Power Supply_**: An external USB port to charge the battery using a 5V DC power supply adaptor.
**_Battery Management_**: The controller can enable or disable charging. If enabled, safe charging of the battery is ensured when connected to an external 5V DC power supply. 
**_Host_**: This is a physical port that allows connecting external hosts via USB to receive and log temperature measurements.

### ASSUMPTIONS
1. Since there was no maximum number of sensors support specified, we shall assume supporting a maximum of 4 sensors since the TMP117 sensor can support only up to 4 unique channel/i2c addresses. 
2. To support more than 4 sensors, we could use an i2c multiplexer. However, this will increase the BOM cost and hence, for MVP we shall stick to the above specs.
3. Since no precedence was mentioned for the occurrence of more than one fault, by default SENSOR FAULT shall always take precedence over other faults. 
4. Since power requirements were not specified, we assume this would be a battery-operated device and hence shall apply the best practices to maximize battery life while providing optimal performance.   
5. Since the logging interval wasn't specified, we shall assume a min of 100 ms to a max of 24 hrs. Since we are using a wired serial port to log data and are not limited by data costs, we shall log data in JSON format. This will make integration easier for external hosts considering there's massive support for processing JSON data. 
