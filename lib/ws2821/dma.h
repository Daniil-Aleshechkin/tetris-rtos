#include "stdint.h"
#include "stdbool.h"

#ifndef DMA_ws2821
#define DMA_ws2821

#define DMA_BUFFER_SIZE 16

void config_DMA(void);

void config_DMA1(void);
void config_DMA2(void);
void config_DMA3(void);

void start_dma1(void);
void start_dma2(uint16_t* buffer);
void start_dma3(void);

void stop_all_dma_channels(void);

void clearDMAEventFlags(void);
bool isFullTransferComplete(void);
bool isTransferComplete(void);

#endif