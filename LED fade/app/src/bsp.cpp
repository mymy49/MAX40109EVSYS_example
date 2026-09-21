/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the LED fade example.
 *
 * @details
 * Implements the board-level hardware initialization routines for the
 * MAX40109EVSYS evaluation board (MAX32665 dual-core MCU).
 *
 * Two initialization functions are provided for dual-core operation:
 *   - `initializeBoard()`       — runs on CPU0: configures the RGB LED
 *                                  PWM timers.
 *   - `initializeBoardOnCpu1()` — runs on CPU1: currently empty.
 */

#include <bsp.h>          ///< BSP declarations (initializeBoard)
#include <yss/instance.h> ///< yss hardware peripheral instances (gpio0, timer1~5)

/**
 * @brief Initializes CPU0 board-level peripherals.
 *
 * @details
 * Called once from `main()` on CPU0 after `initializeYss()`. Performs the
 * following initialization steps in order:
 *
 * 1. **RGB LED** — configures GPIO0 pins 29 (Red), 30 (Blue), 31 (Green)
 *    as alternate functions for PWM timers and initializes the PWM signals.
 */
void initializeBoard()
{
	// Initialize the RGB LED module (GPIO0 pins 29/30/31 -> PWM, all OFF)
	led::initialize();
}

/**
 * @brief Initializes CPU1 board-level peripherals.
 *
 * @details
 * Called once on CPU1. This function is currently empty but is intended
 * to be used for CPU1-specific initialization if required.
 */
void initializeBoardOnCpu1()
{

}
