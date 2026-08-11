/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the yss RTOS runtime example.
 *
 * @details
 * This example demonstrates the yss RTOS runtime timer by continuously
 * printing the elapsed time in milliseconds to the debug output.
 *
 * ### Startup Sequence
 * 1. `initializeYss()` — initializes the yss RTOS kernel, scheduler,
 *    and all enabled peripheral instances defined in `config.h`.
 * 2. `initializeBoard()` — performs board-specific hardware setup
 *    (GPIO pin assignment, peripheral clock enable, etc.).
 * 3. Main loop — polls `runtime::getMsec()` and prints the elapsed
 *    millisecond count via `debug_printf()`.
 */

#include <yss.h>
#include <bsp.h>
#include <yss/debug.h>
#include <util/runtime.h>

/**
 * @brief Application entry point.
 *
 * @details
 * Initializes the yss RTOS and board hardware, then enters an infinite loop
 * that continuously prints the current runtime counter value (in milliseconds)
 * to the debug output using a carriage-return so the value refreshes in place.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	// Initialize the yss RTOS kernel and all enabled peripherals.
	initializeYss();

	// Perform board-specific hardware initialization.
	initializeBoard();

	while(1)
	{
		// Print the elapsed time in milliseconds, overwriting the same line.
		debug_printf("%d\r", (uint32_t)runtime::getMsec());
	}
}
