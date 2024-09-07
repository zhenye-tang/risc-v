#include "rtdef.h"
#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <stddef.h>
#include <stdio.h>

struct device_uart
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
};

static void *uart0_base = (void*)0x10000000;
static struct rt_serial_device serial0;
static struct device_uart uart0;

#define UART_BASE                     0x10000000
#define UART_RBR                      (*(volatile uint8_t *)(UART_BASE + 0x00))
#define UART_THR                      (*(volatile uint8_t *)(UART_BASE + 0x00))
#define UART_IER                      (*(volatile uint8_t *)(UART_BASE + 0x01))
#define UART_IIR                      (*(volatile uint8_t *)(UART_BASE + 0x02))
#define UART_FCR                      (*(volatile uint8_t *)(UART_BASE + 0x02))
#define UART_LCR                      (*(volatile uint8_t *)(UART_BASE + 0x03))
#define UART_LSR                      (*(volatile uint8_t *)(UART_BASE + 0x05))
#define UART_IRQ                      10

void uart_init(void)
{
    UART_LCR = 0x03;
    UART_FCR = 0x07;
    UART_IER = 0x01;
}

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    uart_init();
    return (RT_EOK);
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart = (struct device_uart*)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        break;

    case RT_DEVICE_CTRL_SET_INT:
        break;
    }

    return (RT_EOK);
}

static int _uart_putc(struct rt_serial_device *serial, char c)
{
    while (!(UART_LSR & 0x20));
    UART_THR = c;
    return (1);
}

static int _uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    if (UART_LSR & 0x01)
        ch = UART_RBR;
    return ch;
}

const struct rt_uart_ops _uart_ops = {
    _uart_configure,
    _uart_control,
    _uart_putc,
    _uart_getc,
    // TODO: add DMA support
    RT_NULL};

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    serial = &serial0;
    uart = &uart0;

    serial->ops = &_uart_ops;
    serial->config = config;
    serial->config.baud_rate = 115200;
    uart->hw_base = (rt_ubase_t)uart0_base;
    uart->irqno = 0x0a;

    rt_hw_serial_register(serial,
                          RT_CONSOLE_DEVICE_NAME,
                          RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, serial, RT_CONSOLE_DEVICE_NAME);
    rt_hw_interrupt_umask(uart->irqno);
    return 0;
}

