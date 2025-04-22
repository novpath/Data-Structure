#include <stdio.h>

int main()
{
    int A1, A2;
    double A3;
    int n, cnt;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    A1 = A2 = A3 = cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 3 == 0 && a[i] > A1) {
            A1 = a[i];
        } else if (a[i] % 3 == 1) {
            A2++;
        } else if (a[i] % 3 == 2) {
            A3 += a[i];
            cnt++;
        }
    }
    if (cnt != 0)
        A3 = A3 / cnt;

    if (A1 == 0)
        printf("NONE ");
    else
        printf("%d ", A1);
    if (A2 == 0)
        printf("NONE ");
    else
        printf("%d ", A2);
    if (A3 == 0)
        printf("NONE");
    else
        printf("%.1f\n", A3);
    
    return 0;
}
