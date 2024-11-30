#ifndef __MATRIX_H__
#define __MATRIX_H__

#include<stdint.h>
#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h" 

#define MATRIX_ROWS 8
#define MATRIX_COLUMNS 8

typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

// Macros
#define RST(x) ((x) ? (GPIOC->BSRR = GPIO_BSRR_BS3_Msk) : (GPIOC->BSRR = GPIO_BSRR_BR3_Msk)) 
#define LAT(x) ((x) ? (GPIOC->BSRR = GPIO_BSRR_BS4_Msk) : (GPIOC->BSRR = GPIO_BSRR_BR4_Msk)) 
#define SB(x) ((x) ? (GPIOC->BSRR = GPIO_BSRR_BS5_Msk) : (GPIOC->BSRR = GPIO_BSRR_BR5_Msk)) 

#define SCK(x) ((x) ? (GPIOB->BSRR = GPIO_BSRR_BS1_Msk) : (GPIOB->BSRR = GPIO_BSRR_BR1_Msk)) 
#define SDA(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS4_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR4_Msk)) 

#define ROW0(x) ((x) ? (GPIOB->BSRR = GPIO_BSRR_BS2_Msk) : (GPIOB->BSRR = GPIO_BSRR_BR2_Msk)) 
#define ROW1(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS15_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR15_Msk)) 
#define ROW2(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS2_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR2_Msk)) 
#define ROW3(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS7_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR7_Msk)) 
#define ROW4(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS6_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR6_Msk)) 
#define ROW5(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS5_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR5_Msk)) 
#define ROW6(x) ((x) ? (GPIOB->BSRR = GPIO_BSRR_BS0_Msk) : (GPIOB->BSRR = GPIO_BSRR_BR0_Msk)) 
#define ROW7(x) ((x) ? (GPIOA->BSRR = GPIO_BSRR_BS3_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR3_Msk)) 

// A clock pulse consists of 
// Set to 0, wait, set to 1, wait, set to 0, wait
static inline void pulse_SCK(){
	SCK(0);
	for(int i = 0; i < 2; i++)
		asm volatile ("nop");
	SCK(1);
	for(int i = 0; i < 2; i++)
		asm volatile ("nop");
	SCK(0);
	for(int i = 0; i < 2; i++)
		asm volatile ("nop");
}

// A LAT pulse consists of 
// Set to 1, wait, set to 0, wait, set to 1, wait
static inline void pulse_LAT(){
	LAT(1);
	for(int i = 0; i < 2; i++)
		asm volatile ("nop");
	LAT(0);
	asm volatile ("nop");
	LAT(1);
	asm volatile ("nop");
}

// Basic initialization settings for the matrix
void matrix_init();

// Function to deactivate all rows
void deactivate_rows();

// Function to activate a certain row
void activate_row(int row);

// Sends 8 bits in big-endian
void send_byte(uint8_t val);

// Receives a 8-pixel table and sends the RGB values of each one, from 7 to 0, and activates the rows
// Sends 24 bytes in total
void mat_set_row(int row, volatile rgb_color *val);

// Sets all bank 0 bits to 0 and calls matrix init
void init_bank0();

// Print infinitely the matrix
void display_matrix();







#endif
