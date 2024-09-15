#include "rtthread.h"
#include <stdio.h>
#include <stdint.h>
#include "rtconfig.h"

static void thread_entry(void *prma)
{
    float a, b;
    a = 3.1415926;
    b = 5.678;
    while (1)
    {
        rt_thread_mdelay(5000);
        rt_kprintf("Hello risc-v!! %f\n", a+b);
    }
}

int main(void)
{
    rt_kprintf("Hello risc-v!!\n");
    rt_thread_t thread = rt_thread_create("thread0", thread_entry, NULL, 2048, 10, 20);
    rt_thread_startup(thread);
    return 0;
}
