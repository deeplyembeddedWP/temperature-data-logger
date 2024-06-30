#include <atmel_start.h>
#include "user_src/drivers/include/I2C.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	I2C_begin();

	/* Replace with your application code */
	while (1) {
	}
}
