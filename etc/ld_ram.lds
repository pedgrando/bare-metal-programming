MEMORY
	{
		rom (rx) : ORIGIN = 0x08000000, LENGTH = 1M
		sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
		sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
	}

ENTRY (_start)

_sstack = ORIGIN(sram2) + LENGTH(sram2);

SECTIONS
	{
		.isr_vector : {
			_sisr_vector = .;
			KEEP(*(.isr_vector))
			_eisr_vector = .;
		} > sram1 AT> rom
		_isr_vector_lma = LOADADDR(.isr_vector);

		.text : {
                    	_stext = .;
                        *(.text)
                        _etext = .;
                } > sram1 AT> rom
		_text_lma = LOADADDR(.text);

		.rodata : {
			_srodata = .;
			*(.rodata)
			_erodata = .;
		} > rom

		.data : {
			_sdata = .;
			*(.data)
			_edata = .;
		} >sram1 AT> rom
		_data_lma = LOADADDR(.data);

		.bss : {
			_bstart = .;
			*(.bss)
			*(COMMON)
			_bend = .;
		} > sram1
		
		.boot : {
			*(.boot)
		} > rom
		
	}

_isr_vector_size = SIZEOF(.isr_vector);
_text_size = SIZEOF(.text);
_data_size = SIZEOF(.data);
_rodata_size = SIZEOF(.rodata);
_bss_size = SIZEOF(.bss);
