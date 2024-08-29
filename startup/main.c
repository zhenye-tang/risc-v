#include "uart.h"
#include <stdint.h>
#include "irq.h"
#include "mtime.h"
#include "spin_lock.h"

static spinlock_t lock;

int main(void)
{
    interrupt_init();
    uart_init();
    mtime_init();
    uart_printf("hello risc-v.\n");
    spin_lock(&lock);
    while(1)
    {
        mtime_mdelay(1000);
        uart_printf("current tick = %d.\n", (uint32_t)mtime_read());
    }

    return 0;
}