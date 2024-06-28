# Temperature-Data-Logger
Brief: An application that does the following
- performs temperature measurements from multiple sensors.
- computes the average temperature from all the measurements.
- packetizes the temperature data and sends it to the host via a serial port.

## Technical Specification for MVP
| --- | --- |
| Power supply(V) | 5V DC power | 
| Battery(mAh) | 6600 mAh rechargeable |
| Battery life | upto *x* hours/full charge |
| No. of channels | 4:support up to four sensors |
| Temperature range(°C) | -50°C to 150°C |
| Accuracy(°C) | +/-0.3°C |
| Resolution(°C) | 0.008°C |
| Host Interface | USB |
| Data logging interval, seconds(s) | DEFAULT:1s, MIN:100s MAX:86400s(24 hours) |
| Logging Protocol | Custom protocol to provide seamless integration with external hosts |
| LED status | GREEN: OK, RED: SENSOR FAULT, YELLOW: SENSOR BAD DATA | 

**NOTE**: Increasing the logging frequency shall decrease battery life, default is set to once per second to maximize battery life.
