#include <stdio.h>

int main() {
    int i, j, *p, *q;
    i = 5;
    printf("i=%d\n", i);
    p = &i;
    printf("i=%d, p=%p\n", i, p);
    *p = 7;
    printf("i=%d, p=%p\n", i, p);
    j = 3;
    printf("i=%d, j=%d, p=%p\n", i, j, p);
    p = &j;
    printf("i=%d, j=%d, p=%p\n", i, j, p);
    q = p;
    printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);
    p = &i;
    printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);
    *q = 2;
    printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);
    return 0;
}
