#include "../headers/uart.h"
#include "../headers/matrix.h"
#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
#include "../CMSIS/Include/core_cm4.h"


void uart_init(int baudrate){
	// Init PORTB clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk;

	// Making PB6 USART1 TX and PB7 USART1 RX
	GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE6_Msk)) | GPIO_MODER_MODE6_1;
	GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODE7_Msk)) | GPIO_MODER_MODE7_1;

	// Sets AFRL7 and AFRL6 to AF7 mode
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_3) |(GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_2); 
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_3) |(GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2); 
	
	// Init USART clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN_Msk; 

	// Set USART1 clock to PCLK -> set 2 first CCIPR bits to 0
	RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_Msk;

	// Reset USART1
	RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST_Msk;
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST_Msk;

	// Set USART1 speed to 'baudrate' bauds according to x = freq/(baud_rate)
	USART1->BRR = 80000000/baudrate;	

	// Setting UART mode to 8-N-1
	// 00 -> 8 bits, disables parity control, set oversampling to 16	
	USART1->CR1 = 0; 	

	USART1->CR2 &= ~USART_CR2_STOP_Msk; 			// 1 stop bit

	// Activate USART1, TX and RX
	USART1->CR1 |= USART_CR1_UE_Msk;
	USART1->CR1 |= USART_CR1_RE_Msk;
	USART1->CR1 |= USART_CR1_TE_Msk;

	// Activate Handler - Activate the specific reading interruptions inside the CR1
	USART1->CR1 |= USART_CR1_RXNEIE_Msk;
	// Activate Global USART1 interruptions and
	NVIC_EnableIRQ(USART1_IRQn);

}

void uart_putchar(uint8_t c){
	// Checks if the TX is free
	while(!(USART1->ISR & USART_ISR_TXE_Msk));

	// Sending the char
	USART1->TDR = (uint16_t) c;
}

uint8_t uart_getchar(){
	char c;

	// Checks if the RX has received a byte
	while(!(USART1->ISR & USART_ISR_RXNE_Msk));

	// Reads the char
	c = USART1->RDR;

	return c;
}

void uart_puts(const char *s){
	const char *string = s;

	while(*string != '\0'){
		uart_putchar(*(string++));
	}

	// Waits for a signal of end of transmission
	while(!(USART1->ISR & USART_ISR_TC));
}

void uart_gets(char *s, size_t size){
	char *str = s;

	// Reads size chars and puts them into a '\0'-char-ended string 
	for(size_t i = 0; i < size; i++){
		*str = (uint8_t) uart_getchar();	

		if(*(str++) == '\r') break;	

	}	
	*str = '\0';
}

// Handler receives a char, checks if it is a 0xFF, and if it is, it starts to read a
// frame of 192 bytes. For the UART Handler we just need to treat it (there are no 
// registers that must be set, etc.)
void USART1_IRQHandler(void){
	extern volatile rgb_color matrix[MATRIX_ROWS][MATRIX_COLUMNS];
	volatile uint8_t *linear_matrix = (uint8_t *)matrix;

	static uint8_t reading = 0;
	static uint8_t read_bytes = 0;

	uint8_t aux_char = uart_getchar();	

	// Error handling -> cut communicating if has an error
	if(USART1->ISR & (USART_ISR_ORE | USART_ISR_FE)){
		USART1->ISR = (USART1->ISR & ~USART_ISR_ORE) & ~USART_ISR_FE;	
		reading = 0;
		return;
	}

	// If receive a 0xFF -> start reading
	if(aux_char == 0xFF){
		reading = 1;
		read_bytes = 0;
	} else if(reading == 1){
		// We're in the middle of a reading
		// Reads until read_bytes == 192
		linear_matrix[read_bytes] = aux_char;
		read_bytes++;

		if(read_bytes == MATRIX_ROWS*MATRIX_COLUMNS*3){
			reading = 0;
		}	
	}
}



