#ifndef __PLIC_H__
#define __PLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif //__PLIC_H__