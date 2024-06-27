/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using UART_Sercom_2 to write "Hello World" using the IO abstraction.
 */
void UART_Sercom_2_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&UART_Sercom_2, &io);
	usart_sync_enable(&UART_Sercom_2);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void I2C_Sercom_3_example(void)
{
	struct io_descriptor *I2C_Sercom_3_io;

	i2c_m_sync_get_io_descriptor(&I2C_Sercom_3, &I2C_Sercom_3_io);
	i2c_m_sync_enable(&I2C_Sercom_3);
	i2c_m_sync_set_slaveaddr(&I2C_Sercom_3, 0x12, I2C_M_SEVEN);
	io_write(I2C_Sercom_3_io, (uint8_t *)"Hello World!", 12);
}

void delay_example(void)
{
	delay_ms(5000);
}
