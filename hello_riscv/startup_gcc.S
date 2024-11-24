#define __STACKSIZE__           16384

.section .text._start

.globl _start
_start:
    li     t0, 3 << 11      # mpp: 11 Machine mode
    csrr   a1, mstatus
    or     t0, t0, a1
    csrw   mstatus, t0

    la      t0, trap_entry
    csrw    mtvec, t0

    csrr    a0, mhartid
    la      sp, __stack_start__
    addi    t1, a0, 1
    li      t2, __STACKSIZE__
    mul     t1, t1, t2
    add     sp, sp, t1

    bnez    a0, secondary
    tail    primary_cpu_entry

secondary:
    tail    secondary_cpu_entry 
