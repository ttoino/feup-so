#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat info;

    if (argc < 2) {
        fprintf(stderr, "usage: %s file...\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        char *fname = argv[i];

        if (lstat(fname, &info) == -1) {
            fprintf(stderr, "fsize: Can't stat %s\n", fname);
            return EXIT_FAILURE;
        }

        printf("%s size: %d bytes\tdisk_blocks: %d\towner id: %d\tmodified at: "
               "%s",
               fname, (int)info.st_size, (int)info.st_blocks, (int)info.st_uid,
               ctime((time_t *)&info.st_mtim));
    }

    return EXIT_SUCCESS;
}
