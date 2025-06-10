#include <cstdio>

#define null '-'
#define MaxSize 1024

struct BiTNode {
    int lchild;
    int rchild;
} T[MaxSize];

typedef int TreeId;
typedef char ElementType;
TreeId BuildTree(BiTNode T[], int n);
void PrintLeafNodes(TreeId root, int n);

int main()
{
    int n;
    scanf("%d", &n);
    TreeId R = BuildTree(T, n);
    PrintLeafNodes(R, n);
    return 0;
}

TreeId BuildTree(BiTNode T[], int n)
{
    TreeId root = null;
    ElementType cl, cr;
    if (n) {
        int i;
        int check[n];
        for (i = 0; i < n; i++)
            check[i] = 0;
        for (i = 0; i < n; i++) {
            scanf(" %c %c", &cl, &cr);
            if (cl != null) {
                T[i].lchild = cl - '0';
                check[T[i].lchild] = 1;
            } else {
                T[i].lchild = null;
            }
            if (cr != null) {
                T[i].rchild = cr - '0';
                check[T[i].rchild] = 1;
            } else {
                T[i].rchild = null;
            }
        }
        for (i = 0; i < n; i++)
            if (!check[i]) break;
        root = i;
    }
    return root;
}

void PrintLeafNodes(TreeId root, int n)
{
    int Q[MaxSize];
    int front = 0, rear = 0;
    Q[rear++] = root;
    int first = 1;
    while (front != rear) {
        int current = Q[front++];
        if (T[current].lchild == null && T[current].rchild == null) {
            if (first) {
                printf("%d", current);
                first = 0;
            } else {
                printf(" %d", current);
            }
        }
        if (T[current].lchild != null) {
            Q[rear++] = T[current].lchild;
        }
        if (T[current].rchild != null) {
            Q[rear++] = T[current].rchild;
        }
    }
}
