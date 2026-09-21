/*
 * Copyright (c) 2025 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file main.cpp
 * @brief Application entry point for the yss RTOS LED fade example.
 *
 * @details
 * Demonstrates the use of hardware timers for PWM generation and multi-threading
 * on the MAX40109EVSYS evaluation board (MAX32665 dual-core MCU).
 *
 * Three separate threads are created to independently fade the Red, Green,
 * and Blue channels of the on-board RGB LED. Each thread continuously
 * increases and decreases the duty cycle of its respective LED at different
 * rates, creating a dynamic color-blending effect.
 *
 * ### Thread Configuration
 * | Thread             | LED Channel | Delay Step |
 * |--------------------|-------------|------------|
 * | thread_fadeRed     | Red         | 10 ms      |
 * | thread_fadeGreen   | Green       | 20 ms      |
 * | thread_fadeBlue    | Blue        | 30 ms      |
 *
 * ### Startup Sequence
 * 1. `initializeYss()`   — Initializes the yss RTOS kernel (scheduler,
 *                           memory management, system timer, etc.).
 * 2. `initializeBoard()` — Configures the RGB LED PWM timers on CPU0.
 * 3. Thread Creation     — Registers the fading threads with the scheduler.
 * 4. Main loop           — Continuously yields CPU time, allowing the
 *                           scheduler to manage the LED fading threads.
 */

#include <yss.h>          ///< yss RTOS core: scheduler, thread management, etc.
#include <bsp.h>          ///< BSP declarations
#include <yss/debug.h>    ///< Debug output utilities (debug_printf, etc.)
#include <util/runtime.h> ///< Runtime utilities: runtime::getMsec() for elapsed time

/**
 * @brief Thread function to fade the Red LED.
 *
 * @details
 * Continuously ramps the Red LED brightness up from 0 to 1 and back down to 0
 * using a 10 ms delay between 0.05 step updates.
 */
void thread_fadeRed(void)
{
	float ratio = 0;

	while(1)
	{
		do
		{
			ratio += 0.05;
			led::setRed(ratio);
			thread::delay(10);
		}while(ratio < 1);

		do
		{
			ratio -= 0.05;
			led::setRed(ratio);
			thread::delay(10);
		}while(ratio > 0);
	}
}

/**
 * @brief Thread function to fade the Green LED.
 *
 * @details
 * Continuously ramps the Green LED brightness up from 0 to 1 and back down to 0
 * using a 20 ms delay between 0.05 step updates.
 */
void thread_fadeGreen(void)
{
	float ratio = 0;

	while(1)
	{
		do
		{
			ratio += 0.05;
			led::setGreen(ratio);
			thread::delay(20);
		}while(ratio < 1);

		do
		{
			ratio -= 0.05;
			led::setGreen(ratio);
			thread::delay(20);
		}while(ratio > 0);
	}
}

/**
 * @brief Thread function to fade the Blue LED.
 *
 * @details
 * Continuously ramps the Blue LED brightness up from 0 to 1 and back down to 0
 * using a 30 ms delay between 0.05 step updates.
 */
void thread_fadeBlue(void)
{
	float ratio = 0;

	while(1)
	{
		do
		{
			ratio += 0.05;
			led::setBlue(ratio);
			thread::delay(30);
		}while(ratio < 1);

		do
		{
			ratio -= 0.05;
			led::setBlue(ratio);
			thread::delay(30);
		}while(ratio > 0);
	}
}

/**
 * @brief Application entry point.
 *
 * @details
 * Initializes the yss RTOS and board hardware, creates the three LED fade
 * threads, and enters an infinite main loop that simply yields CPU time.
 *
 * @return int This function never returns under normal operation.
 */
int main(void)
{
	// Initialize the yss RTOS kernel (scheduler, system tick, heap, etc.)
	initializeYss();

	// Initialize CPU0 board-level peripherals (RGB LED PWM timers)
	initializeBoard();

	// Add the LED fading threads to the scheduler with a 512-byte stack size each
	thread::add(thread_fadeRed, 512);
	thread::add(thread_fadeGreen, 512);
	thread::add(thread_fadeBlue, 512);

	// Main loop: continuously yield to other threads
	while(1)
	{
		thread::yield();
	}
}
