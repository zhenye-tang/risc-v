#include <stdint.h>

void handle_trap(unsigned long mcause)
{
    if (mcause == 0x80000007)
    {

    }
    else if (mcause == 0x8000000B)
    {
        /* extern isr */
    }
    else if (mcause == 0x80000003)
    {
        /* M mode soft isr */
    }
    else
    {
        /* exception */
        while(1);
    }

}
