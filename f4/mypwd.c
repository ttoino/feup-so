#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);

    return EXIT_SUCCESS;
}
