/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.h
 * @brief Board Support Package (BSP) public interface for the runtime example.
 *
 * @details
 * Declares the board-level initialization function that must be called once
 * during startup, after the yss RTOS is initialized and before the main
 * application loop begins.
 */

#ifndef BSP__H_
#define BSP__H_

#include <stdint.h>

/**
 * @brief Initializes all board-specific hardware.
 *
 * @details
 * Configures GPIO alternate functions, enables peripheral clocks, and
 * performs any other board-specific hardware initialization required
 * before the application begins. This function must be called once from
 * main() after `initializeYss()`.
 */
void initializeBoard(void);

#endif
