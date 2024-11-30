#include "../headers/clocks.h"
#include "../headers/matrix.h"
#include "../headers/uart.h"
#include "../headers/led.h"
#include "../headers/timer.h"
#include "../headers/irq.h"

#define FREQUENCY 60

int main (int argc, char *argv[]){
	clocks_init();

	led_init();

	matrix_init();

	irq_init();

	uart_init(38400);

	// Start timer with the correct period
	timer_init(1000000/FREQUENCY);

	while(1);

	return 0;
}
