/*
 * Copyright (c) 2015 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file config.h
 * @brief yss RTOS build-time configuration for the runtime example project.
 *
 * @details
 * This file contains valid configuration settings for the Nuvoton M251 series.
 * It is intended to be copied into the user project's include path (app/inc)
 * and renamed to config.h before use.
 *
 * Modify the macro values below to enable or disable peripherals and tune
 * scheduler parameters for the target application.
 */

#ifndef YSS_CONFIG__H_
#define YSS_CONFIG__H_

// ===================== External Crystal Clock Frequency =====================
// If HSE_CLOCK_FREQ is defined, the PLL is configured using the HSE clock
// as its source. If not defined, the HSI clock is used as the PLL source.
// The crystal frequency must be a multiple of 4 MHz.
//#define HSE_CLOCK_FREQ 12000000

// ===================== Scheduler Configuration =====================
/// Timer device used to drive the runtime (scheduler tick) function.
/// Valid options: RUNTIME_TMR0 ~ RUNTIME_TMR5
#define YSS_RUNTIME_TIMER	RUNTIME_TMR0

/// Number of SysTick clocks allocated per thread time-slice.
#define THREAD_GIVEN_CLOCK	20000

/// Maximum number of threads that can be registered simultaneously.
#define MAX_THREAD			16

/// If true, initializes each thread's stack memory with a 0xAA fill pattern
/// to help detect stack overflows during debugging. Set to false in production.
#define FILL_THREAD_STACK	false

// ===================== GUI Configuration =====================
/// Enable or disable the yss GUI library. Set to true to enable.
#define USE_GUI				false

// ===================== KEY Configuration =====================
/// Maximum number of KEY objects that can be created (0 = disabled).
#define NUM_OF_YSS_KEY		0

// ===================== Peripheral Enable / Disable =====================
// Change false to true for each peripheral you want to activate.
//
// Note: Enabling a peripheral that is not wired on the board may cause
//       unexpected behavior. Verify pin assignments before enabling.

// BPWM enable
#define BPWM0_ENABLE		false
#define BPWM1_ENABLE		false

// EADC enable
#define EADC_ENABLE			true

// I2C enable
#define I2C0_ENABLE			false
#define I2C1_ENABLE			false

// I2S enable
#define I2S0_ENABLE			false

// PWM enable
#define PWM0_ENABLE			false
#define PWM1_ENABLE			false
#define PWM2_ENABLE			false
#define PWM3_ENABLE			false

// QSPI enable
#define	QSPI0_ENABLE		true

// SPI enable
#define SPI0_ENABLE			false

// Timer enable
#define TIMER0_ENABLE		false
#define TIMER1_ENABLE		false
#define TIMER2_ENABLE		false
#define TIMER3_ENABLE		false

// UART enable
#define UART0_ENABLE		false
#define UART1_ENABLE		false
#define UART2_ENABLE		false

// USCI enable
#define USPI0_ENABLE		false
#define UUART0_ENABLE		true

#endif
