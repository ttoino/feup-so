# Process Management (using the Kernel API)

## 1.

Consider the following program that calls the function `fork()` multiple times.
Compile it and run it.
How many processes, including the parent process, are created?
Why?

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    /* fork a child process */
    fork();

    /* fork another child process */
    fork();

    /* and fork another */
    fork();

    return EXIT_SUCCESS;
}
```

Check your guess by changing the program in such a way that all processes print their
process ids (`pid`).
Check the function `getpid()`.

<details>
    <summary>Answer</summary>

Eight processes.
When the program is first ran there is only one process.
After the first `fork`, which is only called by one process, there are two.
The second `fork` is called by both processes, generating two more.
The third `fork` is called by all four processes, so we end up with eight.
</details>

## 2.

Consider still this other program that also calls `fork()` repeatedly.
Compile it and run it.
How many processes, including the parent process, are created?
Why?

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < 4; i++)
        fork();
    return EXIT_SUCCESS;
}
```

Again, check your guess by changing the program in such a way that all processes print their process ids.

<details>
    <summary>Answer</summary>

Sixteen processes.
The amount of processes is doubled each iteration of the loop.
There are four iterations and we start with one process, so 1×2×2×2×2 = 2⁴ = 16.
</details>

## 3.

Consider now the following program that, when executed, creates a child process.
How do you explain the value of variable `value` in the parent and child processes?
Hint: make a drawing of their respective address spaces as the parent runs and the `fork()` is executed.
What happens to the variable then?

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    int value = 0;

    if ((pid = fork()) == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        /* child process */
        value = 1;
        printf("CHILD: value = %d, addr = %p\n", value, &value);
        return EXIT_SUCCESS;
    }
    else {
        /* parent process */
        if (waitpid(pid, NULL, 0) == -1) {
            perror("wait");
            return EXIT_FAILURE;
        }
        printf("PARENT: value = %d, addr = %p\n", value, &value);
        return EXIT_SUCCESS;
    }
}
```

Observe the values and addresses of the variable `value` printed by the parent and child processes.
Can you explain the results?

<details>
    <summary>Answer</summary>

```console
$ ./3.out
CHILD: value = 1, addr = 0x7fffc94058f0
PARENT: value = 0, addr = 0x7fffc94058f0
```

The variables from the parent process are copied to the child process when `fork` is called, but these variables will then refer to different places in memory in different processes.
So when `value` is changed in the child process, it is not changed in the parent process.

The printed addresses seem to be the same because these addresses are virtual and point to the same value within one process' addressable space, but not to the same value in physical memory.
</details>

## 4.

Consider the following program that, when executed, creates a child process that then executes a command provided in its command line arguments.
Compile it and run it.
Pay close attention to the code and understand how it works.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid;

    /* fork a child process */
    if ((pid = fork()) == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        /* child process */
        if (execlp(argv[1],argv[1],NULL) == -1) {
            perror("execlp");
            return EXIT_FAILURE;
        }
    } else {
        /* parent process */
        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid");
            return EXIT_FAILURE;
        }
        printf("child exited\n");
    }
    return EXIT_SUCCESS;
}
```

If the function `execlp` executes successfully, how does the child process signal its end to the parent process?

<details>
    <summary>Answer</summary>

`execlp` will replace all the code from the child process to whatever executable the user specifies, so when the `main` function of that process returns the process terminates and the parent is notified via the `wait` function.
</details>

## 5.

The following program implements a very simple command line shell.
Compile it and run it.
Pay close attention to the code and understand how it works.

```c
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char buf[1024];
    char* command;
    pid_t pid;

    /* do this until you get a ^C or a ^D */
    for( ; ; ) {
        /* give prompt, read command and null terminate it */
        fprintf(stdout, "$ ");
        if((command = fgets(buf, sizeof(buf), stdin)) == NULL)
            break;
        command[strlen(buf) - 1] = '\0';

        /* call fork and check return value */
        if((pid = fork()) == -1) {
            fprintf(stderr, "%s: can't fork command: %s\n",
                    argv[0], strerror(errno));
            continue;
        } else if(pid == 0) {
            /* child */
            execlp(command, command, (char *)0);
            /* if I get here "execlp" failed */
            fprintf(stderr, "%s: couldn't exec %s: %s\n",
                    argv[0], buf, strerror(errno));
            /* terminate with error to be caught by parent */
            exit(EXIT_FAILURE);
        }

        /* shell waits for command to finish before giving prompt again */
        if ((pid = waitpid(pid, NULL, 0)) < 0)
            fprintf(stderr, "%s: waitpid error: %s\n",
                    argv[0], strerror(errno));
    }
    exit(EXIT_SUCCESS);
}
```

Note the alternative use (with respect to the function `perror()`) of the function `strerror()` to understand why the system call failed.
The later function returns a string with the error description associated with the number in the variable `errno`.
The value of the variable `errno` is set by the kernel before returning from the failed system call with a value of `-1`.
The string returned by `strerror()` can be included in richer error messages using, for example, buffered and formatted I/O functions such as `fprintf()`.

Why can't you execute commands with arguments, such as `ls -l` ou `uname -n` with this code?

<details>
    <summary>Answer</summary>

Because the `exec` family of functions interpret the first argument as a path to the executable that will be called.
Command line arguments must be passed in through other function arguments, one at a time.
</details>

## 6.

Change the previous program so that the commands can be executed with arguments.
Hint: check the manual pages for `exec` and its numerous variants.
Some of these receive, besides the command name, a variable number of arguments read from the shell.
You can gather these arguments using, for example, the function `strtok` from the Standard C Library.

## 7.

Change the previous program so that it keeps a history of all commands it executed.
Implement a command `myhistory` that gets an integer `n` and prints the last `n` commands executed by the shell.
Hint: you may use the usual `fork()-exec()` sequence, as in all the other shell commands; check the Bash shell command `tail` (you have seen it in the [first set of exercises](/f0/)).

## 8.

Finally, change the program again to implement a command `exit` that terminates the shell.
