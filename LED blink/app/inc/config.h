/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file config.h
 * @brief yss RTOS and peripheral build-time configuration for the LED blink example.
 *
 * @details
 * Contains compile-time configuration settings for the yss RTOS framework
 * targeting the MAX40109EVSYS evaluation board (Nuvoton M251 series MCU).
 *
 * ### How to Use
 * Copy this file into your project's include directory (`app/inc/`) and
 * rename it to `config.h`. Then adjust the settings below to match your
 * hardware and application requirements.
 *
 * ### Sections
 * 1. External Crystal (HSE) Clock Frequency
 * 2. Scheduler Settings
 * 3. GUI Settings
 * 4. Key Input Settings
 * 5. Peripheral Enable / Disable Flags
 */

#ifndef YSS_CONFIG__H_
#define YSS_CONFIG__H_

// =============================================================================
// Section 1: External Crystal (HSE) Clock Frequency
//
// If HSE_CLOCK_FREQ is defined, the PLL is configured using the external
// high-speed crystal (HSE) as its clock source.
// If HSE_CLOCK_FREQ is NOT defined, the internal high-speed oscillator (HSI)
// is used as the PLL clock source instead.
//
// @note The crystal frequency MUST be a multiple of 4 MHz.
//       Example: 12 MHz crystal -> #define HSE_CLOCK_FREQ 12000000
// =============================================================================
//#define HSE_CLOCK_FREQ 12000000

// =============================================================================
// Section 2: Scheduler Settings
// =============================================================================

/// Hardware timer used by the runtime utility functions.
/// Selects which on-chip timer peripheral provides the system tick for
/// `runtime::getMsec()`, `runtime::getUsec()`, etc.
/// Valid values: RUNTIME_TMR0 ~ RUNTIME_TMR5
#define YSS_TIMER			RUNTIME_TMR0

/// Number of SysTick clock cycles allocated per thread per scheduling quantum
/// (time slice). A larger value means each thread runs longer before being
/// preempted. Adjust based on desired responsiveness vs. context-switch overhead.
#define THREAD_GIVEN_CLOCK	20000

/// Maximum number of threads that can be registered with the RTOS scheduler
/// simultaneously. Increasing this value uses more RAM for internal bookkeeping.
#define MAX_THREAD			16

/// If @c true, each thread's stack memory is pre-filled with the pattern 0xAA
/// at thread creation time. Useful for measuring actual stack usage via a
/// debugger (high-water mark). Set to @c false in production to save startup time.
#define FILL_THREAD_STACK	true

// =============================================================================
// Section 3: GUI Settings
// =============================================================================

/// Enables or disables the built-in yss GUI library.
/// Set to @c true only if a graphical display is connected and the GUI
/// rendering subsystem is required by the application.
#define USE_GUI				false

// =============================================================================
// Section 4: Key Input Settings
// =============================================================================

/// Maximum number of software key objects that can be created.
/// Set to 0 to completely disable the key management subsystem and save RAM.
/// Set to a positive integer to enable key debounce and event handling.
#define NUM_OF_YSS_KEY		0

// =============================================================================
// Section 5: Peripheral Enable / Disable Flags
//
// Each peripheral driver can be individually enabled or disabled to reduce
// code size and RAM usage. Set the corresponding flag to @c true to activate
// the driver for that peripheral, or @c false to exclude it from the build.
//
// @note Only enable peripherals that are actually used by your application.
// =============================================================================

/// @defgroup PeripheralEnable Peripheral Enable Flags
/// @{

// --- BPWM (Basic PWM) -------------------------------------------------------
#define BPWM0_ENABLE		false   ///< Basic PWM channel 0: disabled
#define BPWM1_ENABLE		false   ///< Basic PWM channel 1: disabled

// --- EADC (Enhanced Analog-to-Digital Converter) ----------------------------
#define EADC_ENABLE			true    ///< EADC: enabled (used for analog sensing)

// --- I2C (Inter-Integrated Circuit) -----------------------------------------
#define I2C0_ENABLE			false   ///< I2C bus 0: disabled
#define I2C1_ENABLE			false   ///< I2C bus 1: disabled

// --- I2S (Inter-IC Sound) ---------------------------------------------------
#define I2S0_ENABLE			false   ///< I2S audio interface 0: disabled

// --- PWM (Pulse Width Modulation) -------------------------------------------
#define PWM0_ENABLE			false   ///< PWM channel 0: disabled
#define PWM1_ENABLE			false   ///< PWM channel 1: disabled
#define PWM2_ENABLE			false   ///< PWM channel 2: disabled
#define PWM3_ENABLE			false   ///< PWM channel 3: disabled

// --- QSPI (Quad SPI) --------------------------------------------------------
#define	QSPI0_ENABLE		true    ///< QSPI interface 0: enabled

// --- SPI (Serial Peripheral Interface) --------------------------------------
#define SPI0_ENABLE			false   ///< SPI bus 0: disabled

// --- Timer ------------------------------------------------------------------
#define TIMER0_ENABLE		false   ///< Timer 0: disabled (TMR0 reserved for RUNTIME)
#define TIMER1_ENABLE		false   ///< Timer 1: disabled
#define TIMER2_ENABLE		false   ///< Timer 2: disabled
#define TIMER3_ENABLE		false   ///< Timer 3: disabled

// --- UART (Universal Asynchronous Receiver/Transmitter) ---------------------
#define UART0_ENABLE		false   ///< UART 0: disabled
#define UART1_ENABLE		false   ///< UART 1: disabled
#define UART2_ENABLE		false   ///< UART 2: disabled

// --- USCI (Universal Serial Control Interface) ------------------------------
#define USPI0_ENABLE		false   ///< USCI SPI mode 0: disabled
#define UUART0_ENABLE		true    ///< USCI UART mode 0: enabled (used for debug output)

/// @}

#endif
