#include "../headers/led.h"
#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"


void led_init(){
	// Enabling IO ports B and C clocks 
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN_Msk | RCC_AHB2ENR_GPIOCEN_Msk);

	// Seting PB14 to output mode (0 1)
	GPIOB->MODER &= ~GPIO_MODER_MODE14_1; 

	// Sets green led to off
	GPIOB->BSRR = GPIO_BSRR_BR14_Msk ;

	// Setting PC to input mode -> both leds off
	GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk;
}

void led_state(uint8_t state){
	switch(state){
		case LED_OFF:
			// PC9 input mode -> turns off both blue and yellow
			GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk;

			led_g_on();

			break;

		case LED_YELLOW:
			// PC9 output mode
			GPIOC->MODER |= GPIO_MODER_MODE9_0;

			// Setting PC9
			GPIOC->BSRR = GPIO_BSRR_BS9_Msk;

			led_g_off();

			break;
		case LED_BLUE:
			// PC9 output mode
			GPIOC->MODER |= GPIO_MODER_MODE9_0;

			// Resetting PC9
			GPIOC->BSRR = GPIO_BSRR_BR9_Msk;

			led_g_off();
			break;
	}
}

void led_g_on(){
	// Setting PB14
	GPIOB->BSRR = GPIO_BSRR_BS14_Msk;
	GPIOB->BSRR = 0;
}

void led_g_off(){
	// Reseting BP14
	GPIOB->BSRR = GPIO_BSRR_BR14_Msk;
	GPIOB->BSRR = 0;

}

void led_toggle(){
	// Tests if the led is on
	if(GPIOB->IDR & GPIO_IDR_ID14){
		led_g_off();
	} else {
		led_g_on();	
	}

}
