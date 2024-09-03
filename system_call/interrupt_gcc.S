.macro save_contex
    addi sp, sp, -128 
    sw x1, 4*1(sp)
    sw x3, 4*3(sp)
    sw x4, 4*4(sp)
    sw x5, 4*5(sp)
    sw x6, 4*6(sp)
    sw x7, 4*7(sp)
    sw x8, 4*8(sp)
    sw x9, 4*9(sp)
    sw x10, 4*10(sp)
    sw x11, 4*11(sp)
    sw x12, 4*12(sp)
    sw x13, 4*13(sp)
    sw x14, 4*14(sp)
    sw x15, 4*15(sp)
    sw x16, 4*16(sp)
    sw x17, 4*17(sp)
    sw x18, 4*18(sp)
    sw x19, 4*19(sp)
    sw x20, 4*20(sp)
    sw x21, 4*21(sp)
    sw x22, 4*22(sp)
    sw x23, 4*23(sp)
    sw x24, 4*24(sp)
    sw x25, 4*25(sp)
    sw x26, 4*26(sp)
    sw x27, 4*27(sp)
    sw x28, 4*28(sp)
    sw x29, 4*29(sp)
    sw x30, 4*30(sp)
    sw x31, 4*31(sp)

    csrr t0, mstatus
    sw t0, 4*2(sp)
.endm

.macro restore_contex
    lw t0, 4*2(sp)
    csrw mstatus, t0

    lw x1, 4*1(sp)
    lw x3, 4*3(sp)
    lw x4, 4*4(sp)
    lw x5, 4*5(sp)
    lw x6, 4*6(sp)
    lw x7, 4*7(sp)
    lw x8, 4*8(sp)
    lw x9, 4*9(sp)
    lw x10, 4*10(sp)
    lw x11, 4*11(sp)
    lw x12, 4*12(sp)
    lw x13, 4*13(sp)
    lw x14, 4*14(sp)
    lw x15, 4*15(sp)
    lw x16, 4*16(sp)
    lw x17, 4*17(sp)
    lw x18, 4*18(sp)
    lw x19, 4*19(sp)
    lw x20, 4*20(sp)
    lw x21, 4*21(sp)
    lw x22, 4*22(sp)
    lw x23, 4*23(sp)
    lw x24, 4*24(sp)
    lw x25, 4*25(sp)
    lw x26, 4*26(sp)
    lw x27, 4*27(sp)
    lw x28, 4*28(sp)
    lw x29, 4*29(sp)
    lw x30, 4*30(sp)
    lw x31, 4*31(sp)

    addi sp, sp, 128
.endm

.globl trap_entry
trap_entry:
    save_contex
    # trap handler
    csrr    a0, mcause
    csrr    a1, mepc
    mv      a2, sp
    call    handle_trap
    csrw mepc, a0
    restore_contex
    /*
        1. Return from the machine mode exception handler. Set PC to mepc.
        2. Set the privilege level to mstatus.mpp, mstatus.mie to mstatus.mpie, and clear mstatus.mpie to 0.
        3. If user mode is supported, set mstatus.mpp to 0.
    */
    mret
