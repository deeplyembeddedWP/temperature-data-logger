/*
 * Sys_Status_Led.c
 *
 * Created: 30/06/2024 11:48:46 am
 *  Author: Vinay Divakar
 */ 
#include "LED_RGB.h"

void Sys_Status_Led_indicate(enum LED_RGB_color_t color){
	LED_RGB_drive(color);
};
