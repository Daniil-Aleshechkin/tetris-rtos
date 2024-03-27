#include <stm32f103xb.h>
#include "tim2.h"

void init_tim2() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 0x0;
	TIM2->ARR = 10000;
	
	/* CR1 CONFIGS */
	TIM2->CR1 &= ~TIM_CR1_CKD; // No clock division
	TIM2->CR1 &= ~TIM_CR1_ARPE; // Auto-reload preload disabled
	TIM2->CR1 &= ~TIM_CR1_CMS; // Center aligned mode
	TIM2->CR1 &= ~TIM_CR1_DIR; // Up counter
	TIM2->CR1 &= ~TIM_CR1_OPM; // One pulse mode disabled
	
	/* CR2 CONFIGS */
	TIM2->CR2 &= ~TIM_CR2_MMS; // Reset mms mode 
	
	/* SMCR CONFIGS */
	TIM2->SMCR &= ~TIM_SMCR_MSM; // No Master mode
	TIM2->SMCR &= ~TIM_SMCR_ETP; // No external clocks
	TIM2->SMCR &= ~TIM_SMCR_ECE; 
	TIM2->SMCR &= ~TIM_SMCR_ETPS; 
	TIM2->SMCR &= ~TIM_SMCR_ETF; 
	TIM2->SMCR &= ~TIM_SMCR_SMS; // No Slave mode
	
}

void start_tim2(void) {
	TIM2->CR1 |= TIM_CR1_CEN;
	
	//while (!(TIM2->SR & TIM_SR_UIF));
}

void stop_tim2(void) {
	TIM2->CR1 &= ~TIM_CR1_CEN;
	TIM2->SR &= ~TIM_SR_UIF;
}

bool isTim2Updated() {
	return !((TIM2->SR & TIM_SR_UIF) == 0);
}