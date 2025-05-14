#include <stdio.h>

int n, a[30], cnt = 0;

void dfs(int start, int remain, int index) {
    if (remain == 0) {
        printf("%d=%d", n, a[0]);
        for (int i = 1; i < index; i++) {
            printf("+%d", a[i]);
        }
        cnt++;
        if (cnt % 4 == 0 || a[0] == n)
            printf("\n");
        else
            printf(";");
        return;
    }
    
    for (int i = start; i <= remain; i++) {
        a[index] = i;
        dfs(i, remain - i, index + 1);
    }
}

int main() {
    scanf("%d", &n);
    dfs(1, n, 0);
    return 0;
}
