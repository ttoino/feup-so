# Processing Text and Files (using Standard C Library functions)

## 1.

Consider the following program that takes two strings from the command line (`argv[1]` and `argv[2]`) and manipulates them with the string subset of the Standard C Library (`clib`) API.
Compile it and try it.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_SIZE 64

int main(int argc, char* argv[]) {
    char* p1 = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    char* p2 = (char*)malloc(MAX_STR_SIZE * sizeof(char));

    int result = strcmp(argv[1], argv[2]);
    
    if (result == 0)
        printf("the strings are the same\n");
    else if (result < 0)
        printf("%s < %s\n", argv[1], argv[2]);
    else
        printf("%s > %s\n", argv[1], argv[2]);

    strcpy(p1, argv[1]);
    strcpy(p2, argv[2]);
    printf("p1 holds:%s\n", p1);
    printf("p2 holds:%s\n", p2);

    strcat(p1,p2);
    printf("p1 holds:%s\n", p1);

    strcat(p2,p1);
    printf("p2 holds:%s\n", p2);

    return EXIT_SUCCESS;
}
```

Run the command `man 3 string` to see the full set of functions in this API.
Based on this example, write a program that:

- gets a string from the command line and transforms it into an equivalent string but in lowercase;
- gets two strings from the command line and indicates whether the first occurs within the second;
- gets two strings from the command line and indicates how many times the first occurs in the second.

Suggestion: do `man tolower` and `man toupper` to see `clib` functions that may be relevant.

## 2.

Consider the program `naughty.c` that uses the strings API:

```c
#include <stdio.h>
#include <string.h>

int f(char* content) {
    char str[8];
    int result = 2;
    (void)strcpy(str, content);
    return result;
}

int main(int argc, char* argv[]) {
    if (argc == 2)
        printf("result = %d\n", f(argv[1]));
    return EXIT_SUCCESS;
}
```

Compile it and execute it with the following inputs:

```console
$ ./naughty a
$ ./naughty ab
$ ./naughty abc
$ ./naughty abcd
$ ./naughty abcde
$ ./naughty abcdef
$ ./naughty abcdefg
$ ./naughty abcdefgh
$ ./naughty abcdefghi
$ ./naughty abcdefghij
```

How do you explain the results?
Make a drawing of the program's stack to better visualize the problem.
How could you correct the program?

## 3.

Using the subset of the Standard C Library API for file manipulation (e.g., `fopen`, `fclose`, `fseek`, `fread` and `fwrite`), write a program `mycat` that:

- receives as an argument the name of a file and prints its content (similar to the command `cat` with 1 argument);
- receives as arguments the names of several files and prints the contents of all of them, in sequence (similar to the command `cat` with multiple arguments).

```console
$ cat > file1
This is a test
^D
$ cat > file2
Another test
^D
$ cat > file3
And yet another
^D
$ ./mycat file1
This is a test
$ ./mycat file1 file3
This is a test
And yet another
$ ./mycat file1 file2 file3
This is a test
Another test
And yet another
```

## 4.

Create a program `chcase` that receives as arguments the name of a file and an option that sends to the standard output the content of the file as follows:

- with all characters in uppercase if the option is `-u`;
- with all characters in lowercase if the option is `-l`;
- unchanged, if no option is given.

as in the following examples:

```console
$ cat > test.txt
Ads fTsfsdsR DSda BVHGIsdssdeSds
Dfcdfd 45343f rerTEuk
qqfFGfhuymIOu 95r342
^D
$ ./chcase -u test.txt
ADS FTSFSDSR DSDA BVHGISDSSDESDS
DFCDFD 45343F RERTEUK
QQFFGFHUYMIOU 95R342
$ ./chcase -l test.txt
ads ftsfsdsr dsda bvhgisdssdesds
dfcdfd 45343f rerteuk
qqffgfhuymiou 95r342
$ ./chcase test.txt
Ads fTsfsdsR DSda BVHGIsdssdeSds
Dfcdfd 45343f rerTEuk
qqfFGfhuymIOu 95r342
```

## 5.

Write a program that receives the names of two files `file1` and `file2` as arguments and copies the contents of `file1` into `file2`.
If the second file does not exist, it should be created.
If it exists, its contents will be overwritten.
This is the usual semantics of the `cp` command of the Bash shell.

```console
$ cat > file1
This is a test
^D
$ ./mycp file1 file2
$ cat file2
This is a test
$ cat > file3
Another test
^D
$ ./mycp file3 file2
$ cat file2
Another test
```

## 6.

Write a program `mywc` that, given a text file as a command line argument, prints:

- the number of characters in the file, if the option `-c` is used;
- the number of words in the file, if the option `-w` is used;
- the number of lines in the file, if the option `-l` is used;
- the number of characters, if no option is given.

```console
$ cat > file.txt
This is a test
^D
$ ./mywc -c file.txt
15
$ ./mywc -w file.txt
4
$ ./mywc -l file.txt
1
$ ./mywc file.txt
15
```

Compare your program to the shell command `wc`.

## 7.

Write a program `mygrep` that, given a string and a file from the command line, prints all occurrences of the string in the file, indicating the line and column where these begin.
The output would look something like:

```console
$ ./mygrep needle haystack.txt
[2:17]
[5:2]
[23:7]
```
