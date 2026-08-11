/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) public interface for the LED blink example.
 *
 * @details
 * This header provides the public interface of the Board Support Package (BSP)
 * for the MAX40109EVSYS evaluation board.
 *
 * The BSP abstracts hardware-specific initialization details from the
 * application layer. Including this header gives application code access to:
 *   - `initializeBoard()` — top-level board initialization function
 *   - `led` namespace     — RGB LED control functions (via `dev/led.h`)
 *   - `Mutex` class       — yss RTOS mutual-exclusion primitives (via `yss/Mutex.h`)
 *
 * ### Usage
 * @code
 * #include <bsp.h>
 * ...
 * initializeBoard();   // Call once before starting threads
 * @endcode
 */

#ifndef BSP__H_
#define BSP__H_

#include <stdint.h>    ///< Standard fixed-width integer types (uint8_t, uint32_t, etc.)
#include <yss/Mutex.h> ///< yss Mutex class for thread-safe resource access
#include <dev/led.h>   ///< RGB LED driver interface (led::initialize, setRed, etc.)

/**
 * @brief Initializes all on-board peripherals required by the application.
 *
 * @details
 * Must be called once during system startup, after `initializeYss()` and
 * before any threads that access hardware are started.
 *
 * Defined in: `app/src/bsp.cpp`
 */
void initializeBoard(void);

#endif
