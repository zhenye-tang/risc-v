#include "uart.h"
#include <stdint.h>

int main(void)
{
    uart_init();
    uart_printf("hello risc-v.\n");
    while(1)
    {
    }

    return 0;
}