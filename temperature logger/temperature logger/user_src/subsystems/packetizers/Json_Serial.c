/*
 * json_serial.c
 *
 * Created: 30/06/2024 11:49:48 am
 * Author: Vinay Divakar
 * Brief: module to serial packets for logging. Currently only supports 
 * logging sensor measurement data of type float. Can be extended for other 
 * types in the future.
 */
#include "Json_Serial.h"

/**
 * @brief generic function to serialize and log sensor measurement data
 *
 * @param[in] packet points to the packet to be logged
 * @return None.
 */
void Json_Serial_measurement_log(struct packet_t *packet) {
  ASSERT(packet);
  printf("{\"Type\":\"%s\","
         "\"%s\":{\"value\":\"%.4f\",\"timestamp\":\"%lu\",\"error\":\"%d\"},"
         "}\r\n",
         packet->type, packet->param.name, packet->param.value.value_float,
         packet->param.timestamp, packet->param.error);
}