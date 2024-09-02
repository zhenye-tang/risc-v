CROSS_COMPILE ?= riscv32-unknown-elf-

objs := startup_gcc.o interrupt_gcc.o main.o uart.o trap.o vsnprintf.o

riscv32.bin:$(objs)
	$(CROSS_COMPILE)ld --no-warn-rwx-segments -Tlink.lds -o riscv32.elf $^
	$(CROSS_COMPILE)objcopy -O binary -S riscv32.elf $@
	$(CROSS_COMPILE)objdump -D riscv32.elf > riscv32.dis

%.o:%.S
	$(CROSS_COMPILE)gcc -march=rv32imazicsr -mabi=ilp32 -Wall -nostdlib -c -O0 -g -o $@ $<

%.o:%.c
	$(CROSS_COMPILE)gcc -march=rv32imazicsr -mabi=ilp32 -Wall -nostdlib -c -O0 -g -o $@ $<
	
clean:
	rm -rf *.o riscv32.bin riscv32.elf riscv32.dis