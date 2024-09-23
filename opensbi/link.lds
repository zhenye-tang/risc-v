MEMORY
{
    RAM (rwx) : ORIGIN = 0x80200000, LENGTH = 128*1024*1024
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

    . = ALIGN(4);
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
}
