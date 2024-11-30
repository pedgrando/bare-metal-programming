#ifndef __IRQ_H__
#define __IRQ_H__

#include "../CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"

extern unsigned char _sstack;
extern void _start(void);

#define MAKE_DEFAULT_HANDLER(handler) 		\
	void __attribute__((weak)) handler(void){ 	\
		__disable_irq();		\
		while(1); 			\
	}	

void irq_init(void);

#endif

