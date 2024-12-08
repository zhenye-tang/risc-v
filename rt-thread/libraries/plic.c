#include "plic.h"
#include <stdint.h>

#define MIE_MEIE        (1 << 11)  // meie 

void plic_set_priority(int irq, int priority)
{
    *(uint32_t *)PLIC_PRIORITY(irq) =  priority;
}

void plic_irq_enable(int irq)
{
    *(uint32_t *)PLIC_ENABLE_BASE(0, irq) |= (1 << (irq % 32));
    asm volatile("csrs mie, %0" : : "r"(MIE_MEIE));
}

void plic_irq_disable(int irq)
{
    *(uint32_t *)PLIC_ENABLE_BASE(0, irq) &= ~(1 << (irq % 32)); 
}

void plic_set_threshold(int threshold)
{
    *(uint32_t *)PLIC_THRESHOLD(0) = threshold;
}

int plic_claim(void)
{
    int irq = *(uint32_t *)PLIC_CLAIM(0);
    return irq;
}

void plic_complete(int irq)
{
    *(uint32_t *)PLIC_COMPLETE(0) = irq;
}
