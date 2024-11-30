#ifndef __INIT_H__
#define __INIT_H__

#include <stdint.h>

extern uint32_t _isr_vector_size, _text_size, _data_size;
extern char _sdata, _data_lma;
extern char _stext, _text_lma;
extern char _sisr_vector, _isr_vector_lma;
extern char _bstart, _bend;

__attribute__((section(".boot")))void init_bss();

__attribute__((section(".boot")))void init_isr_vector();

__attribute__((section(".boot")))void init_data();

__attribute__((section(".boot")))void init_text();





#endif
