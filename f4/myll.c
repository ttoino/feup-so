#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <memory.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void print_file(char *full_name, char *fname) {
    struct stat st;

    if (lstat(full_name, &st) == -1) {
        perror("lstat");
        return;
    }

    // FIRST MODE CHARACTER
    if (S_ISREG(st.st_mode))
        putchar('-');
    else if (S_ISDIR(st.st_mode))
        putchar('d');
    else if (S_ISCHR(st.st_mode))
        putchar('c');
    else if (S_ISBLK(st.st_mode))
        putchar('b');
    else if (S_ISFIFO(st.st_mode))
        putchar('f');
    else if (S_ISLNK(st.st_mode))
        putchar('l');
    else if (S_ISSOCK(st.st_mode))
        putchar('s');

    // OWNER PERMISSIONS
    putchar(st.st_mode & S_IRUSR ? 'r' : '-');
    putchar(st.st_mode & S_IWUSR ? 'w' : '-');
    mode_t sp = st.st_mode & S_ISUID;
    putchar(st.st_mode & S_IXUSR ? (sp ? 's' : 'x') : (sp ? 'S' : '-'));

    // GROUP PERMISSIONS
    putchar(st.st_mode & S_IRGRP ? 'r' : '-');
    putchar(st.st_mode & S_IWGRP ? 'w' : '-');
    sp = st.st_mode & S_ISGID;
    putchar(st.st_mode & S_IXGRP ? (sp ? 's' : 'x') : (sp ? 'S' : '-'));

    // OTHER PERMISSIONS
    putchar(st.st_mode & S_IROTH ? 'r' : '-');
    putchar(st.st_mode & S_IWOTH ? 'w' : '-');
    sp = st.st_mode & S_ISVTX;
    putchar(st.st_mode & S_IXOTH ? (sp ? 't' : 'x') : (sp ? 'T' : '-'));

    // NUMBER OF LINKS
    printf(" %lu\t", st.st_nlink);

    // OWNER AND GROUP
    struct passwd *owner = getpwuid(st.st_uid);
    if (owner)
        printf("%s\t", owner->pw_name);
    else
        printf("%u\t", st.st_uid);

    struct group *group = getgrgid(st.st_gid);
    if (group)
        printf("%s\t", group->gr_name);
    else
        printf("%u\t", st.st_gid);

    // SIZE
    printf("%lu\t", st.st_size);

    // MODIFICATION DATE
    char tm[18];
    strftime(tm, 18, "%Y %b %e %H:%M", localtime((time_t *)&st.st_mtim));
    printf("%s ", tm);

    // FILE NAME
    if (S_ISLNK(st.st_mode)) {
        ssize_t buf_size = st.st_size + 1;

        if (st.st_size == 0)
            buf_size = PATH_MAX;

        char *real_path = calloc(sizeof(1), buf_size);

        if (!real_path) {
            printf("%s\n", fname);
            perror("malloc");
            return;
        }

        ssize_t n_bytes = readlink(full_name, real_path, buf_size);

        if (n_bytes == -1) {
            printf("%s\n", fname);
            perror("readlink");
            return;
        }

        printf("%s -> %.*s\n", fname, (int)n_bytes, real_path);
        free(real_path);
    } else {
        printf("%s\n", fname);
    }
}

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     fprintf(stderr, "usage: %s file...\n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    for (int i = 0; i < argc; ++i) {
        if (i > 1)
            printf("\n");

        char *fname = argv[i];
        DIR *dir;

        if (i == 0) {
            if (argc == 1)
                fname = ".";
            else
                continue;
        }

        if (!(dir = opendir(fname))) {
            if (errno == ENOTDIR) {
                // It's a file
                char *file_name = strrchr(fname, '/');
                if (file_name)
                    ++file_name;
                else
                    file_name = fname;

                print_file(fname, file_name);
                continue;
            }

            perror("readdir");
            continue;
        }

        if (argc > 2)
            printf("%s\n", fname);

        struct dirent **files;

        int n = scandir(fname, &files, NULL, alphasort);

        if (n == -1) {
            perror("scandir");
            continue;
        }

        for (int j = 0; j < n; ++j) {
            struct dirent *f = files[j];

            if (f->d_name[0] != '.') {
                size_t fname_len = strlen(fname);
                size_t name_len = strlen(f->d_name);

                char *full_name =
                    calloc(sizeof(char), fname_len + name_len + 2);

                if (!full_name) {
                    perror("malloc");
                    continue;
                }

                memcpy(full_name, fname, fname_len);
                if (full_name[fname_len - 1] != '/')
                    full_name[fname_len] = '/';
                strncat(full_name, f->d_name, name_len);

                print_file(full_name, f->d_name);

                free(full_name);
            }

            free(f);
        }
        free(files);

        closedir(dir);
    }

    return EXIT_SUCCESS;
}
