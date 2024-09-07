.section .text._start

.globl _start
_start:
    li     t0, 3 << 11      # mpp: 11 Machine mode
    csrr   a1, mstatus
    or     t0, t0, a1
    csrw   mstatus, t0

    la      t0, SW_handler
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
    la sp, __stack_cpu0
	call entry
	tail exit
