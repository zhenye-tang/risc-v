#include "mtime.h"

#define MTIMECMP_LOW                              ((volatile uint32_t*)0x02004000)
#define MTIMECMP_HIGHT                            ((volatile uint32_t*)0x02004004)
#define MTIME_LOW                                 ((volatile uint32_t*)0x0200BFF8)
#define MTIME_HIGHT                               ((volatile uint32_t*)0x0200BFFC)
#define MIE_MTIE                                  (1 << 7)

uint64_t mtime_read(void)
{
    uint32_t mtime_low = *MTIME_LOW;
    uint32_t mtime_hight = *MTIME_HIGHT;

    while (mtime_hight != *MTIME_HIGHT)
    {
        mtime_hight = *MTIME_HIGHT;
        mtime_low = *MTIME_LOW;
    }

    return ((uint64_t)mtime_hight << 32) | mtime_low;
}

void mtime_write(uint64_t tick)
{
    *MTIMECMP_LOW = tick & 0xffffffff;
    *MTIMECMP_HIGHT = (tick << 32) & 0xffffffff;
}

void mtime_mdelay(int ms)
{
    uint64_t current_time = mtime_read();
    uint64_t end_time = current_time + ms * (CPUTIME_TIMER_FREQ / TICK_PER_SECOND);
    do
    {
        current_time = mtime_read();
    } while(current_time < end_time);
}

/* 1ms tick */
int mtime_isr(void)
{
    uint64_t current_time = mtime_read();
    mtime_write(current_time + CPUTIME_TIMER_FREQ / TICK_PER_SECOND);
    return 0;
}

void mtime_init()
{
    uint32_t current_time = *MTIME_LOW;
    *MTIMECMP_LOW = current_time + CPUTIME_TIMER_FREQ / TICK_PER_SECOND;
    asm volatile("csrs mie, %0" : : "r"(MIE_MTIE));
}