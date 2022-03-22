#include <stdio.h>
#include <stdlib.h>

#define STREAM_SIZE 2048

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Requires arguments!\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        FILE *file = fopen(argv[i], "r");
        char stream[STREAM_SIZE];

        if (!file) {
            fprintf(stderr, "File %s not found!\n", argv[i]);
            continue;
        }

        while (!feof(file) && !ferror(file)) {
            int bytes_read = fread(stream, sizeof(char), STREAM_SIZE - 1, file);
            stream[bytes_read] = '\0';
            printf("%s", stream);
        }

        fclose(file);
    }

    return EXIT_SUCCESS;
}
