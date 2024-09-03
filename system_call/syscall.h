#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#define SET_TIMER               0
#define CONSOLE_PUTCHAR         1
#define CONSOLE_GETCHAR         2
#define SHUTDOWN                3
#define GET_HARTID              4

int system_call(uint32_t arg7, uint32_t arg0);
int system_call_putchar(char c);
int system_gethart(void);

#endif //__SYSCALL_H__