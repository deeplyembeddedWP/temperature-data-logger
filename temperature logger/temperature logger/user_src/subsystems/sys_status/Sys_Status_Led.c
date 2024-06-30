/*
 * Sys_Status_Led.c
 *
 * Created: 30/06/2024 11:48:46 am
 * Author: Vinay Divakar
 * Brief: module to drive system LEDS
 * Dependencies: RGB_LED, PWM
 */ 

#include "Sys_Status_Led.h"

/**
 * @brief drives the LED to indicate system status
 *
 * @param[in] color RGB color
 * @return None.
 */
void Sys_Status_Led_indicate(enum RGB_LED_color_t color){
	RGB_LED_drive(color);
};
