#ifndef __PLIC_H__
#define __PLIC_H__

#include <stdint.h>

#define PLIC_M_BASE                          0x0C000000
#define PLIC_M_PRIORITY_OFFSET               0x0000
#define PLIC_M_ENABLE_OFFSET                 0x2000
#define PLIC_M_ENABLE_STRIDE_OFFECT          0x80
#define PLIC_M_PENDING_BASE                  0x1000
#define PLIC_M_CLAIM_OFFSET                  0x200004
#define PLIC_M_COMPLETE_OFFSET               0x200004
#define PLIC_M_THRESHOLD_OFFSET              0x200000
#define PLIC_M_CONTEXT_STRIDE_OFFSET         0x1000

/* halt plic enable base */
#define PLIC_ENABLE_BASE(hart, id)              (PLIC_M_BASE + PLIC_M_ENABLE_OFFSET + hart * PLIC_M_ENABLE_STRIDE_OFFECT + (id / 32) * 4)
/* halt plic threshold base */
#define PLIC_THRESHOLD(hart)                    (PLIC_M_BASE + PLIC_M_THRESHOLD_OFFSET + hart * PLIC_M_CONTEXT_STRIDE_OFFSET)
/* halt plic claim base */
#define PLIC_CLAIM(hart)                        (PLIC_M_BASE + PLIC_M_CLAIM_OFFSET +  hart * PLIC_M_CONTEXT_STRIDE_OFFSET)
/* halt plic complete base */
#define PLIC_COMPLETE(hart)                     (PLIC_M_BASE + PLIC_M_COMPLETE_OFFSET +  hart * PLIC_M_CONTEXT_STRIDE_OFFSET)
/* halt plic priority base */
#define PLIC_PRIORITY(id)                       (PLIC_M_BASE + PLIC_M_PRIORITY_OFFSET +  id * 4)

void plic_set_priority(int irq, int priority);
void plic_irq_enable(int irq);
void plic_irq_disable(int irq);
void plic_set_threshold(int mthreshold);
int  plic_claim(void);
void plic_complete(int irq);

typedef struct plic_priority
{
    uint32_t priority[1024];
} plic_priority_t;

typedef struct plic_pending
{
    uint32_t pending[32];
    uint32_t reverse[1024 - 32];
} plic_pending_t;

typedef struct plic_enable
{
    struct
    {
        uint32_t enable[32];
    } target[15872]; //0x1F1FFC
    uint8_t reverse[0xe000]; // 0x1FFFFC
} plic_enable_t;

typedef struct 
{
    plic_priority_t priority;
    plic_pending_t pendding;
    plic_enable_t enable;
} plic_t;

#endif //__PLIC_H__