#include "rtthread.h"
#include <stdio.h>
#include <stdint.h>
#include "rtconfig.h"

static void thread_entry(void *prma)
{
    while (1)
    {
        rt_thread_mdelay(5000);
        rt_kprintf("Hello risc-v!!\n");
    }
}

int main(void)
{
    rt_kprintf("Hello risc-v!!\n");
    rt_thread_t thread = rt_thread_create("thread0", thread_entry, NULL, 2048, 10, 20);
    rt_thread_startup(thread);
    return 0;
}
