/*
 * LED.c
 *
 * Created: 29/06/2024 6:23:55 pm
 * Author: Vinay Divakar
 * Brief: subsystem to drive the RGB led to indicate system states
 * Dependencies: PWM drivers
 * TODO: drive the led colors using the relevant PWM driver API's
 */

#include "LED.h"
#include "stdio_start.h"

/**
 * @brief drives the LED
 *
 * @param[in] color intended color for LED to illuminate
 */
void LED_drive(enum LED_color_t color) {
  switch (color) {
  case LED_GREEN:
    // TODO
    break;

  case LED_RED:
    // TODO
    break;

  case LED_YELLOW:
    // TODO
    break;

  default:
    // TODO: drive the LED white to indicate an undefined state
    printf("%s: should never arrive here, seems like a bug? color: %d\r\n",
           __FUNCTION__, color);
    break;
  }
};
