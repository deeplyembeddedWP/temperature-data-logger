/*
 * Json_Serial.h
 *
 * Created: 30/06/2024 11:50:30 am
 * Author: Vinay Divakar
 * Brief: module to serial packets for logging. Currently only supports
 * logging sensor measurement data of type float. Can be extended for other
 * types in the future.
 */ 

#ifndef JSON_SERIAL_H_
#define JSON_SERIAL_H_

#include "Packet.h"
#include "stdio_start.h"
#include <utils_assert.h>

void Json_Serial_measurement_log(struct packet_t *packet);

#endif /* JSON_SERIAL_H_ */