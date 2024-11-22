#include <stdint.h>
#include "stack.h"
#include "uart.h"

unsigned long handle_trap(unsigned long mcause, unsigned long mepc, struct rv_stack_frame *ctx)
{
    if (mcause == 0x80000007)
    {

    }
    else if (mcause == 0x8000000B)
    {
        /* extern isr */
    }
    else if (mcause == 0x80000003)
    {
        /* M mode soft isr */
    }
    else if (mcause == 0x8)
    {
        // mcause == 8, user mode system call
        // mcause == 9, supervisor mode system call
        // mcause == 11, machine mode system call
        mepc += 4;

        if (ctx->a7 == 1)
        {
            /* putchar */
            uart_putc(ctx->a0);
        }
        else if(ctx->a7 == 4)
        {
            __asm__ volatile ("csrr %0, mhartid" : "=r" (ctx->a0));
        }
    }


    return mepc;
}
