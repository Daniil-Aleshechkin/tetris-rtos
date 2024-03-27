#include "stdbool.h"
#include "stdint.h"

#ifndef GPIO_COM
#define GPIO_COM

struct rgb_data {
	bool r1;
	bool r2;
	bool g1;
	bool g2;
	bool b1;
	bool b2;
};

void init_gpio();

void flip_clock();
void flip_latch();

void output_rgb_data(struct rgb_data out);

void multiplex(uint8_t val);

void enable_output();
void disable_output();

#endif
