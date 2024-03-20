#include "ws2821_display.h"
#include "tim2.h"
#include "dma.h"
#include "gpio.h"
#include <stm32f103xb.h>

void fill_dma_buffer(uint16_t *dest, int pos, uint8_t* source);

#define DISPLAY_FRAME_BUFFER_LENGTH DISPLAY_WIDTH*DISPLAY_HEIGHT

// This is what will be sent to the ws2821. Each is a pixel value for G,R,B
static uint8_t display_frame_buffer [DISPLAY_FRAME_BUFFER_LENGTH * 3];

void displayInit() {
	config_gpio();
	config_DMA();
	config_tim2();
	config_DMA1();
	config_DMA2();
	config_DMA3();
	
	for (int i = 0; i < DISPLAY_FRAME_BUFFER_LENGTH*3; i++) {
		display_frame_buffer[i] = ~(uint8_t)0;
	}
}

void clearBuffer() {
	for (int i = 0; i < DISPLAY_FRAME_BUFFER_LENGTH*3; i++) {
		display_frame_buffer[i] = ~(uint8_t)0;
	}
}

void bufferPixel(struct pixel p, int x, int y) {
	int yshift;

	if (x % 2 == 0) {
			yshift = y;
	} else {
			yshift = DISPLAY_HEIGHT - y -1;
	}
	int index = yshift + DISPLAY_HEIGHT * x;

	display_frame_buffer[index*3] = ~p.g;
	display_frame_buffer[index*3+1] = ~p.r;
	display_frame_buffer[index*3+2] = ~p.b;
}

void refreshDisplay() {
	// These are each bits that the DMA channel 5 uses to transfer to the BRR
	// Code currently handles just PB0, so only the first bit is important
	// Each bit is also inverted as the second DMA channel is basically the source of truth of bits
	// Will use 16 size on the final version. 24 is just the testing amount for the real display
	static uint16_t dma_buffer[DMA_BUFFER_SIZE];
	
	int pos = 0;
	
	int max_pos = (DISPLAY_FRAME_BUFFER_LENGTH*3) + 2; // A litter extra is added to give the dma some time to refresh last few bytes
	
	fill_dma_buffer((uint16_t *)dma_buffer, pos, (uint8_t *)display_frame_buffer);
	fill_dma_buffer((uint16_t *)dma_buffer + 8, pos + 1, (uint8_t *)display_frame_buffer);
	pos++;
	pos++;
	stop_all_dma_channels();
	stop_tim2();
	
	// Begin reset timer
	resetLED();
	start_tim2();
	for (int i = 0; i < 225; i++) {
		while(!isTim2Updated());
		resetTime2Update();
	}
	// End reset timer
	stop_tim2();
	start_dma1();
	start_dma2((uint16_t*)&dma_buffer);
	start_dma3();
	
	clearDMAEventFlags();
	
	preOverflowTim2();
	// Begin the data transfer
	start_tim2();
	while (pos < max_pos) {
		if (!isTransferComplete()) {
			continue;
		}
		
		uint16_t *dest = dma_buffer;

		/* Figure out if we're filling the first half of the DMA buffer, or the second half */
		if (DMA1->ISR & DMA_ISR_TCIF5)
				dest += 8;

		/* Clear DMA event flags */
		DMA1->IFCR = (DMA_IFCR_CTCIF5 | DMA_IFCR_CHTIF5);

		/* Unpack one new byte from each channel, into eight words in our DMA buffer
		 * Each 16-bit word in the DMA buffer contains to one bit of the output byte (from each channel)
		 */
		fill_dma_buffer(dest, pos, display_frame_buffer);
		pos++;
	}
	stop_tim2();
	resetLED();
	stop_all_dma_channels();
}

void fill_dma_buffer(uint16_t *dest, int pos, uint8_t* source) {
	dest[0] = source[pos] & 0x1;
	dest[1] = (source[pos] & 0x2) >> 1;
	dest[2] = (source[pos] & 0x4) >> 2;
	dest[3] = (source[pos] & 0x8) >> 3;
	dest[4] = (source[pos] & 0x10) >> 4;
	dest[5] = (source[pos] & 0x20) >> 5;
	dest[6] = (source[pos] & 0x40) >> 6;
	dest[7] = (source[pos] & 0x80) >> 7;
}