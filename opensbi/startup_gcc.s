.section .text._start

boot_hartid: .int
  .global      boot_hartid

.globl _start
_start:
  # save hartid
  la t0, boot_hartid                # global varible rt_boot_hartid
  mv t1, a0                         # get hartid in S-mode frome a0 register
  sw t1, (t0)                       # store t1 register low 4 bits in memory address which is stored in t0

  la sp, _sstack
  call main