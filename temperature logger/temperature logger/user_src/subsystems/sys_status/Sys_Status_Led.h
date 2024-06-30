/*
 * Sys_Status_Led.h
 *
 * Created: 30/06/2024 11:48:00 am
 * Author: Vinay Divakar
 * Brief: module to drive system LEDS
 */ 


#ifndef SYS_STATUS_LED_H_
#define SYS_STATUS_LED_H_

#include "RGB_LED.h"
void Sys_Status_Led_indicate(enum RGB_LED_color_t color);

#endif /* SYS_STATUS_LED_H_ */