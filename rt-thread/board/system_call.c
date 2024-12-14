#include <stdint.h>
#include "system_call.h"

int system_call(uint32_t arg7, uint32_t arg0)
{
    int ret;
    register uintptr_t a7 __asm("a7") = (uintptr_t)(arg7);
    register uintptr_t a0 __asm("a0") = (uintptr_t)(arg0);
    __asm __volatile(
                     "ecall"
                     : "=r"(a0)
                     : "r"(a7), "r"(a0)
                     : "memory");
    ret = a0;
    return (ret);
}

void system_console_output(const char *str)
{
    while (*str)
    {
        system_call(CONSOLE_PUTCHAR, *str++);
    }
}

int system_gethart(void)
{
    return system_call(GET_HARTID, 0);
}

int system_current_mode(void)
{
    return system_call(GET_CUR_MODE, 0);
}
