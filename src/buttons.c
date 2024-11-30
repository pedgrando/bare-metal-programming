#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "../CMSIS/Include/core_cm4.h"
#include "../headers/led.h"


void button_init(){
	// Enable clock in Port C
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	// PC13 to input mode
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;

	// Set PC13 as source for EXTI13
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;	

	// Sets on EXTI13 interrupt mask
	EXTI->IMR1 |= EXTI_IMR1_IM13_Msk;

	// Set rising and falling triggers (make it toggle -> swithc between on and off when pressed) 
	EXTI->RTSR1 |= EXTI_RTSR1_RT13_Msk;
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT13_Msk;

	// Enable the interrupt EXTI13
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
}

// Treatment for "Blue Button Press" exception/ EXTI13
void EXTI15_10_IRQHandler(void){
	// Checks if there are pending interruptions
	if(EXTI->PR1 & EXTI_PR1_PIF13){
		// Clears the pending interruption
		EXTI->PR1 |= EXTI_PR1_PIF13;
		led_toggle();	
	}
		
}
