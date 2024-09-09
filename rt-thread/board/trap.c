#include <rthw.h>
#include <rtthread.h>
#include "riscv-ops.h"
#include "rt_hw_stack_frame.h"
#include "riscv-plic.h"
#include "tick.h"

#define ISR_NUMBER    32
static struct rt_irq_desc irq_desc[ISR_NUMBER];

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t mcause)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", mcause);
    return RT_NULL;
}

void rt_hw_interrupt_init(void)
{
    int idx = 0;

    for (idx = 0; idx < ISR_NUMBER; idx++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
    }
    __plic_set_threshold(0);
    asm volatile("csrs mie, %0" : : "r"(1 << 11));
}

void rt_hw_interrupt_umask(int vector)
{
    __plic_set_priority(vector, 1);
    __plic_irq_enable(vector);
}

void rt_hw_interrupt_mask(int vector)
{
    __plic_irq_disable(vector);
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;
    void *user_param = param;

    if(vector < ISR_NUMBER)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
        }
    }

    return old_handler;
}

void handle_trap(rt_uint32_t mcause, rt_uint32_t mepc, struct rt_hw_stack_frame *sp)
{
    if (mcause == 0x80000007)
    {
        /* M mode timer isr */
        rt_hw_tick_isr();
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
    }
    else
    {
        /* exception */
        rt_backtrace();
        while(1);
    }
}