MEMORY
{
    ROM (rx) : ORIGIN = 0x80000000, LENGTH = 0x200000
    RAM (rwx) : ORIGIN = 0x80200000, LENGTH = 0x1000000
}

__STACKSIZE__ = 16384;

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

        PROVIDE(__ctors_start__ = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE(__ctors_end__ = .);
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

    .stack : ALIGN(64)
    {
        __stack_start__ = .;

        . += __STACKSIZE__;
        __stack_cpu0 = .;

        . += __STACKSIZE__;
        __stack_cpu1 = .;
    } > RAM

    PROVIDE(_memory_start = ORIGIN(RAM));
	PROVIDE(_memory_end = ORIGIN(RAM) + LENGTH(RAM));

    PROVIDE(_heap_start = _sstack);
	PROVIDE(_heap_size = _memory_end - _heap_start);
}