#include "rtdef.h"
#include <rtthread.h>
#include <encoding.h>
#include <stdint.h>

#define MTIMECMP_LOW                              ((volatile uint32_t*)0x02004000)
#define MTIMECMP_HIGHT                            ((volatile uint32_t*)0x02004004)
#define MTIME_LOW                                 ((volatile uint32_t*)0x0200BFF8)
#define MTIME_HIGHT                               ((volatile uint32_t*)0x0200BFFC)
#define MIE_MTIE                                  (1 << 7)
#define CPUTIME_TIMER_FREQ                        (10000000)

static uint64_t mtime_read(void)
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

static void mtime_write(uint64_t tick)
{
    *MTIMECMP_LOW = tick & 0xffffffff;
    *MTIMECMP_HIGHT = (tick << 32) & 0xffffffff;
}

static void mtime_update(void)
{
    uint64_t current_time = mtime_read();
    mtime_write(current_time + CPUTIME_TIMER_FREQ / RT_TICK_PER_SECOND);
}

void rt_hw_us_delay(rt_uint32_t us)
{
    uint64_t current_time = mtime_read();
    uint64_t end_time = current_time + us * (CPUTIME_TIMER_FREQ / 10000000);
    do
    {
        current_time = mtime_read();
    } while(current_time < end_time);
}

int rt_hw_tick_isr(void)
{
    mtime_update();
    rt_tick_increase();
    return 0;
}

int rt_hw_tick_init(void)
{
    clear_csr(mie, MIP_MTIP);
    mtime_update();
    set_csr(mie, MIP_MTIP);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_tick_init);
