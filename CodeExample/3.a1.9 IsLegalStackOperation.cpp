#include <stdio.h>

void IsLegalStackOperation(const char a[], int m)
{
    int num_I = 0, num_O = 0;
    int i = 0, flag = 1;
    while (a[i] != '\0') {
        if (a[i] == 'S')
            num_I++;
        else if (a[i] == 'X') {
            num_O++;
            if (num_O > num_I || num_O > m) {
                flag = 0;
                break;
            }
        }
        i++;
    }
    if (num_I != num_O)
        flag = 0;

    if (flag)
        printf("YES\n");
    else
        printf("NO\n");
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        char str[100];
        scanf("%s", str);
        IsLegalStackOperation(str, m);
    }

    return 0;
}