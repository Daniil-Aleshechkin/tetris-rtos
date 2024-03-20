#include "stdbool.h"

#ifndef TIM2_ws2812
#define TIM2_ws2812

void config_tim2(void);
void start_tim2(void);
void stop_tim2(void);
void preOverflowTim2();

bool isTim2Updated();

void resetTime2Update();
#endif
