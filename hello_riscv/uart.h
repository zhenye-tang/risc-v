#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

void uart_init(void);
void uart_puts(const char* str);
char uart_getc(void);
void uart_printf(const char* fmt,...);

#ifdef __cplusplus
}
#endif


#endif