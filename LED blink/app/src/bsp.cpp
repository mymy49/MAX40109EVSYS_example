/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the LED blink example.
 *
 * @details
 * Implements `initializeBoard()`, the single entry point that configures all
 * on-board peripherals required by the LED blink application on the
 * MAX40109EVSYS evaluation board.
 *
 * The BSP acts as an abstraction layer between the application code and the
 * low-level yss hardware drivers, keeping peripheral configuration details
 * out of `main.cpp`.
 *
 * ### Currently Initialized Peripherals
 * - RGB LED — GPIO0 pins 29 (Red), 30 (Blue), 31 (Green)
 */

#include <bsp.h>          ///< BSP declarations (initializeBoard)
#include <yss/instance.h> ///< yss hardware peripheral instances (gpio0, uart0, etc.)

/**
 * @brief Initializes all board-level peripherals needed by the application.
 *
 * @details
 * Called once from `main()` after `initializeYss()` and before the RTOS
 * scheduler starts dispatching threads. Additional peripheral initializations
 * (UART, SPI, I2C, etc.) can be appended here as the application grows.
 *
 * ### Initialization Order
 * 1. RGB LED module — configures GPIO0 pins 29/30/31 as outputs and sets
 *    all LEDs to the OFF state.
 */
void initializeBoard(void)
{
	// Initialize the RGB LED module.
	// Configures GPIO0 pins 29 (Red), 30 (Blue), and 31 (Green) as
	// push-pull digital outputs and sets all LEDs to the OFF state.
	led::initialize();
}
