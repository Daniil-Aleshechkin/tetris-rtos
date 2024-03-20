#include "stdint.h"

#ifndef WS2821_DISPLAY
#define WS2821_DISPLAY

#define DISPLAY_WIDTH 8
#define DISPLAY_HEIGHT 8

struct pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

void bufferPixel(struct pixel, int x, int y);

void refreshDisplay(void);

void displayInit(void);

void clearBuffer(void);

#endif