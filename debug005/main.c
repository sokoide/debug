#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 3

void* threadEntry1(void* dummy);
void* threadEntry2(void* dummy);
void* threadEntry3(void* dummy);

void* threadEntry1(void* dummy) {
    uint64_t thrd_id = thrd_current();
    printf("[t:%08lx] Hello, I'm a new thread\n", thrd_id);

    thrd_exit(EXIT_SUCCESS);
}

void* threadEntry2(void* dummy) {
    uint64_t thrd_id = thrd_current();
    printf("[t:%08lx] Hello, I'm a new thread\n", thrd_id);
    while (1) {
        printf("[t:%08lx] sleeping\n", thrd_id);
        thrd_sleep(&(struct timespec){.tv_sec = 3}, NULL);
    }

    // this is never called
    printf("[t:%08lx] exitting\n", thrd_id);
    thrd_exit(EXIT_SUCCESS);
}

void* threadEntry3(void* dummy) {
    uint64_t thrd_id = thrd_current();
    printf("[t:%08lx] Hello, I'm a new thread\n", thrd_id);
    for (int i = 0; i < 3; i++) {
        printf("[t:%08lx] sleeping\n", thrd_id);
        thrd_sleep(&(struct timespec){.tv_sec = 3}, NULL);
    }

    printf("[t:%08lx] exitting\n", thrd_id);
    thrd_exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
    thrd_t threads[NUM_THREADS];

    int i = 0;
    int r = thrd_create(&threads[i], (thrd_start_t)threadEntry1, NULL);
    if (r == thrd_error) {
        fprintf(stderr, "[main] failed in thrd_create, ret:%d\n", r);
        exit(EXIT_FAILURE);
    }
    i++;

    r = thrd_create(&threads[i], (thrd_start_t)threadEntry2, NULL);
    if (r == thrd_error) {
        fprintf(stderr, "[main] failed in thrd_create, ret:%d\n", r);
        exit(EXIT_FAILURE);
    }

    i++;
    r = thrd_create(&threads[i], (thrd_start_t)threadEntry3, NULL);
    if (r == thrd_error) {
        fprintf(stderr, "[main] failed in thrd_create, ret:%d\n", r);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("[main] wainting for thread %d to complete...\n", i);
        thrd_join(threads[i], NULL);
    }

    printf("[main] all done\n");

    thrd_exit(EXIT_SUCCESS);
}
