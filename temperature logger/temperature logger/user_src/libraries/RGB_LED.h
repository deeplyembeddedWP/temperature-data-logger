/*
 * RGB_LED.h
 *
 * Created: 30/06/2024 1:05:41 pm
 * Author: Vinay Divakar
 * Brief: subsystem to drive the RGB led to indicate system states
 */ 


#ifndef RGB_LED_H_
#define RGB_LED_H_

// color to illuminate using PWM to indicated states
enum RGB_LED_color_t {
	RGB_LED_RED,
	RGB_LED_GREEN,
	RGB_LED_BLUE,
	RGB_LED_YELLOW,
	RGB_LED_PURPLE,
	RGB_LED_ORANGE,
	RGB_LED_WHITE,
	RGB_LED_OFF,
};

void RGB_LED_drive(enum RGB_LED_color_t color);





#endif /* RGB_LED_H_ */