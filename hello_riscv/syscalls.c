#include <stddef.h>
#include <reent.h>

static int heap[200];

// Add memory management algorithm.

void* _malloc_r(struct _reent *r, size_t size)
{
    return (void *)heap;
}

void _free_r (struct _reent *ptr, void *addr)
{
}