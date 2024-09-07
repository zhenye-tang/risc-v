import os
ARCH     = 'risc-v'
CPU      = 'qemu-virt'

CROSS_TOOL  = 'gcc'
PLATFORM    = 'gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')
if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')

if os.getenv('RTT_EXEC_PATH'):
   EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

CORE = 'risc-v'
MAP_FILE = 'rtthread.map'
LINK_FILE = './link.lds'
TARGET_NAME = 'rtthread.bin'

if PLATFORM == 'gcc':
    PREFIX = 'riscv64-unknown-elf-'
    CC = PREFIX + 'gcc'
    CXX= PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -march=rv32imac_zicsr -mabi=ilp32 -nostartfiles -lc '
    CFLAGS = DEVICE
    CFLAGS += ' -save-temps=obj'
    AFLAGS = '-c'+ DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE
    LFLAGS += ' -Wl,--gc-sections,-cref,-Map=' + MAP_FILE
    LFLAGS += ' -T ' + LINK_FILE
    AFLAGS += ' -I. '
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -g3'
        AFLAGS += ' -g3'
    else:
        CFLAGS += ' -O2'

    CXXFLAGS = CFLAGS

    POST_ACTION = OBJCPY + ' -O binary $TARGET ' + TARGET_NAME + '\n'
    POST_ACTION += SIZE + ' $TARGET\n'
    