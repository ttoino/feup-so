#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STREAM_SIZE 2048

int identity(int c) { return c; }

int main(int argc, char *argv[]) {
    char opt;
    int (*f)(int) = identity;

    while ((opt = getopt(argc, argv, "ul")) != -1) {
        switch (opt) {
        case 'u':
            f = toupper;
            break;
        case 'l':
            f = tolower;
            break;
        default:
            fprintf(stderr, "Invalid argument!\n");
            return EXIT_FAILURE;
        }
    }

    if (optind > argc) {
        fprintf(stderr, "Requires arguments!\n");
        return EXIT_FAILURE;
    }

    for (int i = optind; i < argc; ++i) {
        FILE *file = fopen(argv[i], "r");
        char stream[STREAM_SIZE];

        if (!file) {
            fprintf(stderr, "File %s not found!\n", argv[i]);
            continue;
        }

        while (!feof(file) && !ferror(file)) {
            int bytes_read = fread(stream, sizeof(char), STREAM_SIZE - 1, file);
            stream[bytes_read] = '\0';

            for (char *c = stream; *c; ++c)
                *c = (unsigned char)f((unsigned int)*c);

            printf("%s", stream);
        }

        fclose(file);
    }

    return EXIT_SUCCESS;
}
