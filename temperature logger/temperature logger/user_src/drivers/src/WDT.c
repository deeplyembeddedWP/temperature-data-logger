/*
 * WDT.c
 *
 * Created: 30/06/2024 4:58:27 pm
 * Author: Vinay Divakar
 * Brief: WDT to fire if lockup occurs
 */

#include "driver_init.h"
#include <utils_assert.h>

/**
 * @brief initializes the watchdog timer for a timeout period of 4s
 */
void WDT_init(void) {
  // CLK: 1s per tick
  const uint32_t clk_rate = 1000;
  // timeout: 4s i.e. 4096 ticks
  const uint16_t timeout_period = 4096;

  wdt_set_timeout_period(&WDT_0, clk_rate, timeout_period);
  wdt_enable(&WDT_0);
}

/**
 * @brief reset the watchdog timer
 */
void WDT_feed(void) { 
	wdt_feed(&WDT_0); 
}
