#include <stdint.h>
#include "syscall.h"

static void hw_console_output(const char *str)
{
    while (*str)
    {
        system_call_putchar(*str++);
    }
}

int main(void)
{
    hw_console_output("hello system call.\n");
    int hart_id = system_gethart();
    hw_console_output("current hart id: ");
    system_call_putchar(hart_id + '0');
    hw_console_output("\n");

    while(1)
    {

    }

    return 0;
}