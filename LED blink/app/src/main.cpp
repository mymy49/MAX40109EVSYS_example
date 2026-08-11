/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the yss RTOS LED blink example.
 *
 * @details
 * Demonstrates a basic multi-threaded LED blink application running on the
 * MAX40109EVSYS evaluation board using the yss RTOS framework.
 *
 * Three independent threads are created, each responsible for blinking one
 * color channel of an RGB LED at a different frequency:
 *
 * | Thread            | Frequency | Period   | ON time | OFF time |
 * |-------------------|-----------|----------|---------|----------|
 * | thread_blinkRed   | 0.5 Hz    | 2000 ms  | 1000 ms | 1000 ms  |
 * | thread_blinkGreen | 1.0 Hz    | 1000 ms  |  500 ms |  500 ms  |
 * | thread_blinkBlue  | 2.0 Hz    |  500 ms  |  250 ms |  250 ms  |
 *
 * The main thread continuously prints the system runtime in milliseconds to
 * the debug output, which can be viewed via a serial terminal.
 *
 * ### Startup Sequence
 * 1. `initializeYss()`   — Initializes the yss RTOS kernel (scheduler,
 *                           memory management, system timer, etc.).
 * 2. `initializeBoard()` — Configures board-specific peripherals (GPIO pins
 *                           for LEDs, clock sources, etc.).
 * 3. `thread::add()`     — Registers each LED blink thread with the scheduler.
 *                           The second argument (512) is the stack size in
 *                           bytes allocated for that thread.
 */

#include <yss.h>          ///< yss RTOS core: scheduler, thread management, etc.
#include <bsp.h>          ///< Board Support Package: hardware initialization
#include <yss/debug.h>    ///< Debug output utilities (debug_printf, etc.)
#include <util/runtime.h> ///< Runtime utilities: runtime::getMsec() for elapsed time

/**
 * @brief Global debug counters reserved for debugging purposes.
 *
 * @details
 * Marked `volatile` to prevent the compiler from optimizing them away,
 * ensuring they are always accessible via a debugger or watch window.
 */
volatile uint32_t gDebugCount3, gDebugCount4, gDebugCount5;

/**
 * @brief Thread function that blinks the Red LED at 0.5 Hz.
 *
 * @details
 * Toggles the Red LED with a 1000 ms ON / 1000 ms OFF duty cycle (period =
 * 2000 ms, frequency = 0.5 Hz). `thread::delay()` yields the CPU to other
 * threads during the wait period, allowing the RTOS scheduler to run other
 * tasks concurrently. This function never returns.
 */
void thread_blinkRed(void)
{
	while(1)
	{
		led::setRed(true);   // Turn the Red LED ON
		thread::delay(1000); // Wait 1000 ms, yielding CPU to other threads

		led::setRed(false);  // Turn the Red LED OFF
		thread::delay(1000); // Wait 1000 ms, yielding CPU to other threads
	}
}

/**
 * @brief Thread function that blinks the Green LED at 1.0 Hz.
 *
 * @details
 * Toggles the Green LED with a 500 ms ON / 500 ms OFF duty cycle (period =
 * 1000 ms, frequency = 1.0 Hz). Runs twice as fast as the Red LED thread.
 * This function never returns.
 */
void thread_blinkGreen(void)
{
	while(1)
	{
		led::setGreen(true);  // Turn the Green LED ON
		thread::delay(500);   // Wait 500 ms, yielding CPU to other threads

		led::setGreen(false); // Turn the Green LED OFF
		thread::delay(500);   // Wait 500 ms, yielding CPU to other threads
	}
}

/**
 * @brief Thread function that blinks the Blue LED at 2.0 Hz.
 *
 * @details
 * Toggles the Blue LED with a 250 ms ON / 250 ms OFF duty cycle (period =
 * 500 ms, frequency = 2.0 Hz). Runs four times as fast as the Red LED thread.
 * This function never returns.
 */
void thread_blinkBlue(void)
{
	while(1)
	{
		led::setBlue(true);  // Turn the Blue LED ON
		thread::delay(250);  // Wait 250 ms, yielding CPU to other threads

		led::setBlue(false); // Turn the Blue LED OFF
		thread::delay(250);  // Wait 250 ms, yielding CPU to other threads
	}
}

/**
 * @brief Application entry point.
 *
 * @details
 * Initializes the yss RTOS and board hardware, registers the three LED
 * blink threads with the scheduler, then enters an infinite main loop
 * that prints the elapsed runtime in milliseconds to the debug output.
 * The `\r` character causes the terminal value to refresh in place.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	threadId_t id; ///< Thread ID handle (reserved for future use)

	// Initialize the yss RTOS kernel (scheduler, system tick, heap, etc.)
	initializeYss();

	// Initialize board-level peripherals (LED GPIO pins, etc.)
	initializeBoard();

	// Register the Red LED blink thread with a 512-byte stack
	thread::add(thread_blinkRed, 512);

	// Register the Green LED blink thread with a 512-byte stack
	thread::add(thread_blinkGreen, 512);

	// Register the Blue LED blink thread with a 512-byte stack
	thread::add(thread_blinkBlue, 512);

	// Main loop: continuously print the elapsed runtime in milliseconds.
	// runtime::getMsec() returns the number of milliseconds since system boot.
	// The '\r' character overwrites the same terminal line for a clean display.
	while(1)
	{
		debug_printf("Runtime : %d\r", (uint32_t)runtime::getMsec());
	}
}
