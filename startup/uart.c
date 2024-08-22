#include <stdint.h>

// QEMU virt board UART0 base address for RISC-V
#define UART0_BASE 0x10000000L

// UART0寄存器映射
volatile uint32_t* const UART0 = (uint32_t*)UART0_BASE;

void uart_putc(char c)
{
    *UART0 = c;
}

void uart_puts(const char* str)
{
    while (*str)
    {
        uart_putc(*str++);
    }
}

