#include "rthw.h"
#include "rtthread.h"
#include <stdio.h>
#include <stdint.h>
#include "system_call.h"

static int *p = NULL;

static void thread_entry(void *prma)
{
    while (1)
    {
        rt_thread_mdelay(3000);
        rt_kprintf("Hello risc-v, I'm cpu_%d, Privileged Mode = 0x%x!!!\n", system_gethart(), system_current_mode());
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
