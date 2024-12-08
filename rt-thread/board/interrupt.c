
#include <rthw.h>
#include <rtthread.h>
#include "encoding.h"
#include "riscv-plic.h"
#include "clint.h"

#define ISR_NUMBER    32
struct rt_irq_desc irq_desc[ISR_NUMBER];

int rt_hw_clint_ipi_enable(void)
{
    clint_ipi_enable();
    return 0;
}

int rt_hw_clint_ipi_disable(void)
{
    clint_ipi_disable();
    return 0;
}

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t mcause)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", mcause);
    return RT_NULL;
}

void rt_hw_scondary_interrupt_init()
{
    __plic_set_threshold(0);
    // asm volatile("csrs mie, %0" : : "r"(1 << 11));
    /* Enable machine external interrupts. */
    set_csr(mie, MIP_MEIP);
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
    set_csr(mie, MIP_MEIP);
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


