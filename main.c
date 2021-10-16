#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

jmp_buf buf;

void handler(int sig) {
    printf("handler\n");
    longjmp(buf, 1);
}

int main() {
    int *p = 0;

    signal(SIGSEGV, handler);

    for (int i = 0; i < 10; i++) {
        if (setjmp(buf) == 0) {
            printf("segfault\n");
            *(volatile int *)p;
            printf("should not print\n");
        } else {
            printf("do something else\n");
        }
    }
}