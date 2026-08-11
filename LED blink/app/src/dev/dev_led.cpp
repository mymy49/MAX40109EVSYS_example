/*
 * Copyright (c) 2026 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file dev_led.cpp
 * @brief RGB LED driver implementation for the MAX40109EVSYS evaluation board.
 *
 * @details
 * Implements the `led` namespace functions declared in `dev/led.h`.
 * Each color channel of the RGB LED is driven by a dedicated GPIO0 pin
 * configured as a push-pull active-low output.
 *
 * ### Hardware Pin Assignment
 * | Color  | GPIO Port | Pin | Active Level |
 * |--------|-----------|-----|--------------|
 * | Red    | GPIO0     | 29  | Active-low   |
 * | Blue   | GPIO0     | 30  | Active-low   |
 * | Green  | GPIO0     | 31  | Active-low   |
 *
 * Because the pins are active-low, the `setOutput()` call inverts the
 * logical `on` parameter (`!on`) so that callers always use
 * `true` = ON and `false` = OFF.
 */

#include <dev/led.h>      ///< RGB LED driver declarations
#include <yss/instance.h> ///< yss hardware peripheral instances (gpio0, etc.)

namespace led
{
	/**
	 * @brief Initializes the RGB LED GPIO pins and sets all LEDs to OFF.
	 *
	 * @details
	 * Configures GPIO0 pins 29, 30, and 31 as push-pull digital outputs,
	 * then calls each set*() function with `false` to ensure all three
	 * color channels start in the OFF state.
	 */
	void initialize(void)
	{
		gpio0.setAsOutput(29); ///< Configure P0.29 as output (Red LED)
		gpio0.setAsOutput(30); ///< Configure P0.30 as output (Blue LED)
		gpio0.setAsOutput(31); ///< Configure P0.31 as output (Green LED)

		setRed(false);   // Ensure Red  LED starts OFF
		setGreen(false); // Ensure Green LED starts OFF
		setBlue(false);  // Ensure Blue  LED starts OFF
	}

	/**
	 * @brief Controls the Red LED (GPIO0 pin 29, active-low).
	 *
	 * @param[in] on @c true to turn the Red LED ON, @c false to turn it OFF.
	 */
	void setRed(bool on)
	{
		gpio0.setOutput(29, !on); // Invert: pin LOW = LED ON (active-low)
	}

	/**
	 * @brief Controls the Blue LED (GPIO0 pin 30, active-low).
	 *
	 * @param[in] on @c true to turn the Blue LED ON, @c false to turn it OFF.
	 */
	void setBlue(bool on)
	{
		gpio0.setOutput(30, !on); // Invert: pin LOW = LED ON (active-low)
	}

	/**
	 * @brief Controls the Green LED (GPIO0 pin 31, active-low).
	 *
	 * @param[in] on @c true to turn the Green LED ON, @c false to turn it OFF.
	 */
	void setGreen(bool on)
	{
		gpio0.setOutput(31, !on); // Invert: pin LOW = LED ON (active-low)
	}
}
