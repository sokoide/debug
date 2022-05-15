#include <stdio.h>

void foo(char* name);
int bar(int a, int b);
int baz(int c);

void foo(char* name) { printf("name: %s\n", name); }

int bar(int a, int b) {
    int r = baz(a + b);
    return r;
}

int baz(int c) { return c * 10; }

int main(int argc, char** argv) {
    foo(argv[0]);
    printf("bar: %d\n", bar(40, 2));

    return 0;
}
