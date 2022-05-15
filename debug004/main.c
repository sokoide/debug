#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 2

void* threadEntry(void* dummy);
void foo1();
void foo2();
void foo3();

void* threadEntry(void* dummy) {
    uint64_t thrd_id = thrd_current();
    printf("[t:%08lx] Hello, I'm a new thread\n", thrd_id);
    while (1) {
        printf("[t:%08lx] sleeping\n", thrd_id);
        foo1();
    }

    // this is never called
    printf("[t:%08lx] exitting\n", thrd_id);
    thrd_exit(EXIT_SUCCESS);
}

void foo1() { foo2(); }

void foo2() { foo3(); }

void foo3() {
    // sleep 3 seconds
    thrd_sleep(&(struct timespec){.tv_sec = 3}, NULL);
}

int main(int argc, char** argv) {
    thrd_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        int r = thrd_create(&threads[i], (thrd_start_t)threadEntry, NULL);
        if (r == thrd_error) {
            fprintf(stderr, "[main] failed in thrd_create, ret:%d\n", r);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("[main] wainting for thread %d to complete...\n", i);
        thrd_join(threads[i], NULL);
    }

    printf("[main] all done\n");

    thrd_exit(EXIT_SUCCESS);
}
