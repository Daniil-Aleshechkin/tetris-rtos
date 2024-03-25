/**
 * @file ws2821_display.h
 * @brief Interface and control logic for WS2812 LED display on STM32.
 *
 * This header file defines the interface and control logic for initializing and managing
 * a WS2812 LED display. It provides functions for initializing the display hardware,
 * buffering individual pixel colors, clearing the display buffer, and refreshing the
 * display to show new pixel data. The implementation uses DMA for efficient data transfer.
 */

#ifndef WS2821_DISPLAY
#define WS2821_DISPLAY

#include "stdint.h"

#define DISPLAY_WIDTH 8 ///< The width of the LED display in pixels.
#define DISPLAY_HEIGHT 8 ///< The height of the LED display in pixels.

/**
 * @struct pixel
 * @brief Represents an RGB color pixel.
 *
 * Defines the structure for an RGB color pixel, with separate byte values for red, green, and blue components.
 */
struct pixel {
    uint8_t r; ///< Red component of the pixel.
    uint8_t g; ///< Green component of the pixel.
    uint8_t b; ///< Blue component of the pixel.
};

/**
 * @brief Buffers a single pixel's color at a specified position.
 * 
 * Buffers the color of a single pixel in the display buffer at the specified (x, y) position.
 * The display buffer holds the pixel data to be displayed upon the next refresh.
 * 
 * @param p The pixel color to buffer.
 * @param x The x position of the pixel in the display.
 * @param y The y position of the pixel in the display.
 */
void bufferPixel(struct pixel p, int x, int y);

/**
 * @brief Refreshes the LED display with buffered pixel data.
 * 
 * Transfers the buffered pixel data to the WS2812 LED display using DMA, effectively
 * refreshing the display with new pixel colors. This function handles the timing and
 * data format required by WS2812 LEDs.
 */
void refreshDisplay(void);

/**
 * @brief Initializes the WS2812 LED display.
 * 
 * Prepares the GPIO, DMA, and timer configurations required for controlling the WS2812 LED display.
 * This function must be called before any operations to buffer or display pixel data.
 */
void displayInit(void);

/**
 * @brief Clears the display buffer.
 * 
 * Resets the display buffer to a default state, effectively clearing any buffered pixel data.
 * This does not immediately affect the display; `refreshDisplay()` must be called to update the display.
 */
void clearBuffer(void);

#endif /* WS2821_DISPLAY */
