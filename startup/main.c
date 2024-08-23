#include "uart.h"
#include <stdint.h>

#define MTIMECMP   ((volatile uint32_t*)0x02004000)
#define MTIME      ((volatile uint32_t*)0x0200BFF8)
#define MIE_MTIE   0x80
#define MSTATUS_MIE 0x8

int func_a(int a, int b)
{
    return a + b;
}

int main(void)
{

    uint32_t current_time = *MTIME;
    *MTIMECMP = current_time + 10000;  // 设置 1ms 的间隔
    asm volatile("csrs mie, %0" : : "r"(0x80));

    int a,b;
    a = 10;
    b = 20;
    a = a + b;
    func_a(a, b);

    uart_puts("hello world\n");

    while(1);

    return 0;
}