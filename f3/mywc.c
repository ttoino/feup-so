#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STREAM_SIZE 2048

int main(int argc, char *argv[]) {
    char opt;
    bool all = true;
    char sep = '\0';

    while ((opt = getopt(argc, argv, "cwl")) != -1) {
        switch (opt) {
        case 'c':
            all = true;
            break;
        case 'w':
            all = false;
            sep = ' ';
            break;
        case 'l':
            all = false;
            sep = '\n';
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
        int wc = sep == ' ';

        if (!file) {
            fprintf(stderr, "File %s not found!\n", argv[i]);
            continue;
        }

        while (!feof(file) && !ferror(file)) {
            int bytes_read = fread(stream, sizeof(char), STREAM_SIZE - 1, file);

            if (all) {
                wc += bytes_read;
                continue;
            }

            stream[bytes_read] = '\0';

            for (char *c = stream; *c; ++c)
                wc += *c == sep;
        }

        printf("%d\n", wc);
        fclose(file);
    }

    return EXIT_SUCCESS;
}
