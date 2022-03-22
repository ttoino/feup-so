#include <stdio.h>
#include <stdlib.h>

#define STREAM_SIZE 2048

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Requires two arguments!\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[2], "r");
    char stream[STREAM_SIZE];
    char *needle = argv[1];
    int a = 0, x = 1, y = 1, px = 1, py = 1;

    if (!file) {
        fprintf(stderr, "File %s not found!\n", argv[2]);
        return EXIT_FAILURE;
    }

    while (!feof(file) && !ferror(file)) {
        int bytes_read = fread(stream, sizeof(char), STREAM_SIZE - 1, file);
        stream[bytes_read] = '\0';

        for (char *c = stream; *c; ++c, ++x) {
            if (*c == '\n') {
                ++y;
                x = 0;
            }

            if (needle[a] == '\0') {
                a = 0;
                printf("[%d:%d]\n", py, px);
            }

            if (a == 0) {
                px = x;
                py = y;
            }

            if (needle[a] == *c)
                ++a;
            else
                a = 0;
        }
    }

    if (needle[a] == '\0') {
        a = 0;
        printf("[%d:%d]\n", py, px);
    }

    fclose(file);

    return EXIT_SUCCESS;
}
