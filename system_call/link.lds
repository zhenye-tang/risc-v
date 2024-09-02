MEMORY
{
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128*1024*1024
}

ENTRY(_start)

SECTIONS
{
    .text :
    {
        KEEP(*(.text._start))
        *(.text)
        *(.text.*)
    } > RAM

    .rodata   : { *(.rodata) *(.rodata.*) } > RAM

    . = ALIGN(4);
    .data :
    {
        *(.data)
        *(.data.*)
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