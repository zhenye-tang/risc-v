#include "clint.h"
#include "encoding.h"

#define CLINT_NUM_CORES            10
#define CPUTIME_TIMER_FREQ         10000000

volatile clint_t *const clint = (volatile clint_t *)CLINT_BASE_ADDR;

struct clint_timer_desc
{
    uint64_t delayms;
    uint64_t ticks;
    uint64_t one_shot;
    clint_timer_cb_t cb;
    void *user_data;
};

struct clint_ipi_desc
{
    clint_ipi_cb_t cb;
    void *user_data;
};

struct clint_ipi_desc clint_ipi_desc[CLINT_NUM_CORES];
struct clint_timer_desc clint_timer_desc[CLINT_NUM_CORES];

int clint_ipi_init(void)
{
    unsigned long id = current_coreid();
    /* Clear Machine Software Interrupt bit, disable software interrupt  */
    clear_csr(mie, MIP_MSIP);
    clint_ipi_desc[id] = (struct clint_ipi_desc){0};
    return 0;
}

int clint_ipi_enable(void)
{
    set_csr(mstatus, MSTATUS_MIE);
    set_csr(mie, MIP_MSIP);
    return 0;
}

int clint_ipi_disable(void)
{
    clear_csr(mie, MIP_MSIP);
    return 0;
}

int clint_ipi_register(clint_ipi_cb_t callback, void *user_data)
{
    unsigned long id = current_coreid();
    clint_ipi_desc[id].cb = callback;
    clint_ipi_desc[id].user_data = user_data;
    return 0;
}

int clint_ipi_send(size_t core_id)
{
    if (core_id > CLINT_NUM_CORES)
        return -1;

    clint->msip[core_id].msip = 1;
    return 0;
}

int clint_ipi_clear(size_t core_id)
{
    if (core_id > CLINT_NUM_CORES)
        return -1;
    if (clint->msip[core_id].msip)
        clint->msip[core_id].msip = 0;
    return 0;
}

int clint_timer_init(void)
{
    clear_csr(mie, MIP_MTIP);
    unsigned long id = current_coreid();
    clint_timer_desc[id] = (struct clint_timer_desc){0};
    return 0;
}

int clint_timer_start(uint64_t delayms, int one_shot)
{
    int id = current_coreid();

    clint_timer_desc[id].delayms = delayms;
    clint_timer_desc[id].one_shot = one_shot;
    clint_timer_desc[id].ticks = delayms * (CPUTIME_TIMER_FREQ / 1000UL);

    uint64_t now = clint->mtime;
    uint64_t end = now + clint_timer_desc[id].ticks;
    clint->mtimecmp[id].value = end;
    set_csr(mstatus, MSTATUS_MIE);
    set_csr(mie, MIP_MTIP);

    return 0;
}

int clint_timer_register(clint_timer_cb_t callback, void *user_data)
{
    int id = current_coreid();
    clint_timer_desc[id].cb = callback;
    clint_timer_desc[id].user_data = user_data;
    return 0;
}

uintptr_t clint_timer_current_tick(void)
{
    return clint->mtime;
}

int clint_timer_mdelay(uintptr_t ms)
{
    uintptr_t end = clint->mtime + ms * (CPUTIME_TIMER_FREQ / 1000UL);
    uintptr_t current_time = clint->mtime;
    while(current_time < end)
    {
        current_time = clint->mtime;
    }
    return 0;
}

uintptr_t clint_m_timer_irq_handle(uintptr_t mepc)
{
    int id = current_coreid();

    clear_csr(mie, MIP_MTIP);
    if (clint_timer_desc[id].cb)
        clint_timer_desc[id].cb(clint_timer_desc[id].user_data);

    if (!clint_timer_desc[id].one_shot && clint_timer_desc[id].ticks)
    {
        clint->mtimecmp[id].value += clint_timer_desc[id].ticks;
        set_csr(mie, MIP_MTIP);
    }

    return mepc;
}

uintptr_t clint_m_soft_irq_handle(uintptr_t mepc)
{
    int id = current_coreid();

    clear_csr(mie, MIP_MSIP);
    clint->msip[id].msip = 0;
    if (clint_ipi_desc[id].cb)
        clint_ipi_desc[id].cb(clint_ipi_desc[id].user_data);
    set_csr(mie, MIP_MSIP);
    return mepc;
}

