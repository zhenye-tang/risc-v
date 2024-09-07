#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "rtconfig.h"
#include "tick.h"
#include "drv_uart.h"

#define RT_HEAP_SIZE (1*1024*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

void rt_hw_board_init()
{
    rt_hw_interrupt_init();
    rt_system_heap_init(rt_heap, rt_heap + RT_HEAP_SIZE);
    rt_hw_tick_init();
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
