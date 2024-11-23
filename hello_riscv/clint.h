#ifndef __CLINT_H__
#define __CLINT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/**
 * CLINT RAM Layout
 *
 * | Address   -| Description                     |
 * |------------|---------------------------------|
 * | 0x02000000 | msip for core 0                 |
 * | 0x02000004 | msip for core 1                 |
 * | ...        | ...                             |
 * | 0x02003FF8 | msip for core 4094              |
 * |            |                                 |
 * | 0x02004000 | mtimecmp for core 0             |
 * | 0x02004008 | mtimecmp for core 1             |
 * | ...        | ...                             |
 * | 0x0200BFF0 | mtimecmp For core 4094          |
 * | 0x0200BFF8 | mtime                           |
 * |            |                                 |
 * | 0x0200C000 | Reserved                        |
 * | ...        | ...                             |
 * | 0x0200EFFC | Reserved                        |
 */

#define CLINT_BASE_ADDR             (0x02000000U)

typedef struct 
{
    struct
    {
        uint32_t msip : 1;
        uint32_t zero : 31;
    } msip[4095];
    uint32_t resv;
    struct
    {
        union
        {
            struct
            {
                uint64_t low : 32;
                uint64_t hight : 32;
            };
            uint64_t value;
        };
    } mtimecmp[4095];
    uint64_t mtime;
} clint_t;

typedef int (*clint_ipi_cb_t)(void *user_data);
typedef int (*clint_timer_cb_t)(void *user_data);

/* Inter-Processor Interrupt init */
int clint_ipi_init(void);
int clint_ipi_enable(void);
int clint_ipi_disable(void);
int clint_ipi_send(size_t hart_id);
int clint_ipi_clear(size_t hart_id);
int clint_ipi_register(clint_ipi_cb_t callback, void *user_data);

/* CLINT timer init*/
int clint_timer_init(void);
int clint_timer_start(uint64_t delayms, int one_shot);
int clint_timer_register(clint_timer_cb_t callback, void *user_data);
int clint_timer_mdelay(uintptr_t ms);
uintptr_t clint_timer_current_tick(void);

#ifdef __cplusplus
}
#endif

#endif //__CLINT_H__