/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_usart_sync.h>

#include <hal_i2c_m_sync.h>

#include <hal_delay.h>

extern struct usart_sync_descriptor UART_Sercom_2;

extern struct i2c_m_sync_desc I2C_Sercom_3;

void UART_Sercom_2_PORT_init(void);
void UART_Sercom_2_CLOCK_init(void);
void UART_Sercom_2_init(void);

void I2C_Sercom_3_CLOCK_init(void);
void I2C_Sercom_3_init(void);
void I2C_Sercom_3_PORT_init(void);

void delay_driver_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
