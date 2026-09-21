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
 * Declares the public API for controlling the on-board RGB LED via PWM.
 * All functions are grouped inside the `led` namespace to avoid naming
 * conflicts with other modules and to clearly indicate their ownership.
 *
 * ### Hardware Pin Mapping
 * | Color  | GPIO Port | Pin | Timer Alternate Function |
 * |--------|-----------|-----|--------------------------|
 * | Red    | GPIO0     | 29  | TMR5                     |
 * | Blue   | GPIO0     | 30  | TMR0                     |
 * | Green  | GPIO0     | 31  | TMR1                     |
 *
 * The driver uses timers to generate PWM signals for each color channel,
 * allowing smooth fading by varying the duty cycle.
 *
 * ### Usage Example
 * @code
 * led::initialize();       // Must be called once before using LED functions
 * led::setRed(0.5f);       // Set Red LED brightness to 50%
 * led::setGreen(0.1f);     // Set Green LED brightness to 10%
 * led::setBlue(1.0f);      // Set Blue LED to maximum brightness
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
	 * @brief Initializes the RGB LED GPIO pins and PWM timers.
	 *
	 * @details
	 * Configures GPIO0 pins 29 (Red), 30 (Blue), and 31 (Green) as alternate
	 * functions for PWM generation using Timer 5, 0, and 1 respectively.
	 * Initializes the PWM frequency to 5kHz and sets the duty ratio to 0.0
	 * for all colors initially.
	 *
	 * This function must be called once — typically from `initializeBoard()` —
	 * before any of the `set*()` functions are used.
	 */
	void initialize(void);

	/**
	 * @brief Controls the Red LED brightness.
	 *
	 * @details
	 * Updates the PWM duty cycle for Timer 5 (P0.29).
	 *
	 * @param[in] ratio The duty cycle ratio from 0.0 (OFF) to 1.0 (fully ON).
	 */
	void setRed(float ratio);

	/**
	 * @brief Controls the Blue LED brightness.
	 *
	 * @details
	 * Updates the PWM duty cycle for Timer 0 (P0.30).
	 *
	 * @param[in] ratio The duty cycle ratio from 0.0 (OFF) to 1.0 (fully ON).
	 */
	void setBlue(float ratio);

	/**
	 * @brief Controls the Green LED brightness.
	 *
	 * @details
	 * Updates the PWM duty cycle for Timer 1 (P0.31).
	 *
	 * @param[in] ratio The duty cycle ratio from 0.0 (OFF) to 1.0 (fully ON).
	 */
	void setGreen(float ratio);
}

#endif
