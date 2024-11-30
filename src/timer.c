#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "../headers/led.h"
#include "../headers/matrix.h"

#define FREQ 80000000



void timer_init(int max_us){
	// Turn on the clock for TIM2
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN_Msk;	
	
	// Erase TIM2_SR flags and reset the counter (TIM2_CNT)
	TIM2->SR = 0;
	TIM2->CNT = 0;

	// Set the counting directions upward
	TIM2->CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);	
	
	// Value of the prescaler is set to divide the frequency by 80
	// (80 MHZ / 1 MHZ) - 1 = 79
	TIM2->PSC = 79; 

	// Set the counting limit to MAX_US
	TIM2->ARR = max_us;

	// Authorize the interruptions in UPDATE
	TIM2->DIER |= TIM_DIER_UIE;

	// Authorize global interruptions for TIM2
	NVIC_EnableIRQ(TIM2_IRQn);

	// Increases clock priority for it to be able to write the matrix
	NVIC_SetPriority(TIM2_IRQn, 1);

	// Enables counter
	TIM2->CR1 |= TIM_CR1_CEN;	


}

// Handler that prints the matrix every 1/60 seconds
void TIM2_IRQHandler(void){
	// Checks if an update interrupt has arrived
	if(TIM2->SR & TIM_SR_UIF){
		// Resets the interrupt bit
		TIM2->SR &= ~TIM_SR_UIF;
		
		// The handler functionallity itself	
		led_toggle();

		display_matrix();
	}
}
