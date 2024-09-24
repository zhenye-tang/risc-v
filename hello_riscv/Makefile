CROSS_COMPILE ?= riscv32-unknown-elf-

objs := interrupt_gcc.o startup_gcc.o main.o uart.o irq.o plic.o trap.o mtime.o vsnprintf.o

riscv32.bin:$(objs)
	$(CROSS_COMPILE)gcc -Wl,-Map=riscv32.map -nostartfiles -Tlink.lds -o riscv32.elf $^
	$(CROSS_COMPILE)objcopy -O binary -S riscv32.elf $@
	$(CROSS_COMPILE)objdump -D riscv32.elf > riscv32.dis

%.o:%.S
	$(CROSS_COMPILE)gcc -march=rv32imazicsr -mabi=ilp32 -Wall -nostdlib -c -O0 -g -o $@ $<

%.o:%.c
	$(CROSS_COMPILE)gcc -march=rv32imazicsr -mabi=ilp32 -Wall -nostdlib -c -O0 -g -o $@ $<
	
clean:
	rm -rf *.o riscv32.bin riscv32.elf riscv32.dis