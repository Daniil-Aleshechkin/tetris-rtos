/**
 * @file dma.h
 * @brief DMA configuration and control for WS2812 LED strip on STM32.
 *
 * This header file contains functions for configuring DMA channels to control a WS2812 LED strip.
 * It provides a way to send data to the LEDs using DMA channels to achieve precise timing required
 * by WS2812 protocol, thus freeing the CPU for other operations.
 */

#ifndef DMA_WS2812
#define DMA_WS2812

#include "stdint.h"
#include "stdbool.h"

#define DMA_BUFFER_SIZE 16 ///< Define the size of the DMA buffer for WS2812 data.

/**
 * @brief Initializes DMA channels for WS2812 control.
 * 
 * Enables DMA1 clock and sets priority for DMA1 Channel2 interrupt.
 */
void config_DMA(void);

/**
 * @brief Configures DMA1 Channel 2 for WS2812 data transfer.
 * 
 * Sets up DMA1 Channel 2 for memory-to-peripheral transfer to send data to WS2812 LEDs.
 */
void config_DMA1(void);

/**
 * @brief Configures DMA1 Channel 5 for WS2812 data transfer.
 * 
 * Sets up DMA1 Channel 5 for memory-to-peripheral transfer to send data to WS2812 LEDs.
 * Allows memory increment to send variable data.
 */
void config_DMA2(void);

/**
 * @brief Configures DMA1 Channel 7 for WS2812 data transfer.
 * 
 * Sets up DMA1 Channel 7 for memory-to-peripheral transfer to finalize the signal for WS2812 LEDs.
 */
void config_DMA3(void);

/**
 * @brief Starts DMA1 Channel 2 transfer.
 * 
 * Initiates the transfer of data for WS2812 LED initialization signal.
 */
void start_dma1(void);

/**
 * @brief Starts DMA1 Channel 5 transfer with a given buffer.
 * 
 * @param buffer Pointer to the data buffer to be transferred to WS2812 LEDs.
 */
void start_dma2(uint16_t* buffer);

/**
 * @brief Starts DMA1 Channel 7 transfer.
 * 
 * Initiates the transfer to finalize the signal for WS2812 LEDs.
 */
void start_dma3(void);

/**
 * @brief Stops all DMA transfers related to WS2812 control.
 * 
 * Disables DMA transfer for all related channels to stop sending data to WS2812 LEDs.
 */
void stop_all_dma_channels(void);

/**
 * @brief Checks if the DMA transfer is complete.
 * 
 * @return true if the transfer is complete, false otherwise.
 */
bool isTransferComplete(void);

/**
 * @brief Checks if the full DMA transfer is complete.
 * 
 * @return true if the full transfer is complete, false otherwise.
 */
bool isFullTransferComplete(void);

/**
 * @brief Clears DMA event flags.
 * 
 * Resets the flags associated with DMA transfer events.
 */
void clearDMAEventFlags(void);

#endif /* DMA_WS2812 */
