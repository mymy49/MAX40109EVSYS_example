/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the yss RTOS timer example.
 *
 * @details
 * Demonstrates the use of five hardware timers running at different
 * frequencies on the MAX40109EVSYS evaluation board (MAX32665 dual-core MCU).
 *
 * Five timers are configured in `initializeBoard()` / `initializeBoardOnCpu1()`.
 * Each timer's ISR increments a dedicated global counter, which is then
 * printed to the debug output from the main loop.
 *
 * ### Timer Configuration
 * | Counter         | Timer  | Frequency | Configured by         |
 * |-----------------|--------|-----------|-----------------------|
 * | gTimer1Counter  | timer1 |    10 Hz  | initializeBoard()     |
 * | gTimer2Counter  | timer2 |   100 Hz  | initializeBoard()     |
 * | gTimer3Counter  | timer3 |   1 kHz   | initializeBoard()     |
 * | gTimer4Counter  | timer4 |  10 kHz   | initializeBoardOnCpu1() |
 * | gTimer5Counter  | timer5 | 100 kHz   | initializeBoardOnCpu1() |
 *
 * ### Startup Sequence
 * 1. `initializeYss()`   — Initializes the yss RTOS kernel (scheduler,
 *                           memory management, system timer, etc.).
 * 2. `initializeBoard()` — Configures the RGB LED and starts timer1/2/3
 *                           on CPU0.
 * 3. Main loop           — Continuously prints all five counter values
 *                           to the debug output, overwriting the same line.
 *
 * @note `initializeBoardOnCpu1()` must be called separately on CPU1.
 */

#include <yss.h>          ///< yss RTOS core: scheduler, thread management, etc.
#include <bsp.h>          ///< BSP declarations and gTimerNCounter globals
#include <yss/debug.h>    ///< Debug output utilities (debug_printf, etc.)
#include <util/runtime.h> ///< Runtime utilities: runtime::getMsec() for elapsed time

/**
 * @brief Application entry point.
 *
 * @details
 * Initializes the yss RTOS and board hardware, then enters an infinite main
 * loop that continuously prints the current value of all five timer ISR
 * counters to the debug output, separated by commas. The `\r` character
 * causes the output to refresh in place on the same terminal line.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	// Initialize the yss RTOS kernel (scheduler, system tick, heap, etc.)
	initializeYss();

	// Initialize CPU0 board-level peripherals (RGB LED + timer1/2/3)
	initializeBoard();

	// Main loop: print all five timer ISR counters, refreshing the same line.
	while(1)
	{
		debug_printf("%d, %d, %d, %d, %d\r",
			gTimer1Counter,   // timer1: 10 Hz
			gTimer2Counter,   // timer2: 100 Hz
			gTimer3Counter,   // timer3: 1 kHz
			gTimer4Counter,   // timer4: 10 kHz  (CPU1)
			gTimer5Counter);  // timer5: 100 kHz (CPU1)
	}
}
