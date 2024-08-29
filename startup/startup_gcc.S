.section .text._start

.globl _start
_start:
    csrr a0, mhartid

    li  t0, 0
    beq a0, t0, __primary_core0_init # 如果是第 0 个核

    li  t0, 1
    beq a0, t0, __secondary_core1_init # 如果是第 0 个核

    li  t0, 2
    beq a0, t0, __secondary_core2_init # 如果是第 0 个核

    li  t0, 3
    beq a0, t0, __secondary_core3_init # 如果是第 0 个核

__primary_core0_init:
    csrrci a0, mstatus, 0x8
    li a0, 0x1800
    csrw mstatus, a0

    la      t0, trap_entry
    csrw    mtvec, t0

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
    csrsi mstatus, 0x8

    j main





__secondary_core1_init:
    wfi
    j __secondary_core1_init

__secondary_core2_init:
    wfi
    j __secondary_core2_init

__secondary_core3_init:
    wfi
    j __secondary_core3_init

