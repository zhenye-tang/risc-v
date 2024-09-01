#ifndef __IRQ_H__
#define __IRQ_H__

#include <stdint.h>

typedef void (*isr_handler_t)(int vector, void *param);

struct irq_desc
{
    isr_handler_t handler;
    void            *param;
};

// mie: global interrupt enable 
__attribute__((always_inline)) static inline void __enable_irq(void)
{
    __asm volatile("csrs mstatus, 8");
}

__attribute__((always_inline)) static inline void __disable_irq(void)
{
    __asm volatile("csrc mstatus, 8");
}

void interrupt_init(void);
void interrupt_umask(int vector);
void interrupt_install(int vector, isr_handler_t handler, void *param);
void interrupt_uninstall(int vector, isr_handler_t handler, void *param);

#endif //__IRQ_H__