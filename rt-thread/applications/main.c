#include "rthw.h"
#include "rtthread.h"
#include <stdio.h>
#include <stdint.h>

static void thread_entry(void *prma)
{
    while (1)
    {
        rt_thread_mdelay(3000);
        rt_kprintf("Hello risc-v, I'm cpu_%d!!!\n", rt_hw_cpu_id());
    }
}

int main(void)
{
    rt_kprintf("Hello risc-v!!\n");
    rt_thread_t thread = rt_thread_create("thread0", thread_entry, NULL, 2048, 10, 20);
    rt_thread_startup(thread);
    thread = rt_thread_create("thread1", thread_entry, NULL, 2048, 11, 20);
    rt_thread_startup(thread);
    thread = rt_thread_create("thread2", thread_entry, NULL, 2048, 9, 20);
    rt_thread_startup(thread);
    return 0;
}
