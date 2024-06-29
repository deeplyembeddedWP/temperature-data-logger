/*
 * LED.h
 *
 * Created: 29/06/2024 6:23:43 pm
 * Author: Vinay Divakar
 * Brief: subsystem to drive the RGB led to indicate system states
 */

#ifndef LED_H_
#define LED_H_

// color to illuminate using PWM
enum LED_color_t {
  LED_RED,
  LED_GREEN,
  LED_BLUE,
  LED_YELLOW,
  LED_PURPLE,
  LED_ORANGE,
  LED_WHITE,
  LED_OFF,
};

void LED_drive(enum LED_color_t color);

#endif /* LED_H_ */