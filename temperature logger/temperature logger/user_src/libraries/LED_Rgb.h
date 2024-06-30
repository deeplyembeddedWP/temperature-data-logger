/*
 * LED_RGB.h
 *
 * Created: 29/06/2024 6:23:43 pm
 * Author: Vinay Divakar
 * Brief: subsystem to drive the RGB led to indicate system states
 */

#ifndef LED_RGB_H_
#define LED_RGB_H_

// color to illuminate using PWM
enum LED_RGB_color_t {
  LED_RGB_RED,
  LED_RGB_GREEN,
  LED_RGB_BLUE,
  LED_RGB_YELLOW,
  LED_RGB_PURPLE,
  LED_RGB_ORANGE,
  LED_RGB_WHITE,
  LED_RGB_OFF,
};

void LED_RGB_drive(enum LED_RGB_color_t color);

#endif /* LED_H_ */