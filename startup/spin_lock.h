#ifndef __SPIN_LOCK___
#define __SPIN_LOCK___

typedef int spinlock_t;
#define UNLOCKED 0
#define LOCKED   1

static __inline__ void spin_lock(spinlock_t *lock) {
    while (__atomic_exchange_n(lock, LOCKED, __ATOMIC_ACQUIRE) == LOCKED) {
        /* wait */
    }
}

static __inline__ void spin_unlock(spinlock_t *lock) {
    __atomic_store_n(lock, UNLOCKED, __ATOMIC_RELEASE);
}

#endif //__SPIN_LOCK___