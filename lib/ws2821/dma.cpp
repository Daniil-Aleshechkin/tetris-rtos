#include "dma.h"
#include "stdbool.h"
#include <stm32f103xb.h>


static const uint16_t ws2812_gpio_set_bits = 0xFFFF; // We're only touching PB0 for now

static uint16_t dmaBuffer[DMA_BUFFER_SIZE];

void config_DMA(void) {
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	uint32_t prioritygroup = NVIC_GetPriorityGrouping();
	
	NVIC_SetPriority(DMA1_Channel2_IRQn, NVIC_EncodePriority(prioritygroup, 0, 0));
}

void config_DMA1(void) {
	DMA1_Channel2->CCR &= ~DMA_CCR_MEM2MEM; // We want mem -> periferal
	DMA1_Channel2->CCR |= DMA_CCR_DIR;
	DMA1_Channel2->CCR &= ~DMA_CCR_MINC; // No perf or mem incrment modes
	DMA1_Channel2->CCR &= ~DMA_CCR_PINC;
	DMA1_Channel2->CCR &= ~DMA_CCR_PSIZE; // Word size perifiral
	DMA1_Channel2->CCR |= DMA_CCR_PSIZE_1;
	DMA1_Channel2->CCR &= ~DMA_CCR_MSIZE; // Half word size memory
	DMA1_Channel2->CCR |= DMA_CCR_MSIZE_0;
	DMA1_Channel2->CCR |= DMA_CCR_CIRC; // Circular mode enabled
	DMA1_Channel2->CCR |= DMA_CCR_PL; // Very high priority
}

void config_DMA2(void) {
	DMA1_Channel5->CCR &= ~DMA_CCR_MEM2MEM; // We want mem -> periferal
	DMA1_Channel5->CCR |= DMA_CCR_DIR;
	DMA1_Channel5->CCR |= DMA_CCR_MINC; // Mem incrment mode only
	DMA1_Channel5->CCR &= ~DMA_CCR_PINC;
	DMA1_Channel5->CCR &= ~DMA_CCR_PSIZE; // Word size perifiral
	DMA1_Channel5->CCR |= DMA_CCR_PSIZE_1;
	DMA1_Channel5->CCR &= ~DMA_CCR_MSIZE; // Half word size memory
	DMA1_Channel5->CCR |= DMA_CCR_MSIZE_0;
	DMA1_Channel5->CCR |= DMA_CCR_CIRC; // Circular mode enabled
	DMA1_Channel5->CCR |= DMA_CCR_PL; // Very high priority
}

void config_DMA3(void) {
	DMA1_Channel7->CCR &= ~DMA_CCR_MEM2MEM; // We want mem -> periferal
	DMA1_Channel7->CCR |= DMA_CCR_DIR;
	DMA1_Channel7->CCR &= ~DMA_CCR_MINC; // No perf or mem incrment modes
	DMA1_Channel7->CCR &= ~DMA_CCR_PINC;
	DMA1_Channel7->CCR &= ~DMA_CCR_PSIZE; // Word size perifiral
	DMA1_Channel7->CCR |= DMA_CCR_PSIZE_1;
	DMA1_Channel7->CCR &= ~DMA_CCR_MSIZE; // Half word size memory
	DMA1_Channel7->CCR |= DMA_CCR_MSIZE_0;
	DMA1_Channel7->CCR |= DMA_CCR_CIRC; // Circular mode enabled
	DMA1_Channel7->CCR |= DMA_CCR_PL; // Very high priority
}

void start_dma1(void) {
	DMA1_Channel2->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel2->CPAR = (uint32_t)&GPIOB->BSRR; // We're going to set the BSRR address to start the ws2821 signal for the bit
	DMA1_Channel2->CMAR = (uint32_t)&ws2812_gpio_set_bits; // This is the source. Should be just an 0x1
	
	DMA1_Channel2->CCR |= DMA_CCR_EN;
	TIM2->DIER |= TIM_DIER_UDE; // Enable TIM 2 update
}

void start_dma2(uint16_t* buffer) {
	DMA1_Channel5->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel5->CPAR = (uint32_t)&GPIOB->BRR; // We're going to set the BSRR address to start the ws2821 signal for the bit
	DMA1_Channel5->CMAR = (uint32_t)buffer; // This is the source. Should be just an 0x1
	
	DMA1_Channel5->CCR |= DMA_CCR_EN;
	TIM2->DIER |= TIM_DIER_CC1DE; // Enable TIM Channel 1 update
}

void start_dma3(void) {
	DMA1_Channel7->CNDTR = DMA_BUFFER_SIZE; // Set the buffer size
	DMA1_Channel7->CPAR = (uint32_t)&GPIOB->BRR; // We're going to set the BRR address to finish the signal for a 1 bit
	DMA1_Channel7->CMAR = (uint32_t)&ws2812_gpio_set_bits; // This is the source. Should be just an 0x1
	
	DMA1_Channel7->CCR |= DMA_CCR_EN;
	TIM2->DIER |= TIM_DIER_CC2DE; // Enable TIM Channel 2 update
}

void stop_all_dma_channels(void) {
	TIM2->DIER &= ~TIM_DIER_CC2DE;
	TIM2->DIER &= ~TIM_DIER_CC1DE;
	TIM2->DIER &= ~TIM_DIER_UDE;
}

bool isTransferComplete() {
	return !((DMA1->ISR & (DMA_ISR_TCIF5 | DMA_ISR_HTIF5)) == 0);
}

bool isFullTransferComplete() {
	return (DMA1->ISR & DMA_ISR_TCIF5);
}

void clearDMAEventFlags() {
	DMA1->IFCR = (DMA_IFCR_CTCIF5 | DMA_IFCR_CHTIF5);
}