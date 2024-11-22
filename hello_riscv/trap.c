#include <stdint.h>
#include "clint.h"
#include "plic.h"
#include "stack.h"
#include "irq.h"
#include "mtime.h"
#include "uart.h"

extern struct irq_desc irq_desc[];

void handle_trap(unsigned long mcause, struct rv_stack_frame *sp)
{
    if (mcause == 0x80000007)
    {
        /* M mode timer isr */
        mtime_isr();
    }
    else if (mcause == 0x8000000B)
    {
        /* extern isr */
        int irq = plic_claim();
        plic_complete(irq);
        if (irq_desc[irq].handler)
            irq_desc[irq].handler(irq, irq_desc[irq].param);
    }
    else if (mcause == 0x80000003)
    {
        /* M mode soft isr */
        uart_printf("soft isr.\n");
        clint_ipi_clear(0);
    }
    else
    {
        /* exception */
        while(1);
    }

}
