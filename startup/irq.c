#include <stdint.h>
#include "uart.h"


#define MTIMECMP   ((volatile uint32_t*)0x02004000)
#define MTIME      ((volatile uint32_t*)0x0200BFF8)
#define MIE_MTIE   0x80
#define MSTATUS_MIE 0x8

void handle_interrupt(void)
{
    uint32_t vector;
    __asm__ __volatile__("csrr %0,mcause"
                         : "=r"(vector));
    uart_puts("interrupt!!\n");
    uint32_t current_time = *MTIME;
    *MTIMECMP = current_time + 10000000;  // 设定下次中断时间（1 秒后）
}