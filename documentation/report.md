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
This driver was for the 32x32 LED matrix. It worked completely differently from the 8x8 which was based on ws-2812s. Instead of taking in one stream from one channel, and remembering it, you could only control 2 of the 32 rows using a shift register.

The display had 13 total pins with 6 data pins, and 7 control pins. 4 of the 7 are to control which of the 32 rows the data pins would multiplex to. As there are 32 rows and you selected 2 at a time, there are 16 possible configurations. The other 3 are the latch pin, the clock pin, and the output enable pin.

The data pins are the RGB values for each row making 6 total pins. You input the data you wish to send then send a clock pulse, and repeat 32 times. When all the data is sent, you need to send a pusle to the latch pin to actually display the rows. The output enable pins simply turns the rows on and off. This is useful when transitioning rows, as they are not cleared when you change which rows you display.

I simply used based GPIO control to make my driver. The driver first sent the RGB values for the 1st pixel of the top and bottom row I control, then it sent a clock pulse and repeated 32 times for each pixel. When it was done it sent a latch pulse. After the latch I had it wait for a timer to ensure the rows were on long enough for them to be actually visible. Then I turned off the rows using the output enable pin and transitioned to the next 2 rows. After all 16 were processed, the refresh would have been complete.

Unlike the other driver this must be constantly called as only 2 out of the 32 rows would ever be on at a time. 

## Tetris GUI integration
This integration was very simple as I designed the orginal project with this extention in mind. There already was a print task that ran currently with the input task. To ensure the application displayed using the display driver, I simply replaced the code in the print task that sent a text representation of the board state with code that would buffer and refresh a new frame. 

## Bad-Apple Video player

The bad apple video player uses the 32x32 driver I wrote. Each frame of the video consisted of 128 bytes. Each bit represented a pixel as the video is in black and white, and I needed a total of 32x32=1024 pixels. I could not store all 6562 frames in flash, at maximum about 900-1000 frames could be stored as I compresed each frame to 128 bytes. Because of this I needed to send each frame and display it at runtime. It like my tetris app relies on two tasks, an input task and a print task. The input task reads froma USART serial input and writes to a framebuffer which the print task prints. The biggest engineering challenge was to send a frame via USART as bytes sent via USART are lost if they are not read. To ensure I send and recieve a frame without missing a byte, I sent a hardcoded byte and had the input task attempt to recieve it. This byte would indicate that a frame is ready to be sent by the client. The input task would then send another hardcoded byte to indicate to the client that a frame is ready to be recieved, then the client would send the frame. While the client is sending the frame, the input task echoes what's received, and the client ensures the amount of bytes echoed is equal to 128 before sending a new frame. When the loading is done the input task stores the received frame in a 7 frame buffer, and it listens to a timer which runs about 32 times a second before popping that buffer and switching to the next frame.

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