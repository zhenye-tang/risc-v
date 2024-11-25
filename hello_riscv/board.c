#include "clint.h"
#include "uart.h"
#include "atomic.h"

extern unsigned int __bss_start;
extern unsigned int __bss_end;

extern unsigned int _sidata;
extern unsigned int _sdata;
extern unsigned int _edata;

static int weakup_flag;

void bss_init(void)
{
    unsigned int *start =  &__bss_start;
    while (start < &__bss_end)
    {
        *start++ = 0;
    }
}

void data_init(void)
{
    unsigned int *src =  &_sidata;
    unsigned int *dst =  &_sdata;
    if (src != dst)
    {
        while (dst < &_edata)
        {
            *dst++ = *src++;
        }
    }
}

void primary_cpu_entry(void)
{
    bss_init();
    data_init();
    extern int main(void);
    main();
    while(1);
}

void secondary_cpu_weakup(void)
{
    weakup_flag = 1;
    /* Use memory barrier to keep coherency */
    mb();
}

static int clint_ipi_cb(void *user_data)
{
    uart_printf(user_data);
    return 0;
}

static int clint_timer_cb(void *user_data)
{
    clint_ipi_send(0);
    return 0;
}

void secondary_cpu_entry(void)
{
    /* TODO: What if weakup_flag is a junk value? Is there a more elegant way?*/
    while (!weakup_flag);

    clint_timer_init();
    clint_timer_start(2000, 0);
    clint_timer_register(clint_timer_cb, NULL);

    clint_ipi_init();
    clint_ipi_enable();
    clint_ipi_register(clint_ipi_cb, "core1 soft isr.\n");

    while (1)
    {
        clint_timer_mdelay(1000);
    }
}