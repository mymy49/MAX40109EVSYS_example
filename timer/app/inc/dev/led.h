/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file led.h
 * @brief RGB LED driver public interface for the MAX40109EVSYS evaluation board.
 *
 * @details
 * Declares the public API for controlling the on-board RGB LED.
 * All functions are grouped inside the `led` namespace to avoid naming
 * conflicts with other modules and to clearly indicate their ownership.
 *
 * ### Hardware Pin Mapping
 * | Color  | GPIO Port | Pin | Active Level |
 * |--------|-----------|-----|--------------|
 * | Red    | GPIO0     | 29  | Active-low   |
 * | Blue   | GPIO0     | 30  | Active-low   |
 * | Green  | GPIO0     | 31  | Active-low   |
 *
 * The driver inverts the logic internally so that callers always use
 * logical `true` = ON and `false` = OFF, regardless of the hardware polarity.
 *
 * ### Usage Example
 * @code
 * led::initialize();    // Must be called once before using LED functions
 * led::setRed(true);    // Turn Red LED ON
 * led::setGreen(false); // Turn Green LED OFF
 * led::setBlue(true);   // Turn Blue LED ON
 * @endcode
 */

#ifndef DEV_LED__H_
#define DEV_LED__H_

#include <stdint.h> ///< Standard fixed-width integer types

/**
 * @namespace led
 * @brief Namespace encapsulating all RGB LED control functions.
 */
namespace led
{
	/**
	 * @brief Initializes the RGB LED GPIO pins as digital outputs.
	 *
	 * @details
	 * Configures GPIO0 pins 29 (Red), 30 (Blue), and 31 (Green) as push-pull
	 * digital outputs and sets all three LEDs to the OFF state as the
	 * default initial condition.
	 *
	 * This function must be called once — typically from `initializeBoard()` —
	 * before any of the `set*()` functions are used.
	 */
	void initialize(void);

	/**
	 * @brief Controls the Red LED.
	 *
	 * @details
	 * The underlying GPIO pin (P0.29) is active-low; the driver inverts the
	 * signal internally so callers always use logical ON/OFF semantics.
	 *
	 * @param[in] on @c true to turn the Red LED ON, @c false to turn it OFF.
	 */
	void setRed(bool on);

	/**
	 * @brief Controls the Blue LED.
	 *
	 * @details
	 * The underlying GPIO pin (P0.30) is active-low; the driver inverts the
	 * signal internally.
	 *
	 * @param[in] on @c true to turn the Blue LED ON, @c false to turn it OFF.
	 */
	void setBlue(bool on);

	/**
	 * @brief Controls the Green LED.
	 *
	 * @details
	 * The underlying GPIO pin (P0.31) is active-low; the driver inverts the
	 * signal internally.
	 *
	 * @param[in] on @c true to turn the Green LED ON, @c false to turn it OFF.
	 */
	void setGreen(bool on);
}

#endif
