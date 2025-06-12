#include <cstdio>

#define MAXN 10001
#define MINH (-10001)

int H[MAXN], size;

void Create()
{
    size = 0;
    H[0] = MINH;    // 设置“岗哨”
}

void Insert(int x)
{
    if (size == MAXN)
        return;
    int i;
    for (i = ++size; H[i / 2] > x; i /= 2)
        H[i] = H[i / 2];
    H[i] = x;
}

int Delete(int H[])
{
    if (size == 0)
        return H[0];

    int minItem = H[1];
    int lastItem = H[size--];
    int parent, child;
    for (parent = 1; parent * 2 <= size; parent = child) {
        child = parent * 2;

        if (child != size && H[child + 1] < H[child]) {
            child++;
        }

        if (lastItem <= H[child]) break;
        H[parent] = H[child];
    }
    H[parent] = lastItem;

    return minItem;
}

int main()
{
    int n, x;
    scanf("%d", &n);
    Create();
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        Insert(x);
    }
    int cost = 0;
    while (size >= 2) {
        int a = Delete(H), b = Delete(H);
        cost += a + b;
        Insert(a + b);
    }
    printf("%d\n", cost);

    return 0;
}
