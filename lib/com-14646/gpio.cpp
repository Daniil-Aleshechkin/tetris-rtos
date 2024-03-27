#include "gpio.h"
#include <stm32f103xb.h>

void init_gpio() {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
	GPIOB->CRL |= GPIO_CRL_MODE0; // R1
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
	GPIOB->CRL |= GPIO_CRL_MODE1; // G1
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	GPIOB->CRL |= GPIO_CRL_MODE2; // B1
	
	GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
	GPIOB->CRL |= GPIO_CRL_MODE6; // R2
	
	GPIOB->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
	GPIOB->CRH |= GPIO_CRH_MODE8; // B2
	
	GPIOB->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
	GPIOB->CRH |= GPIO_CRH_MODE9; // G2
	
	GPIOC->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
	GPIOC->CRL |= GPIO_CRL_MODE5; // A
	
	GPIOC->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
	GPIOC->CRL |= GPIO_CRL_MODE6; // B
	
	GPIOC->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	GPIOC->CRL |= GPIO_CRL_MODE2; // C
	
	GPIOC->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
	GPIOC->CRL |= GPIO_CRL_MODE3; // D
	
	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
	GPIOA->CRL |= GPIO_CRL_MODE0; // CLK
	
	GPIOA->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
	GPIOA->CRL |= GPIO_CRL_MODE1; // LAT
	
	GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
	GPIOA->CRH |= GPIO_CRH_MODE9; // OE
}

void flip_clock() {
	
		//GPIOA->ODR |= GPIO_ODR_ODR0;
		//GPIOA->ODR &= ~GPIO_ODR_ODR0;
	GPIOA->BSRR = GPIO_BSRR_BS0;
	GPIOA->BRR = GPIO_BRR_BR0;
}
void flip_latch() {
	GPIOA->BSRR = GPIO_BSRR_BS1;
	GPIOA->BRR = GPIO_BRR_BR1;
	
	//GPIOA->ODR |= GPIO_ODR_ODR1;
	
	//GPIOA->ODR &= ~GPIO_ODR_ODR1;
}

void output_rgb_data(struct rgb_data out) {
	GPIOB->BSRR = (out.r1 ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0) | 
	(out.g1 ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1) | 
	(out.b1 ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2) | 
	(out.r2 ? GPIO_BSRR_BS6 : GPIO_BSRR_BR6) |
	(out.b2 ? GPIO_BSRR_BS9 : GPIO_BSRR_BR9);
	
	GPIOB->BSRR = (out.g2 ? GPIO_BSRR_BS8 : GPIO_BSRR_BR8);
}

void multiplex(uint8_t val) {
	bool a = (val & 0x1) == 0x1;
	bool c = (val & 0x2) == 0x2;
	bool d = (val & 0x4) == 0x4;
	bool b = (val & 0x8) == 0x8;
	
	GPIOC->BSRR = (a ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5)|
	(b ? GPIO_BSRR_BS6 : GPIO_BSRR_BR6) |
		(c ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2) |
	(d ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3);

}

void enable_output() {
	GPIOA->BRR = GPIO_BRR_BR9;
}
void disable_output() {
	GPIOA->BSRR = GPIO_BSRR_BS9;
}
