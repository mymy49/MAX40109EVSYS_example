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
 * Each color channel of the RGB LED is driven by a hardware timer using
 * PWM to control its brightness.
 *
 * ### Hardware Pin Assignment
 * | Color  | GPIO Port | Pin | Timer Alternate Function |
 * |--------|-----------|-----|--------------------------|
 * | Red    | GPIO0     | 29  | TMR5                     |
 * | Blue   | GPIO0     | 30  | TMR0                     |
 * | Green  | GPIO0     | 31  | TMR1                     |
 *
 * The `setDutyRatio()` functions are used to set the PWM duty cycle for each
 * color, enabling smooth fading rather than simple ON/OFF control.
 */

#include <dev/led.h>      ///< RGB LED driver declarations
#include <yss/instance.h> ///< yss hardware peripheral instances (gpio0, etc.)

namespace led
{
	/**
	 * @brief Initializes the RGB LED GPIO pins and PWM timers.
	 *
	 * @details
	 * Configures GPIO0 pins 29, 30, and 31 to use their alternate functions
	 * for hardware timers (TMR5, TMR0, TMR1).
	 * Sets the PWM frequency to 5000 Hz and starts the timers with a 0.0
	 * duty ratio to ensure all three color channels start in the OFF state.
	 */
	void initialize(void)
	{
		gpio0.setAsAltFunc(29, Gpio::P0_29_TMR5); ///< Configure P0.29 as output (Red LED)
		gpio0.setAsAltFunc(30, Gpio::P0_30_TMR0); ///< Configure P0.30 as output (Blue LED)
		gpio0.setAsAltFunc(31, Gpio::P0_31_TMR1); ///< Configure P0.31 as output (Green LED)

		timer5.enableClock();
		timer5.initializeAsPwm(5000);
		timer5.start();
		timer5.setDutyRatio(0.0);

		timer0.enableClock();
		timer0.initializeAsPwm(5000);
		timer0.start();
		timer0.setDutyRatio(0.0);

		timer1.enableClock();
		timer1.initializeAsPwm(5000);
		timer1.start();
		timer1.setDutyRatio(0.0);
	}

	/**
	 * @brief Controls the Red LED brightness.
	 *
	 * @param[in] ratio Duty cycle ratio (0.0 to 1.0).
	 */
	void setRed(float ratio)
	{
		timer5.setDutyRatio(ratio);
	}

	/**
	 * @brief Controls the Blue LED brightness.
	 *
	 * @param[in] ratio Duty cycle ratio (0.0 to 1.0).
	 */
	void setBlue(float ratio)
	{
		timer0.setDutyRatio(ratio);
	}

	/**
	 * @brief Controls the Green LED brightness.
	 *
	 * @param[in] ratio Duty cycle ratio (0.0 to 1.0).
	 */
	void setGreen(float ratio)
	{
		timer1.setDutyRatio(ratio);
	}
}
