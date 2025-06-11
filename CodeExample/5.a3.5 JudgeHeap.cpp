#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MINH (-10001)

int *H;
int size, n, m;

void Create()
{
    size = 0;
    H[0] = MINH;    // 设置“岗哨”
}

void Insert(int x, int maxsize)
{
    if (size == maxsize)
        return;
    int i;
    for (i = ++size; H[i / 2] > x; i /= 2)
        H[i] = H[i / 2];
    H[i] = x;
}

int FindNode(const int x)
{
    for (int i = 1; i <= n; i++) {
        if (H[i] == x)
            return i;
    }
    return -1;
}

bool IsRoot(int x)
{
    return (FindNode(x) == 1);
}

bool IsSiblings(int x, int y)
{
    return (FindNode(x) / 2 == FindNode(y) / 2);
}

bool IsParent(int x, int y)
{
    return (FindNode(y) / 2 == FindNode(x));
}

bool IsChild(int x, int y)
{
    return (FindNode(x) / 2 == FindNode(y));
}

int main()
{
    int x, y;
    scanf("%d %d", &n, &m);
    H = (int *) malloc((n + 1) * sizeof(int));
    if (n <= 0 || H == nullptr)
        return -1;
    Create();
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        Insert(x, n);
    }

    for (int i = 0; i < m; i++) {
        char line[100];
        scanf(" %99[^\n]", line);

        if (strstr(line, "root")) {
            sscanf(line, "%d is the root", &x);
            IsRoot(x) ? printf("T\n") : printf("F\n");
        } else if (strstr(line, "siblings")) {
            sscanf(line, "%d and %d are siblings", &x, &y);
            IsSiblings(x, y) ? printf("T\n") : printf("F\n");
        } else if (strstr(line, "parent")) {
            sscanf(line, "%d is the parent of %d", &x, &y);
            IsParent(x, y) ? printf("T\n") : printf("F\n");
        } else if (strstr(line, "child")) {
            sscanf(line, "%d is a child of %d", &x, &y);
            IsChild(x, y) ? printf("T\n") : printf("F\n");
        }
    }

    free(H);
    return 0;
}
