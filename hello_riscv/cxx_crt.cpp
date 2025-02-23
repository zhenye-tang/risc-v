#include <cstdlib>
#include <vector>
#include <cstdio>
#include "uart.h"
#include <cstddef>

void* __dso_handle = nullptr;

void* operator new(size_t size) {
    void *p = malloc(size);
    return p;
}

void operator delete(void* pointer) noexcept {
    free(pointer);
}

void operator delete(void* pointer, size_t size) noexcept {
    free(pointer);
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void* pointer) noexcept {
    free(pointer);
}

void operator delete[](void* pointer, size_t size) noexcept {
    free(pointer);
}

extern "C" void cplusplus_init(void)
{
    typedef void(*pfunc)();
    extern pfunc __ctors_start__[];
    extern pfunc __ctors_end__[];
    pfunc *p;

    for (p = __ctors_start__; p < __ctors_end__; p++)
        (*p)();
}