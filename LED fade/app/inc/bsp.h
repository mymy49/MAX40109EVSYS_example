/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) public interface for the LED fade example.
 *
 * @details
 * Provides the public interface of the Board Support Package (BSP) for the
 * MAX40109EVSYS evaluation board.
 *
 * The BSP abstracts hardware-specific initialization details from the
 * application layer. Including this header gives application code access to:
 *   - `initializeBoard()`      — CPU0 board initialization (RGB LED PWM timers)
 *   - `initializeBoardOnCpu1()` — CPU1 board initialization (empty in this example)
 *   - `led` namespace          — RGB LED control functions (via `dev/led.h`)
 *   - `Mutex` class            — yss RTOS mutual-exclusion primitives (via `yss/Mutex.h`)
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
 * @brief Initializes CPU0 board-level peripherals.
 *
 * @details
 * Must be called once on CPU0 during system startup, after `initializeYss()`
 * and before the main application loop. Configures the RGB LED GPIO pins and
 * starts Timer 0, 1, 5 for PWM generation.
 *
 * Defined in: `app/src/bsp.cpp`
 */
void initializeBoard(void);

/**
 * @brief Initializes CPU1 board-level peripherals.
 *
 * @details
 * Must be called once on CPU1. This function is currently empty in this
 * example, but is intended for dual-core operation where CPU1 manages its
 * own set of hardware resources independently from CPU0.
 *
 * Defined in: `app/src/bsp.cpp`
 */
void initializeBoardOnCpu1(void);

#endif
