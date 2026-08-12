/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file config.h
 * @brief yss RTOS and peripheral build-time configuration for the timer example.
 *
 * @details
 * Contains compile-time configuration settings for the yss RTOS framework
 * targeting the MAX40109EVSYS evaluation board (MAX32665 MCU).
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

/// @defgroup TimerEnable Timer Enable Flags
/// @{

/// Timer 0: disabled. TMR0 is reserved for the RUNTIME system tick (YSS_TIMER).
#define TIMER0_ENABLE		false

/// Timer 1: enabled. Used to generate a 10 Hz interrupt (isr_timer1).
#define TIMER1_ENABLE		true

/// Timer 2: enabled. Used to generate a 100 Hz interrupt (isr_timer2).
#define TIMER2_ENABLE		true

/// Timer 3: enabled. Used to generate a 1 kHz interrupt (isr_timer3).
#define TIMER3_ENABLE		true

/// Timer 4: enabled. Used to generate a 10 kHz interrupt (isr_timer4) on CPU1.
#define TIMER4_ENABLE		true

/// Timer 5: enabled. Used to generate a 100 kHz interrupt (isr_timer5) on CPU1.
#define TIMER5_ENABLE		true

/// @}

#endif
