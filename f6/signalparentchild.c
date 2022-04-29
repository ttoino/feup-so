#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

size_t signal_count = 0;

static void handler() {
    printf("%d: Received %lu signal(s)\n", getpid(), ++signal_count);
}

int main(int argc, char *argv[]) {
    pid_t pid;

    if (signal(SIGUSR1, handler) == SIG_ERR) {
        fprintf(stderr, "Error creating signal handler in parent!\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Error creating child process!\n");
        exit(EXIT_FAILURE);

    } else if (pid > 0) {
        kill(pid, SIGUSR1);

        waitpid(pid, NULL, 0);

    } else {
        kill(getppid(), SIGUSR1);
        sleep(1);
        kill(getppid(), SIGUSR1);
        sleep(1);
        kill(getppid(), SIGUSR1);
    }
}
