/**
 * @file util_STM32.c
 * @brief Implementation of system clock initialization and basic delay functionality for STM32 microcontrollers.
 *
 * Provides the implementation for initializing the system clock of STM32 microcontrollers to a specific
 * frequency using either the High-Speed Internal (HSI) oscillator, the High-Speed External (HSE) oscillator,
 * or the PLL. Additionally, it includes a basic delay function that utilizes a simple decrement loop.
 */

#ifndef UTIL_STM32
#define UTIL_STM32

/**
 * @brief Initializes the system clock of the STM32 microcontroller.
 * 
 * This function configures the system clock source and sets up the PLL for desired system frequency.
 * It enables the HSI and HSE oscillators, waits for them to stabilize, then configures and enables the PLL
 * as the system clock source. The function also sets the MCO (Microcontroller Clock Output) to output
 * the system clock on PA8 for observation. The PLL input and multiplication factor are set for optimal
 * performance up to the maximum allowed system clock frequency.
 */
void clockInit(void);

/**
 * @brief Generates a software delay.
 * 
 * Blocks the program execution for a specified amount of loop iterations. The actual time delay
 * depends on the clock configuration and the delay loop execution time.
 * 
 * @param delay The number of iterations to delay, roughly proportional to the desired time delay.
 */
void delay(int delay);
#endif