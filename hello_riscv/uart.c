#include <stdint.h>
#include <stddef.h>
#include "irq.h"
#include "uart.h"
#include <stdio.h>
#include <stdarg.h>

#define UART_BASE                     0x10000000
#define UART_RBR                      (*(volatile uint8_t *)(UART_BASE + 0x00))
#define UART_THR                      (*(volatile uint8_t *)(UART_BASE + 0x00))
#define UART_IER                      (*(volatile uint8_t *)(UART_BASE + 0x01))
#define UART_IIR                      (*(volatile uint8_t *)(UART_BASE + 0x02))
#define UART_FCR                      (*(volatile uint8_t *)(UART_BASE + 0x02))
#define UART_LCR                      (*(volatile uint8_t *)(UART_BASE + 0x03))
#define UART_LSR                      (*(volatile uint8_t *)(UART_BASE + 0x05))
#define UART_IRQ                      10

void uart_putc(char c);

static void uart_isr(int vector, void *param)
{
    char c = uart_getc();
    uart_putc(c);
}

void uart_putc(char c)
{
    while (!(UART_LSR & 0x20));
    UART_THR = c;
}

char uart_getc(void)
{
    while (!(UART_LSR & 0x01));
    return UART_RBR;
}

void uart_puts(const char* str)
{
    while (*str)
    {
        uart_putc(*str++);
    }
}

void uart_init(void)
{
    UART_LCR = 0x03;
    UART_FCR = 0x07;
    UART_IER = 0x01;
    interrupt_install(UART_IRQ, uart_isr, NULL);
    interrupt_umask(UART_IRQ);
}

void uart_printf(char* fmt,...)
{
    static uint8_t tx_buf[200];
    va_list ap;
    va_start(ap,fmt);
    vsnprintf((char*)tx_buf,200, fmt,ap);
    va_end(ap);
    uart_puts((const char *)tx_buf);
}