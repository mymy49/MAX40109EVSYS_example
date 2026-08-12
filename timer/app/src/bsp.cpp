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
 * @brief Global event counters incremented by each timer ISR.
 * @details Declared extern in bsp.h; defined here on CPU0's data segment.
 */
uint32_t gTimer1Counter, gTimer2Counter, gTimer3Counter, gTimer4Counter, gTimer5Counter;

/**
 * @brief ISR callback for timer1 (10 Hz).
 * @details Called by the yss timer driver every time timer1 overflows.
 *          Increments gTimer1Counter. Do NOT call context-switching functions here.
 * @warning Must not call any yss function that triggers a context switch.
 */
void isr_timer1(void)
{
	gTimer1Counter++;
}

/**
 * @brief ISR callback for timer2 (100 Hz).
 * @details Called by the yss timer driver every time timer2 overflows.
 *          Increments gTimer2Counter. Do NOT call context-switching functions here.
 * @warning Must not call any yss function that triggers a context switch.
 */
void isr_timer2(void)
{
	gTimer2Counter++;
}

/**
 * @brief ISR callback for timer3 (1 kHz).
 * @details Called by the yss timer driver every time timer3 overflows.
 *          Increments gTimer3Counter. Do NOT call context-switching functions here.
 * @warning Must not call any yss function that triggers a context switch.
 */
void isr_timer3(void)
{
	gTimer3Counter++;
}

/**
 * @brief ISR callback for timer4 (10 kHz), executed on CPU1.
 * @details Called by the yss timer driver every time timer4 overflows.
 *          Increments gTimer4Counter. Do NOT call context-switching functions here.
 * @warning Must not call any yss function that triggers a context switch.
 */
void isr_timer4(void)
{
	gTimer4Counter++;
}

/**
 * @brief ISR callback for timer5 (100 kHz), executed on CPU1.
 * @details Called by the yss timer driver every time timer5 overflows.
 *          Increments gTimer5Counter. Do NOT call context-switching functions here.
 * @warning Must not call any yss function that triggers a context switch.
 */
void isr_timer5(void)
{
	gTimer5Counter++;
}

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

	// timer1: 10 Hz interrupt — isr_timer1() increments gTimer1Counter
	timer1.enableClock();
	timer1.initialize(10);
	timer1.setIsrForUpdate(isr_timer1);
	timer1.enableInterrupt();

	// timer2: 100 Hz interrupt — isr_timer2() increments gTimer2Counter
	timer2.enableClock();
	timer2.initialize(100);
	timer2.setIsrForUpdate(isr_timer2);
	timer2.enableInterrupt();

	// timer3: 1 kHz interrupt — isr_timer3() increments gTimer3Counter
	timer3.enableClock();
	timer3.initialize(1000);
	timer3.setIsrForUpdate(isr_timer3);
	timer3.enableInterrupt();
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
	// timer4: 10 kHz interrupt — isr_timer4() increments gTimer4Counter
	timer4.enableClock();
	timer4.initialize(10000);
	timer4.setIsrForUpdate(isr_timer4);
	timer4.enableInterrupt();

	// timer5: 100 kHz interrupt — isr_timer5() increments gTimer5Counter
	timer5.enableClock();
	timer5.initialize(100000);
	timer5.setIsrForUpdate(isr_timer5);
	timer5.enableInterrupt();
}
