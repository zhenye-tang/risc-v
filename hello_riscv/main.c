#include "uart.h"
#include <stdint.h>
#include "irq.h"
#include "mtime.h"
#include "clint.h"

int main(void)
{
    interrupt_init();
    uart_init();
    mtime_init();
    clint_ipi_init();
    clint_ipi_enable();
    uart_printf("hello risc-v.\n");
    while(1)
    {
        mtime_mdelay(1000);
        uart_printf("current tick = %d.\n", (uint32_t)mtime_read());
        clint_ipi_send(0);
    }

    return 0;
}