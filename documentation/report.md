# LED Matrices

# Project Description

This project involved the creation of drivers for LED matrices, as well as exploring applications for these drivers. Two drivers were created, one for a 8x8 powered by neopixel LEDs (WS-2812), and another 32x32 one from sparkfun COM-14646. The two things I did were I apply these drivers as a GUI for my 452 Tetris project, and I created a video player which plays the music video 'Bad apple' (https://www.youtube.com/watch?v=FtutLA63Cp8)

# Project Design

## WS-2812 driver
This was based on the design from the STM32F103fastNP library (https://github.com/evilwombat/stm32f103_fastNP) which uses the technique from this block post  https://www.martinhubacek.cz/blog/stm32-ws2812b-dma-library/

The data just needs to be sent with one serial connection on one pin using a specific protocal which is time sensitive.

Each bit is sent in series with a zero being represented as a short pulse:

And a one being represented with a long pulse:

Then to indicate the data is finished a reset single must be sent which is a long series at 0:

The method I used to send this protocal uses the DMA and timer 2. I use 3 DMA channels which listen to timer events. The first channel listens for the timer 2 begining event. That channel is programmed to send a byte with all 1s to the BSRR register, to set the pin on. The second channel sends a byte from our buffer to the BRR. A 1 in the bit means 0 because we will reset for the short 1 pulse, and do nothing for the long pulse. The final channel always sends a 1 to the BRR, for the long pulse. For the reset signal we just turn the timer off when we're done processing the data.

## COM-14646 driver

## Tetris GUI integration

## Bad-Apple Video player

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