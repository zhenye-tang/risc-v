MEMORY
{
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x18800000
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
        . += 8K;
        _sstack = .;
    }

    .stack0 (NOLOAD) : {
        _stack0_start = .;
        . = . + 4K;
        _stack0_end = .;
    } > RAM

    .stack1 (NOLOAD) : {
        _stack1_start = .;
        . = . + 4K;
        _stack1_end = .;
    } > RAM

    .stack2 (NOLOAD) : {
        _stack2_start = .;
        . = . + 4K;
        _stack2_end = .;
    } > RAM
}