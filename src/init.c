#include "../headers/memfuncs.h"
#include "../headers/init.h"

/* ----------------------------------- Init functions ---------------------------------
 * 	These are the boot functions, that copy the ROM sections to their respective RAM
 * 	positions defined in the linker script. The _s(name of the section) addresses
 * 	are the RAM addresses and the _(name of the section)_lma are the ROM addresses
 *  	from where they ought to be copied. Also, they are put in a separeted region from
 *  	text, so that it is possible to separate the code that needs to be copied from the
 *  	bootloader code.
 * ------------------------------------------------------------------------------------
 */

__attribute__((section(".boot")))void init_bss(){
	char *bss = &_bstart;

	for(; bss < &_bend; bss++){
		*bss = 0;
	}	
}

__attribute__((section(".boot")))void init_isr_vector(){
	memcpy(&_sisr_vector, &_isr_vector_lma, (uint32_t) &_isr_vector_size);
}

__attribute__((section(".boot")))void init_data(){
	memcpy(&_sdata, &_data_lma, (uint32_t) &_data_size);
}

__attribute__((section(".boot")))void init_text(){
	memcpy(&_stext, &_text_lma, (uint32_t) &_text_size);
}



