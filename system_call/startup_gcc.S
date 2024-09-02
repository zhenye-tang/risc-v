.section .text._start

.globl _start
_start:
    li     t0, 3 << 11      # mpp: 11 Machine mode
    csrc   mstatus, t0
    li     t0, 1 << 7
    csrs   mstatus, t0

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

    /*
        For qemu version >= 6.0, exception would be raised if no PMP enty is
        configured. So just configure one entny, which allows all the whole
        32-bits physical address range is R/W/X.
    */
    li      t0, 0xffffffff
    csrw    pmpaddr0, t0
    li      t0, 0xf
    csrw    pmpcfg0, t0

    la sp, _sstack
    la t0, main
    csrw mepc, t0
    mret
