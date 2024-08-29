.section .text._start

.globl _start
_start:
    csrrci a0, mstatus, 0x8
    li a0, 0x1800
    csrw mstatus, a0

    /*
    1. 读取 cpuid, 如果是其他核心，则让它等着，主核启动之后，让从核启动，从核启动后，要跑那些代码呢？
    2. 跑那些代码，是我决定的
    3. 每个核心都有自己的一套寄存器、中断向量表, 来中断之后，那个核心处理？
    4. 每个核都有可能跑代码段的指令，那么对于临界区的保户是怎么样的，能用 mutex 吗？
    5. 在某一时刻，如何指定让某些核运行指定的代码？
     */

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
