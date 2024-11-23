#include <stdint.h>
#include "clint.h"
#include "plic.h"
#include "stack.h"
#include "irq.h"
#include "uart.h"

extern struct irq_desc irq_desc[];

uintptr_t __attribute__((weak))
handle_irq_dummy(uintptr_t mepc)
{
    while(1);
    return mepc;
}

uintptr_t __attribute__((weak, alias("handle_irq_dummy")))
clint_m_timer_irq_handle(uintptr_t mepc);

uintptr_t __attribute__((weak, alias("handle_irq_dummy")))
clint_m_soft_irq_handle(uintptr_t mepc);

void handle_trap(unsigned long mcause, struct rv_stack_frame *sp)
{
    if (mcause == 0x80000007)
    {
        clint_m_timer_irq_handle(0);
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
        clint_m_soft_irq_handle(0);
    }
    else
    {
        /* exception */
        while(1);
    }
}
