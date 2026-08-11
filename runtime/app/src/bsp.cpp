/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

/**
 * @file bsp.cpp
 * @brief Board Support Package (BSP) implementation for the runtime example.
 *
 * @details
 * Implements `initializeBoard()`, which is responsible for all board-specific
 * hardware initialization including GPIO pin configuration, peripheral clock
 * enables, and any other setup that depends on the physical board design.
 *
 * Add peripheral initialization calls here before the application's main loop
 * starts. Refer to the yss driver APIs in `yss/instance.h` for available
 * peripheral instances (e.g., `gpio0`, `uart0`, `spi0`).
 */

#include <bsp.h>
#include <yss/instance.h>

/**
 * @brief Initializes all board-specific hardware peripherals.
 *
 * @details
 * Called once from `main()` after `initializeYss()`. Place GPIO alternate
 * function assignments, clock enables, and peripheral initialization calls
 * here to configure the hardware before the main application loop runs.
 */
void initializeBoard(void)
{

}
