#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void handler1() { printf("Received SIGUSR1\n"); }

static void handler2() { printf("Received SIGUSR2\n"); }

static void handler3() { printf("Received SIGHUP\n"); }

static void handler4() { printf("Received SIGTSTP\n"); }

static void handler5() { printf("Received SIGINT\n"); }

static void handler6() { printf("Received SIGKILL\n"); }

static void handler7() { printf("Received SIGTERM\n"); }

int main(int argc, char *argv[]) {
    printf("My PID is %d\n", getpid());
    if (signal(SIGUSR1, handler1) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGUSR1: %s\n", strerror(errno));

    if (signal(SIGUSR2, handler2) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGUSR2: %s\n", strerror(errno));

    if (signal(SIGHUP, handler3) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGHUP: %s\n", strerror(errno));

    if (signal(SIGTSTP, handler4) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGTSTP: %s\n", strerror(errno));

    if (signal(SIGINT, handler5) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGINT: %s\n", strerror(errno));

    if (signal(SIGKILL, handler6) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGKILL: %s\n", strerror(errno));

    if (signal(SIGTERM, handler7) == SIG_ERR)
        fprintf(stderr, "Can't catch SIGTERM: %s\n", strerror(errno));

    /* stick around ... */
    for (;;)
        pause();
}
