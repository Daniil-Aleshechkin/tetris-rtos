/**
 * @file tim2.h
 * @brief Configuration and control of TIM2 for WS2812 LED driving on STM32.
 *
 * This header file provides functions to configure and control Timer 2 (TIM2) of the STM32
 * microcontroller for generating precise timing signals required by WS2812 LEDs. It includes
 * setup for PWM outputs and utility functions to start, stop, and manage the timer's operation.
 */

#ifndef TIM2_WS2812
#define TIM2_WS2812

#include "stdbool.h"
#include <stm32f103xb.h>

#define TIMER2_FREQ_HZ          72000000 ///< Frequency of Timer 2.
#define WS2812_TIMER_PERIOD        (((TIMER2_FREQ_HZ / 1000) * 125) / 100000) ///< Timer period for WS2812 bit timing.
#define WS2812_TIMER_PWM_CH1_TIME  (((TIMER2_FREQ_HZ / 1000) *  40) / 100000) ///< PWM high time for a WS2812 '0' bit.
#define WS2812_TIMER_PWM_CH2_TIME  (((TIMER2_FREQ_HZ / 1000) *  80) / 100000) ///< PWM high time for a WS2812 '1' bit.

/**
 * @brief Configures TIM2 for WS2812 LED signal generation.
 * 
 * Sets up TIM2 with specific period and pulse widths to generate the signal timings required by WS2812 LEDs.
 * This configuration sets up PWM output for controlling the LEDs.
 */
void config_tim2(void);

/**
 * @brief Starts TIM2 for WS2812 signal transmission.
 * 
 * Enables TIM2 and waits for the update interrupt flag to ensure the timer is running. This function
 * should be called after `config_tim2()` and before sending data to WS2812 LEDs.
 */
void start_tim2(void);

/**
 * @brief Stops TIM2 to halt WS2812 signal transmission.
 * 
 * Disables TIM2 to stop sending signals to WS2812 LEDs. This function can be used to reset or stop
 * the LED strip operation.
 */
void stop_tim2(void);

/**
 * @brief Sets TIM2 counter close to overflow.
 * 
 * Preloads the TIM2 counter to a value close to overflow. This function can be used to synchronize
 * the timer overflow with specific operations, such as resetting the WS2812 LEDs.
 */
void preOverflowTim2(void);

/**
 * @brief Checks if TIM2 has updated since the last check.
 * 
 * @return true if TIM2 has reached an update event (overflow), false otherwise.
 */
bool isTim2Updated(void);

/**
 * @brief Resets the update interrupt flag for TIM2.
 * 
 * Clears the update interrupt flag of TIM2 to prepare for detecting the next update event.
 */
void resetTime2Update(void);

#endif /* TIM2_WS2812 */
