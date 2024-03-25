/**
 * @file gpio_ws2821.h
 * @brief GPIO configuration and control for WS2812 (often referred to as WS2821) LED strips on STM32.
 *
 * This header file contains functions for configuring GPIOs to control WS2812 LED strips and
 * includes initialization and reset functionalities. It is designed to prepare the hardware
 * GPIO pins for the data transmission using DMA for precise timing control.
 */

#ifndef GPIO_WS2821
#define GPIO_WS2821

/**
 * @brief Configures GPIO pins for WS2812 control.
 * 
 * Initializes GPIO pins to the correct mode and speed for controlling WS2812 LEDs. This function
 * must be called before attempting to send data to the LEDs to ensure the GPIO is correctly
 * configured for output.
 */
void config_gpio(void);

/**
 * @brief Resets the WS2812 LEDs to a known state.
 * 
 * Pulls the GPIO pin low to reset the WS2812 LEDs. This ensures that the LED strip is
 * in a known state before sending new data.
 */
void resetLED(void);

#endif /* GPIO_WS2821 */
