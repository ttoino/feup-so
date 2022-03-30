#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s file...\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        close(open(argv[i], O_CREAT, 0644));
        utime(argv[i], NULL);
    }

    return EXIT_SUCCESS;
}
