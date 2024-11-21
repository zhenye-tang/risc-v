#include "clint.h"
#include "encoding.h"

#define CLINT_NUM_CORES            10
volatile clint_t *const clint = (volatile clint_t *)CLINT_BASE_ADDR;

struct clint_ipi_desc
{
    clint_ipi_cb_t cb;
    void *user_data;
};

struct clint_ipi_desc clint_ipi_desc[CLINT_NUM_CORES];

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