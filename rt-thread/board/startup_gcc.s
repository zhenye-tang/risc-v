#include "rtconfig.h"

.section .text._start
.globl _start
_start:
    csrw mideleg, 0
    csrw medeleg, 0
    csrw mie, 0
    csrw mip, 0

    li     t0, 3 << 11      # mpp: 11 Machine mode
    csrr   a1, mstatus
    or     t0, t0, a1
    csrw   mstatus, t0
    la     gp, __global_pointer

    la      t0, trap_entry
    csrw    mtvec, t0

    csrr    a0, mhartid
    la      sp, __stack_start__
    addi    t1, a0, 1
    li      t2, __STACKSIZE__
    mul     t1, t1, t2
    add     sp, sp, t1
#ifdef RT_USING_SMP
    bnez a0, secondary_cpu_entry
#endif
    j    primary_cpu_entry

primary_cpu_entry:
    /* bss init */
    la   t0, __bss_start
    la   t1, __bss_end
1:
    bge  t0, t1, 2f
    sw   zero, 0(t0)
    addi t0, t0, 4
    j    1b
2:
	call entry
	tail exit

#ifdef RT_USING_SMP
secondary_cpu_entry:
  la a0, secondary_boot_flag
  lw a0, 0(a0)
  li a1, 0xa55a
  beq a0, a1, 1f

  j secondary_cpu_entry

1:
    tail secondary_cpu_c_start

.data
.global secondary_boot_flag
.align 2
secondary_boot_flag:
    .word 0
#endif