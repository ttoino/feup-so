#include <errno.h>
#include <fcntl.h>
#include <memory.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// 6.
char **getArgs(char *str) {
    size_t n = 1;
    char **args = calloc(n, sizeof(char *));

    while (1) {
        if (str == NULL || *str == '\0') {
            args[n - 1] = NULL;
            return args;
        }

        // skip spaces and tabs in the beginning of arguments
        for (; *str == ' ' || *str == '\t'; ++str)
            ;

        args = reallocarray(args, ++n, sizeof(char *));
        args[n - 2] = str;

        // Replace next space or tab with a null byte
        for (; *str != '\0' && *str != ' ' && *str != '\t'; ++str) {
            // Remove '\' and skip the next character
            if (*str == '\\')
                for (char *s = str; *s != '\0'; ++s)
                    *s = *(s + 1);

            // Keep everything between single quotes as is
            else if (*str == '\'') {
                for (; *str != '\0'; ++str) {
                    *str = *(str + 1);

                    if (*str == '\'') {
                        for (char *s = str; *s != '\0'; ++s)
                            *s = *(s + 2);
                        break;
                    }
                }

                // Handle quotes that weren't closed
                if (*str == '\0')
                    --str;
            }
        }

        *str++ = '\0';
    }

    return args;
}

// 7.
#define HISTORY_FILE ".myhistory"

int main(int argc, char *argv[]) {
    char buf[1024];
    char *command;
    pid_t pid;

    // 7.
    FILE *history_file = fopen(HISTORY_FILE, "a");

    /* do this until you get a ^C or a ^D */
    while (1) {
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "$ ");
        if ((command = fgets(buf, sizeof(buf), stdin)) == NULL)
            break;

        // 7.
        fwrite(command, sizeof(char), strlen(buf), history_file);
        fflush(history_file);

        command[strlen(buf) - 1] = '\0';

        /* call fork and check return value */
        if ((pid = fork()) == -1) {
            fprintf(stderr, "%s: can't fork command: %s\n", argv[0],
                    strerror(errno));
            continue;
        } else if (pid == 0) {
            // 6.
            char **args = getArgs(command);

            // 7.
            if (strcmp(args[0], "myhistory") == 0) {
                if (args[1]) {
                    errno = 0;
                    char *endptr;
                    strtoul(args[1], &endptr, 0);
                    if (errno != 0 || *endptr != '\0')
                        goto NO_ARGS;

                    if (execlp("tail", "tail", "-n", args[1], HISTORY_FILE,
                               NULL) == -1)
                        goto EXEC_ERROR;
                }

            NO_ARGS:
                if (execlp("cat", "cat", HISTORY_FILE, NULL) == -1)
                    goto EXEC_ERROR;
            }

            // 8.
            if (strcmp(args[0], "exit") == 0) {
                pid_t ppid = getppid();

                kill(ppid, SIGINT);
                exit(EXIT_SUCCESS);
            }

            /* child */
            execvp(args[0], args);
        /* if I get here "execlp" failed */
        EXEC_ERROR:
            fprintf(stderr, "%s: couldn't exec %s: %s\n", argv[0], buf,
                    strerror(errno));
            /* terminate with error to be caught by parent */
            exit(EXIT_FAILURE);
        }

        /* shell waits for command to finish before giving prompt again */
        if ((pid = waitpid(pid, NULL, 0)) < 0)
            fprintf(stderr, "%s: waitpid error: %s\n", argv[0],
                    strerror(errno));
    }

    exit(EXIT_SUCCESS);
}
