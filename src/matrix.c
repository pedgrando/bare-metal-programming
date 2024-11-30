#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "../headers/matrix.h"

volatile rgb_color matrix[MATRIX_ROWS][MATRIX_COLUMNS];

void matrix_init(){
	// Init ports A, B and C clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN_Msk | RCC_AHB2ENR_GPIOBEN_Msk | RCC_AHB2ENR_GPIOCEN_Msk;

	// Setting A2, A3, A4, A5, A6, A7, A15 to output mode
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) | GPIO_MODER_MODE2_0;  
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_Msk) | GPIO_MODER_MODE3_0;  
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_Msk) | GPIO_MODER_MODE4_0;  
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_Msk) | GPIO_MODER_MODE5_0;  
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODE6_0;  
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODE7_0;  
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) | GPIO_MODER_MODE15_0;  

	// Setting B0, B1, B2 to output mode
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk) | GPIO_MODER_MODE0_0;  
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_Msk) | GPIO_MODER_MODE1_0;  
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_Msk) | GPIO_MODER_MODE2_0;  

	// Setting C3, C4, C5 to output mode
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_Msk) | GPIO_MODER_MODE3_0;  
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4_Msk) | GPIO_MODER_MODE4_0;  
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5_Msk) | GPIO_MODER_MODE5_0;  


	// Setting ALL precedent pins to VERY HIGH SPEED -> 11
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_Msk;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7_Msk;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk;

	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk;

	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk;
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_Msk;
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_Msk;

	// Reset DM163
	RST(0);

	// Set LAT
	LAT(1);

	// Select BANK1
	SB(1);

	// Reset SCK and SDA
	SCK(0);
	SDA(0);
	
	// Reset C0 to C7 -> turn off all rows
	deactivate_rows();

	// 150 ms delay
	for(int i = 0; i < 12000000; i++)
		asm volatile ("nop");

	// Turns off the reset -> allows matrix to work
	RST(1);

	// Fills all the BANK0 registers with 1
	init_bank0();

	// Reselects the BANK1
	SB(1);
}

// Function to deactivate all rows
void deactivate_rows(){
	ROW0(0);
	ROW1(0);
	ROW2(0);
	ROW3(0);
	ROW4(0);
	ROW5(0);
	ROW6(0);
	ROW7(0);
}

// Function to activate a certain row
void activate_row(int row){
	switch(row){
		case 0:
			ROW0(1);
			break;
		case 1:
			ROW1(1);
			break;
		case 2:
			ROW2(1);
			break;
		case 3:
			ROW3(1);
			break;
		case 4:
			ROW4(1);
			break;
		case 5:
			ROW5(1);
			break;
		case 6:
			ROW6(1);
			break;
		case 7:
			ROW7(1);
			break;
		default:
			break;
	
	}
}

// Sends a byte according to the protocol stablished
// Puts a bit in SDA, then sends a clock pulse to update; repeat until send the whole byte
void send_byte(uint8_t val){
	for(int i = 7; i >= 0; i--){
		SDA((val >> i) & 1);	
		pulse_SCK();
	}	

}

// Receives a 8-pixel table and sends the RGB values of each one, from 7 to 0, and activates the rows
// Sends 24 bytes in total
void mat_set_row(int row, volatile rgb_color *val){
	// For each pixel, sends data B G R data, respectively
	// We begin from the last 
	for(int i = 7; i >= 0; i--){
		send_byte(val[i].b);
		send_byte(val[i].g);
		send_byte(val[i].r);
	}
	
	// Activates the row relative to the send data
	activate_row(row);
	// Pulse LAT to finish the data transfert
	pulse_LAT();
}

// Initializes the bank 0 to all '1's
void init_bank0(){
	// Selects bank zero
	SB(0);
	// Sends 6 * 24 bits of data
	for(int j = 0; j < 144; j ++){
		// Send 1
		SDA(1);	
		// Pulse clock to send
		pulse_SCK();
	}
	
	// Pulse lat to open outputs and finish the transfert of all 24 bytes
	pulse_LAT();

}

// A function that indefinitively display the matrix defined in this file, that can be
// modified by other files
void display_matrix(){
	for(int i = 0; i < 8; i++){
		mat_set_row(i, matrix[i]);
		for(int j = 0; j < 20000; j++)
			asm volatile ("nop");
		deactivate_rows();
	}
}












