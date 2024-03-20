#include "tim2.h"
#include <stm32f103xb.h>


#define TIMER2_FREQ_HZ          72000000
#define WS2812_TIMER_PERIOD        (((TIMER2_FREQ_HZ / 1000) * 125) / 100000)
#define WS2812_TIMER_PWM_CH1_TIME  (((TIMER2_FREQ_HZ / 1000) *  40) / 100000)
#define WS2812_TIMER_PWM_CH2_TIME  (((TIMER2_FREQ_HZ / 1000) *  80) / 100000)

void config_tim2(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 0x0;
	TIM2->ARR = WS2812_TIMER_PERIOD;
	
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
	
	/* TIM2 Channel 1 configs */
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M; // Set the Tim2 channel 1 to PWM 1 output compare mode
	TIM2->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC2M_1);
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1FE; // Disable OC fast mode
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE; // Set Preload enable
	
	TIM2->CCER &= ~TIM_CCER_CC1P; // High polarity
	TIM2->CCER |= TIM_CCER_CC1E;
	
	TIM2->CCR2 = WS2812_TIMER_PWM_CH1_TIME;
	
	/* TIM2 Channel 1 configs */
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2M; // Set the Tim2 channel 2 to PWM 1 output compare mode
	TIM2->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	TIM2->CCMR1 &= ~TIM_CCMR1_OC2FE; // Disable OC fast mode
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE; // Set Preload enable
	
	TIM2->CCER &= ~TIM_CCER_CC2P; // High polarity
	TIM2->CCER |= TIM_CCER_CC2E;
	
	TIM2->CCR2 = WS2812_TIMER_PWM_CH2_TIME;
}

void start_tim2(void) {
	TIM2->CR1 |= TIM_CR1_CEN;
	
	while (!(TIM2->SR & TIM_SR_UIF));
}

void stop_tim2(void) {
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

void preOverflowTim2() {
	TIM2->CNT = TIM2->ARR - 10;
}

bool isTim2Updated() {
	return !((TIM2->SR & TIM_SR_UIF) == 0);
}

void resetTime2Update() {
	TIM2->SR &= ~TIM_SR_UIF;
}
