# LED Matrices

## Project Description

This project was aimed at developing drivers for LED matrices and exploring potential applications for these drivers. Two distinct drivers were developed: one for an 8x8 matrix powered by NeoPixel LEDs (WS-2812) and another for a 32x32 matrix from SparkFun (COM-14646). The applications developed include a graphical user interface (GUI) for a Tetris game (My project from 452) and a video player capable of playing the music video "Bad Apple."

## Project Design

### WS-2812 Driver
This driver is based on the STM32F103FastNP library (https://github.com/evilwombat/stm32f103_fastNP) which uses the technique from this block post  https://www.martinhubacek.cz/blog/stm32-ws2812b-dma-library/. The protocol for sending data is time-sensitive, requiring a single serial connection via one pin.

In this protocol:
- A 'zero' is represented by a short pulse.
- A 'one' is represented by a long pulse.
- A reset signal, indicated by a prolonged low signal, marks the end of the data transmission.

The implementation employs DMA and Timer 2:
1. The first DMA channel triggers on Timer 2's start event, sending a byte with all bits set to '1' to the BSRR register to turn the pin high.
2. The second channel sends a byte from our buffer to the BRR register, where a bit '1' resets the pin for a short pulse.
3. The final channel sends a constant '1' to the BRR for the long pulse.
4. The reset signal is executed by turning off the timer after data processing.

### COM-14646 Driver
This driver controls the 32x32 LED matrix, differing significantly from the WS-2812-based 8x8 matrix. It involves manipulating only two of the 32 rows at a time via a shift register, with 13 total pins: 6 for data (RGB values for each row) and 7 for control.

Operations are as follows:
- Data is input, followed by a clock pulse, repeated 32 times.
- A latch pulse is then sent to display the rows.
- The output enable pin turns the rows on or off, which is crucial during row transitions.

The driver operates by sending RGB values and clock pulses for each pixel, waiting via a timer to ensure visibility, and then using the output enable pin to transition between row pairs. This process continues cyclically as only two rows are visible at any given time.

### Tetris GUI Integration
This integration was designed with the original project framework in mind. The existing print task, which runs concurrently with the input task, was modified to use the display driver instead of displaying a text representation of the Tetris board.

### Bad Apple Video Player

This application uses the 32x32 driver to display frames from the "Bad Apple" music video. Each frame is represented by 128 bytes, with each bit corresponding to a pixel in the black and white video. With a need for 1024 pixels per frame and a limitation on flash storage, only about 900-1000 frames can be stored at any time. 

The system operates with two main tasks:
- An input task that reads frames from a USART serial input into a framebuffer.
- A print task that displays the frames.

A major engineering challenge was the real-time transmission and reception of frames over USART which has a risk of data loss. To manage this, a specific byte is sent to indicate readiness for frame transmission, which prompts the corresponding tasks on the sender and receiver sides to coordinate frame transfer effectively. The video runs at approximately 30 frames per second, facilitated by a timer-controlled buffer that runs at 32 Hz.

# Project Testing

# Project Usage

## Project assembly

### 8x8 Matrix

### 32x32 Matrix

## Build and Flashing instructions

### Tetris-RTOS

### Bad-Apple video player

### WS-2812 driver

### COM-14646 driver

## Project Functions and Features

### Tetris-RTOS

### Bad-apple video player