#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

void run_command(int in, int out, char **command) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Error creating child process!\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);

        if (execvp(command[0], command) < 0) {
            fprintf(stderr, "Error running %s!\n", command[0]);
            exit(EXIT_FAILURE);
        }
    }

    close(in);
    close(out);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Requires an argument!\n");
        exit(EXIT_FAILURE);
    }

    size_t command_index = 0;

    char *cmd_str = NULL, *cmd_save = NULL, *token = NULL, *token_save = NULL;

    int old_pipe[2], curr_pipe[2];

    cmd_str = strtok_r(argv[1], "|", &cmd_save);

    char **command = NULL;

    while (cmd_str != NULL) {
        old_pipe[0] = curr_pipe[0];
        old_pipe[1] = curr_pipe[1];

        if (command) {
            if (pipe(curr_pipe) < 0) {
                fprintf(stderr, "Error creating pipe!\n");
                exit(EXIT_FAILURE);
            }

            if (command_index == 1)
                run_command(STDIN_FILENO, curr_pipe[WRITE_END], command);
            else
                run_command(old_pipe[READ_END], curr_pipe[WRITE_END], command);

            free(command);
        }

        size_t command_len = 0;
        command = calloc(1, sizeof(char *));
        token = strtok_r(cmd_str, " ", &token_save);

        while (token != NULL) {
            command[command_len] = token;
            command = reallocarray(command, ++command_len + 1, sizeof(char *));

            token = strtok_r(NULL, " ", &token_save);
        }
        command[command_len] = NULL;

        ++command_index;
        cmd_str = strtok_r(NULL, "|", &cmd_save);
    }

    if (command) {
        if (command_index == 1)
            run_command(STDIN_FILENO, STDOUT_FILENO, command);
        else
            run_command(curr_pipe[READ_END], STDOUT_FILENO, command);

        free(command);

        for (size_t i = 0; i < command_index; ++i)
            wait(NULL);
    }
}
