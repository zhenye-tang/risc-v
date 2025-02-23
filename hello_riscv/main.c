#include "uart.h"
#include <stdint.h>
#include "irq.h"
#include "clint.h"

static int clint_timer_cb(void *user_data)
{
    clint_ipi_send(1);
    return 0;
}

static int clint_ipi_cb(void *user_data)
{
    uart_printf(user_data);
    return 0;
}

extern int cpp_test();
extern void cplusplus_init(void);

int main(void)
{
    interrupt_init();
    cplusplus_init();
    cpp_test();
    uart_init();
    uart_printf("hello risc-v.\n");
    clint_timer_init();
    clint_timer_start(1000, 0);
    clint_timer_register(clint_timer_cb, NULL);
    clint_ipi_init();
    clint_ipi_enable();
    clint_ipi_register(clint_ipi_cb, "core0 soft isr.\n");
    void secondary_cpu_weakup(void);
    secondary_cpu_weakup();
    while(1);
    return 0;
}