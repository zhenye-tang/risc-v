CROSS_COMPILE ?= /home/tzy/riscv32_tool/bin/riscv32-unknown-elf-

objs := start.o main.o uart.o irq.o

riscv32.bin:$(objs)
	$(CROSS_COMPILE)ld -Tlink.lds -o riscv32.elf $^
	$(CROSS_COMPILE)objcopy -O binary -S riscv32.elf $@
	$(CROSS_COMPILE)objdump -D riscv32.elf > riscv32.dis
	
%.o:%.s
	$(CROSS_COMPILE)gcc -march=rv32imazicsr -mabi=ilp32 -Wall -nostdlib -c -O0 -g -o $@ $<

%.o:%.c
	$(CROSS_COMPILE)gcc -march=rv32imazicsr -mabi=ilp32 -Wall -nostdlib -c -O0 -g -o $@ $<
	
clean:
	rm -rf *.o riscv32.bin riscv32.elf riscv32.dis