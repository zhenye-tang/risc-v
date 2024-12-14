#ifndef __SYSTEM_CALL__
#define __SYSTEM_CALL__

#define SET_TIMER               0
#define CONSOLE_PUTCHAR         1
#define CONSOLE_GETCHAR         2
#define SHUTDOWN                3
#define GET_HARTID              4
#define GET_CUR_MODE            5


int system_call(uint32_t arg7, uint32_t arg0);
void system_console_output(const char *str);
int system_gethart(void);
int system_current_mode(void);


#endif //__SYSTEM_CALL__