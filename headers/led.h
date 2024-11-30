#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

enum {LED_OFF, LED_YELLOW, LED_BLUE};

void led_toggle();

void led_init();

void led_g_on();

void led_g_off();

void led_state(uint8_t state);
#endif
