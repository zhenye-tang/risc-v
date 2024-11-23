#include <stdint.h>
#include "clint.h"
#include "plic.h"
#include "stack.h"
#include "irq.h"
#include "uart.h"
#include "clint.h"

extern struct irq_desc irq_desc[];

void handle_trap(unsigned long mcause, struct rv_stack_frame *sp)
{
    if (mcause == 0x80000007)
    {
        extern uintptr_t clint_m_timer_irq_handle(uintptr_t mepc);
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
        extern uintptr_t clint_m_soft_irq_handle(uintptr_t mepc);
        clint_m_soft_irq_handle(0);
    }
    else
    {
        /* exception */
        while(1);
    }

}
