#include "gpio.h"

#include <stm32f103xb.h>

void config_gpio() {
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
		GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
		GPIOB->CRL |= GPIO_CRL_MODE0;
}

void resetLED() {
	GPIOB->BRR = GPIO_BRR_BR0;
}
