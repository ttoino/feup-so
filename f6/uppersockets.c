#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define CHANNEL0 0
#define CHANNEL1 1

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Requires exactly one argument!\n");
        return EXIT_FAILURE;
    }

    int sockets[2];
    char buf[1024];
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
        perror("opening stream socket pair");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        return EXIT_FAILURE;

    } else if (pid == 0) {
        /* this is the child */
        close(sockets[CHANNEL0]);

        int bytes_read;
        do {
            bytes_read = read(sockets[CHANNEL1], buf, sizeof(buf));

            for (int i = 0; i < bytes_read; ++i)
                buf[i] = toupper(buf[i]);

            /* write message from parent */
            write(sockets[CHANNEL1], buf, bytes_read);
        } while (bytes_read > 0);

        printf("Child exited\n");

        close(sockets[CHANNEL1]);

        /* leave gracefully */
        return EXIT_SUCCESS;

    } else {
        /* this is the parent */
        close(sockets[CHANNEL1]);

        FILE *file = fopen(argv[1], "r");

        if (!file)
            fprintf(stderr, "File %s not found!\n", argv[1]);

        while (!feof(file) && !ferror(file)) {
            int bytes_read = fread(buf, sizeof(char), sizeof(buf), file);

            if (write(sockets[CHANNEL0], buf, bytes_read) < 0)
                perror("writing stream message");
        }

        fclose(file);

        int bytes_read;
        do {
            bytes_read = read(sockets[CHANNEL0], buf, sizeof(buf));

            /* write message from parent */
            write(STDOUT_FILENO, buf, bytes_read);
        } while (bytes_read > 0);

        printf("Parent exited\n");

        close(sockets[CHANNEL0]);

        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0) {
            perror("did not catch child exiting");
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
}
