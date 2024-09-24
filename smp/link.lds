MEMORY
{
    ROM (rx) : ORIGIN = 0x80000000, LENGTH = 512K
    RAM (rwx) : ORIGIN = 0x80080000, LENGTH = 512K
}

ENTRY(_start)

SECTIONS
{
    .text :
    {
        KEEP(*(.text._start))
        *(.text)
        *(.text.*)
    } > ROM

    .rodata   : { *(.rodata) *(.rodata.*) } > ROM

    .data.lma :
    {
        /* This is used by the startup in order to initialize the .data secion */
        _sidata = .;
    } > ROM

    . = ALIGN(4);
    .data : AT (_sidata)
    {
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;
        *(.data)
        *(.data.*)
        *(.sdata .sdata.*)
        . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
		_edata = .;
    } > RAM

    . = ALIGN(4);
    __bss_start = .;
    .bss (NOLOAD):
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
    } > RAM
    __bss_end = .;

    .stack : ALIGN(4K)
    {
        _estack = .;
        . += 128K;
        _sstack = .;
    }

    PROVIDE(_memory_start = ORIGIN(RAM));
	PROVIDE(_memory_end = ORIGIN(RAM) + LENGTH(RAM));

    PROVIDE(_heap_start = _sstack);
	PROVIDE(_heap_size = _memory_end - _heap_start);
}