#include <stdio.h>

int main() {
    int D, P;
    scanf("%d %d", &D, &P);
    if (P == 3)
        printf("%d\n", D - 1);
    else
        printf("%d\n", D - P / 2 - 1);
    return 0;
}

