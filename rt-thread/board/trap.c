#include <rthw.h>
#include <rtthread.h>
#include "riscv-ops.h"
#include "rt_hw_stack_frame.h"
#include "riscv-plic.h"
#include "tick.h"
#include "encoding.h"

#define ISR_NUMBER    32
extern struct rt_irq_desc irq_desc[];

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

void handle_trap(rt_uint32_t mcause, rt_uint32_t mepc, struct rt_hw_stack_frame *sp)
{
    if (mcause == 0x80000007)
    {
        /* M mode timer isr */
        clint_m_timer_irq_handle(mepc);
    }
    else if (mcause == 0x8000000B)
    {
        /* extern isr */
        int irq = __plic_irq_claim();
        __plic_irq_complete(irq);
        if (irq_desc[irq].handler)
            irq_desc[irq].handler(irq, irq_desc[irq].param);
    }
    else if (mcause == 0x80000003)
    {
        /* M mode soft isr */
        clint_m_soft_irq_handle(mepc);
    }
    else
    {
        /* exception */
        rt_backtrace();
        while(1);
    }
}