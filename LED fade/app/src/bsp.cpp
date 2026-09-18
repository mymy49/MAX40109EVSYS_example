/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the timer example.
 *
 * @details
 * Implements the board-level hardware initialization routines for the
 * MAX40109EVSYS evaluation board (MAX32665 dual-core MCU).
 *
 * Two initialization functions are provided for dual-core operation:
 *   - `initializeBoard()`       — runs on CPU0: configures the RGB LED and
 *                                  starts timer1 (10 Hz), timer2 (100 Hz),
 *                                  and timer3 (1 kHz).
 *   - `initializeBoardOnCpu1()` — runs on CPU1: starts timer4 (10 kHz) and
 *                                  timer5 (100 kHz).
 *
 * ### Timer ISR Callback Summary
 * | ISR            | Timer  | Frequency | Counter Variable |
 * |----------------|--------|-----------|-----------------|
 * | isr_timer1()   | timer1 |    10 Hz  | gTimer1Counter  |
 * | isr_timer2()   | timer2 |   100 Hz  | gTimer2Counter  |
 * | isr_timer3()   | timer3 |   1 kHz   | gTimer3Counter  |
 * | isr_timer4()   | timer4 |  10 kHz   | gTimer4Counter  |
 * | isr_timer5()   | timer5 | 100 kHz   | gTimer5Counter  |
 */

#include <bsp.h>          ///< BSP declarations (initializeBoard, gTimerNCounter)
#include <yss/instance.h> ///< yss hardware peripheral instances (gpio0, timer1~5)

/**
 * @brief Initializes CPU0 board-level peripherals.
 *
 * @details
 * Called once from `main()` on CPU0 after `initializeYss()`. Performs the
 * following initialization steps in order:
 *
 * 1. **RGB LED** — configures GPIO0 pins 29 (Red), 30 (Blue), 31 (Green)
 *    as push-pull outputs and sets all LEDs to the OFF state.
 * 2. **timer1** — started at 10 Hz; ISR callback: `isr_timer1()`.
 * 3. **timer2** — started at 100 Hz; ISR callback: `isr_timer2()`.
 * 4. **timer3** — started at 1 kHz; ISR callback: `isr_timer3()`.
 */
void initializeBoard()
{
	// Initialize the RGB LED module (GPIO0 pins 29/30/31 → push-pull output, all OFF)
	led::initialize();
}

/**
 * @brief Initializes CPU1 board-level peripherals.
 *
 * @details
 * Called once on CPU1. Starts two high-frequency timers managed exclusively
 * by CPU1:
 *
 * 1. **timer4** — started at 10 kHz; ISR callback: `isr_timer4()`.
 * 2. **timer5** — started at 100 kHz; ISR callback: `isr_timer5()`.
 */
void initializeBoardOnCpu1()
{

}
