#ifndef __ATOMIC_H__
#define __ATOMIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* memory barrier macro */
#define mb()                          \
    {                                 \
        asm volatile("fence" ::       \
                         : "memory"); \
    }

#define atomic_swap(ptr, val) __sync_lock_test_and_set(ptr, val)
#define atomic_add(ptr, val) __sync_fetch_and_add(ptr, val)
#define atomic_or(ptr, val) __sync_fetch_and_or(ptr, val)
#define atomic_cas(ptr, oldval, newval) __sync_val_compare_and_swap(ptr, oldval, newval)
#define atomic_set(ptr, val) (*(volatile typeof(*(ptr)) *)(ptr) = val)
#define atomic_read(ptr) (*(volatile typeof(*(ptr)) *)(ptr))

typedef struct spinlock
{
    int lock;
} spinlock_t;

static inline int spinlock_trylock(spinlock_t *lock)
{
    int res = atomic_swap(&lock->lock, -1);
    mb();
    return res;
}

static inline void spinlock_lock(spinlock_t *lock)
{
    /* TODO: Enter sleep mode using the wfe command */
    while (spinlock_trylock(lock));
}

static inline void spinlock_unlock(spinlock_t *lock)
{
    /* TODO: Use SEV to wake up other cores */
    atomic_set(&lock->lock, 0);
    mb();
}

#ifdef __cplusplus
}
#endif

#endif // __ATOMIC_H__