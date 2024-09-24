.section .text._start

.globl _start
_start:
    li     t0, 3 << 11      # mpp: 11 Machine mode
    csrr   a1, mstatus
    or     t0, t0, a1
    csrw   mstatus, t0

    la      t0, trap_entry
    csrw    mtvec, t0

__data_init:
    la   a0, _sidata
    la   a1, _sdata
    la   a2, _edata
    bgeu a1, a2, __bss_init

__data_copy:
    beq a0, a1, __bss_init
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a1, a1, 4
    addi a0, a0, 4
    bltu a1, a2, 1b

__bss_init:
    la   t0, __bss_start
    la   t1, __bss_end
1:
    bge  t0, t1, __cpu_stack_init
    sw   zero, 0(t0)
    addi t0, t0, 4
    j    1b

__cpu_stack_init:
    la sp, _sstack
    j main
