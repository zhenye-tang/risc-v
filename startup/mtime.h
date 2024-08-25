#ifndef __MTIME_H__
#define __MTIME_H__

#include <stdint.h>

#define CPUTIME_TIMER_FREQ              (10000000)
#define TICK_PER_SECOND                 (1000)

void mtime_mdelay(int ms);
void mtime_init();
int mtime_isr(void);
uint64_t mtime_read(void);

#endif