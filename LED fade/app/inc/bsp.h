/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) public interface for the timer example.
 *
 * @details
 * Provides the public interface of the Board Support Package (BSP) for the
 * MAX40109EVSYS evaluation board.
 *
 * The BSP abstracts hardware-specific initialization details from the
 * application layer. Including this header gives application code access to:
 *   - `initializeBoard()`      — CPU0 board initialization (LED + timer1/2/3)
 *   - `initializeBoardOnCpu1()` — CPU1 board initialization (timer4/5)
 *   - `led` namespace          — RGB LED control functions (via `dev/led.h`)
 *   - `Mutex` class            — yss RTOS mutual-exclusion primitives (via `yss/Mutex.h`)
 *   - `gTimerNCounter`         — Global ISR event counters for timer1~5
 *
 * ### Usage
 * @code
 * #include <bsp.h>
 * ...
 * initializeYss();
 * initializeBoard();   // Call once on CPU0 before the main loop
 * @endcode
 */

#ifndef BSP__H_
#define BSP__H_

#include <stdint.h>    ///< Standard fixed-width integer types (uint8_t, uint32_t, etc.)
#include <yss/Mutex.h> ///< yss Mutex class for thread-safe resource access
#include <dev/led.h>   ///< RGB LED driver interface (led::initialize, setRed, etc.)

/**
 * @brief Initializes CPU0 board-level peripherals (RGB LED and timer1/2/3).
 *
 * @details
 * Must be called once on CPU0 during system startup, after `initializeYss()`
 * and before the main application loop. Configures the RGB LED GPIO pins and
 * starts timer1 (10 Hz), timer2 (100 Hz), and timer3 (1 kHz).
 *
 * Defined in: `app/src/bsp.cpp`
 */
void initializeBoard(void);

/**
 * @brief Initializes CPU1 board-level peripherals (timer4 and timer5).
 *
 * @details
 * Must be called once on CPU1. Starts timer4 (10 kHz) and timer5 (100 kHz).
 * This function is intended for dual-core operation where CPU1 manages its
 * own set of hardware resources independently from CPU0.
 *
 * Defined in: `app/src/bsp.cpp`
 */
void initializeBoardOnCpu1(void);

/**
 * @defgroup TimerCounters Timer ISR Event Counters
 * @brief Global counters incremented by each timer's ISR callback.
 *
 * @details
 * Each counter is incremented once per timer interrupt event:
 *   - `gTimer1Counter` : incremented at  10 Hz (every 100 ms)
 *   - `gTimer2Counter` : incremented at 100 Hz (every  10 ms)
 *   - `gTimer3Counter` : incremented at  1 kHz (every   1 ms)
 *   - `gTimer4Counter` : incremented at 10 kHz (every 100 µs)
 *   - `gTimer5Counter` : incremented at 100 kHz (every  10 µs)
 * @{
 */
extern uint32_t gTimer1Counter; ///< Event count for timer1 ISR (10 Hz)
extern uint32_t gTimer2Counter; ///< Event count for timer2 ISR (100 Hz)
extern uint32_t gTimer3Counter; ///< Event count for timer3 ISR (1 kHz)
extern uint32_t gTimer4Counter; ///< Event count for timer4 ISR (10 kHz)
extern uint32_t gTimer5Counter; ///< Event count for timer5 ISR (100 kHz)
/** @} */

#endif
