#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

#define LINESIZE 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Requires exactly one argument!\n");
        return EXIT_FAILURE;
    }

    int fd[2];
    pid_t pid;
    char line[LINESIZE];

    if (pipe(fd) < 0) {
        perror("pipe error");

        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        perror("fork error");

        exit(EXIT_FAILURE);

    } else if (pid > 0) {
        /* parent */
        close(fd[READ_END]);

        FILE *file = fopen(argv[1], "r");

        if (!file)
            fprintf(stderr, "File %s not found!\n", argv[1]);

        while (!feof(file) && !ferror(file)) {
            int bytes_read = fread(line, sizeof(char), LINESIZE, file);

            if (write(fd[WRITE_END], line, bytes_read) < 0)
                fprintf(stderr, "Unable to write to pipe: %s\n",
                        strerror(errno));
        }

        fclose(file);

        close(fd[WRITE_END]);

        /* wait for child and exit */
        if (waitpid(pid, NULL, 0) < 0)
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));

        exit(EXIT_SUCCESS);

    } else {
        /* child */
        close(fd[WRITE_END]);

        int bytes_read;
        do {
            bytes_read = read(fd[READ_END], line, LINESIZE);

            /* write message from parent */
            write(STDOUT_FILENO, line, bytes_read);
        } while (bytes_read > 0);

        close(fd[READ_END]);

        /* exit gracefully */
        exit(EXIT_SUCCESS);
    }
}
