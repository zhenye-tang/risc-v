#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>

#define SRAM_START_ADDR        (0x80000000)
#define SRAM_SIZE              (0x1000000)

extern rt_uint8_t __bss_end;

extern int rt_hw_clint_ipi_enable(void);

void rt_hw_board_init()
{
    rt_hw_interrupt_init();
#ifdef RT_USING_SMP
    rt_hw_clint_ipi_enable();
#endif
    rt_system_heap_init((void *)&__bss_end, (void *)(SRAM_START_ADDR + SRAM_SIZE));
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}
