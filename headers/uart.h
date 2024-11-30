#ifndef __UART_H__
#define __UART_H__

#include<stdint.h>
#include<stddef.h>

void uart_init(int baudrate);

void uart_putchar(uint8_t c);

uint8_t uart_getchar();

void uart_puts(const char *s);

void uart_gets(char *s, size_t size);

#endif
