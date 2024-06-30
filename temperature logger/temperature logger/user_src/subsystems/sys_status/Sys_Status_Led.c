/*
 * Sys_Status_Led.c
 *
 * Created: 30/06/2024 11:48:46 am
 *  Author: Vinay Divakar
 */ 
#include "RGB_LED.h"

void Sys_Status_Led_indicate(enum RGB_LED_color_t color){
	RGB_LED_drive(color);
};
