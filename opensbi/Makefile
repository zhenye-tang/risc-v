CROSS_COMPILE ?= riscv64-zephyr-elf-

objs := startup_gcc.o main.o

riscv.bin:$(objs)
	$(CROSS_COMPILE)gcc -march=rv64imazicsr -mabi=lp64 -Tlink.lds -nostartfiles -o riscv.elf $^
	$(CROSS_COMPILE)objcopy -O binary -S riscv.elf $@
	$(CROSS_COMPILE)objdump -D riscv.elf > riscv.dis

%.o:%.s
	$(CROSS_COMPILE)gcc -march=rv64imazicsr -mabi=lp64 -Wall -nostdlib -c -O0 -g -o $@ $<

%.o:%.c
	$(CROSS_COMPILE)gcc -march=rv64imazicsr -mabi=lp64 -Wall -nostdlib -c -O0 -g -o $@ $<
	
clean:
	rm -rf *.o riscv.bin riscv.elf riscv.dis