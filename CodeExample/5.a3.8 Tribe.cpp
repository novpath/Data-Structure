#include <cstdio>
#define SIZE 10001
int S[SIZE];

void Union(int S[], int Root1, int Root2)
{
    if (Root1 == Root2) return;
    if (Root2 > Root1) {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    } else {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

int Find(int S[], int x)
{
    int root = x;
    while (S[root] >= 0)
        root = S[root];
    while (x != root) {
        int t = S[x];
        S[x] = root;
        x = t;
    }
    return root;
}

void InitSet(int S[])
{
    for (int i = 0; i < SIZE; i++)
        S[i] = -1;
}

int main()
{
    int n, k, maxId = 0;
    int a, b, i, t = -1;
    InitSet(S);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &a);
            if (maxId < a)
                maxId = a;
            if (j != 0)
                Union(S, Find(S, t), Find(S, a - 1));
            t = a - 1;
        }
    }
    int tribeNum = 0;
    for (i = 0; i < maxId; i++) {
        if (S[i] < 0)
            tribeNum++;
    }
    printf("%d %d\n", maxId, tribeNum);
    int q;
    scanf("%d", &q);
    for (i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        if (Find(S, a - 1) == Find(S, b - 1))
            printf("Y\n");
        else
            printf("N\n");
    }

    return 0;
}
