#include <sys/stat.h>
#include <sys/types.h>
/* ... */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s perms file\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;

    errno = 0;
    long perms = strtol(argv[1], &endptr, 8);

    if (errno) {
        perror("strtol");
        return EXIT_FAILURE;
    }

    if (*endptr || perms < 0 || perms > 0777) {
        fprintf(stderr, "%s: illegal permission value\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (chmod(argv[2], perms) == -1) {
        fprintf(stderr, "%s: cannot chmod %s\n", argv[0], argv[2]);
        return EXIT_FAILURE;
    }

    /* ... */
}
