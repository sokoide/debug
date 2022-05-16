#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

void* threadEntry1(void* dummy);
void foo(int i);

void* threadEntry1(void* dummy) {
    uint64_t thrd_id = thrd_current();
    printf("[t:%08lx] Hello, I'm a new thread\n", thrd_id);

    for (int i = 0; i < 100000; i++) {
        foo(i);
    }

    thrd_exit(EXIT_SUCCESS);
}

void foo(int i) {
    char c[16];
    c[i] = i;
}

int main(int argc, char** argv) {
    thrd_t t;

    int r = thrd_create(&t, (thrd_start_t)threadEntry1, NULL);
    if (r == thrd_error) {
        fprintf(stderr, "[main] failed in thrd_create, ret:%d\n", r);
        exit(EXIT_FAILURE);
    }

    thrd_join(t, NULL);

    printf("[main] all done\n");

    thrd_exit(EXIT_SUCCESS);
}
