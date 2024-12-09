#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>
#include "encoding.h"
#include "clint.h"
#include "atomic.h"


int rt_hw_cpu_id(void)
{
    return read_csr(mhartid);
}

#ifdef RT_USING_SMP

void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    ((spinlock_t *)lock)->lock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    spinlock_lock((spinlock_t *)lock);
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    spinlock_unlock((spinlock_t *)lock);
}

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    int idx;
    for (idx = 0; idx < RT_CPUS_NR; idx ++)
    {
        if (cpu_mask & (1 << idx))
        {
            clint_ipi_send(idx);
        }
    }
}

extern rt_base_t secondary_boot_flag;
void rt_hw_secondary_cpu_up(void)
{
    mb();
    secondary_boot_flag = 0xa55a;
}

extern void rt_hw_scondary_interrupt_init(void);
extern int rt_hw_tick_init(void);
extern int rt_hw_clint_ipi_enable(void);

static int clint_ipi_cb(void *user_data)
{
    rt_schedule();
}

void secondary_cpu_c_start(void)
{
    rt_hw_spin_lock(&_cpus_lock);
    rt_hw_scondary_interrupt_init();
    rt_hw_tick_init();
    rt_hw_clint_ipi_enable();
    clint_ipi_register(clint_ipi_cb, NULL);
    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfi");
}

#endif

