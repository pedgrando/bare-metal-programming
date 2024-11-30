.syntax unified
.thumb

.global _start
.extern _sstack

.section .boot, "ax", %progbits
.thumb_func
_start:
	ldr r0, =_sstack
	mov sp, r0

	bl init_text
	bl init_bss
	bl init_data 
	bl init_isr_vector

	b main

_end:
	b _end
