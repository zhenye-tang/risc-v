#include <stdint.h>
#include "irq.h"
#include "plic.h"
#include <stddef.h>

#define MAX_HANDLERS 128

static struct irq_desc irq_desc[MAX_HANDLERS];

static void interrupt_handle_default(int vector, void *param)
{
    return;
}

void interrupt_init(void)
{
    for (int idx = 0; idx < MAX_HANDLERS; idx++)
    {
        irq_desc[idx].handler = interrupt_handle_default;
        irq_desc[idx].param = NULL;
    }
    plic_set_threshold(0);
    __enable_irq();
}

void interrupt_umask(int vector)
{
    plic_set_priority(vector, 1);
    plic_irq_enable(vector);
}

void interrupt_install(int vector, isr_handler_t handler, void *param)
{
    if (vector < MAX_HANDLERS)
    {
        irq_desc[vector].handler = handler;
        irq_desc[vector].param = param;
    }
}

void interrupt_uninstall(int vector, isr_handler_t handler, void *param)
{
    if (vector < MAX_HANDLERS)
    {
        irq_desc[vector].handler = interrupt_handle_default;
        irq_desc[vector].param = NULL;
        plic_irq_disable(vector);
    }
}
