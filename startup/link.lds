MEMORY
{
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x18800000
}

SECTIONS
{
    .text :
    {
        *(_start)
        *(.text)
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
}