#include <stdio.h>
#include <stdlib.h>

#define STREAM_SIZE 2048

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Requires two arguments!\n");
        return EXIT_FAILURE;
    }

    FILE *from = fopen(argv[1], "r");
    FILE *to = fopen(argv[2], "w");
    char stream[STREAM_SIZE];

    if (!from) {
        fprintf(stderr, "File %s not found!\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (!to) {
        fprintf(stderr, "File %s not found!\n", argv[2]);
        return EXIT_FAILURE;
    }

    while (!feof(from) && !ferror(from)) {
        int bytes_read = fread(stream, sizeof(char), STREAM_SIZE - 1, from);
        stream[bytes_read] = '\0';
        fprintf(to, "%s", stream);
    }

    fclose(from);
    fclose(to);

    return EXIT_SUCCESS;
}
