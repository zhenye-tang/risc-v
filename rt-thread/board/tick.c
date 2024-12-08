#include "rtdef.h"
#include <rtthread.h>
#include <encoding.h>
#include <stdint.h>
#include "clint.h"

void rt_hw_us_delay(rt_uint32_t us)
{

}

static int clint_timer_cb(void *user)
{
    rt_tick_increase();
}

int rt_hw_tick_init(void)
{
    clint_timer_init();
    clint_timer_start(1, 0);
    clint_timer_register(clint_timer_cb, NULL);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_tick_init);
