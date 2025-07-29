#include <cstdio>

#define NULL nullptr

bool IsMinHeap(int A[], int k, int len)
{
    if (k >= len) return true;          // 当前节点超出有效范围时返回true（空子树）

    int left = 2 * k;                   // 左子节点下标
    int right = 2 * k + 1;              // 右子节点下标

    if (left < len) {                   // 检查左子树
        if (A[k] > A[left])             // 验证父节点 <= 左子节点
            return false;
        if (!IsMinHeap(A, left, len)) // 递归检查左子树，若失败则返回
            return false;
    }

    if (right < len) {                   // 检查右子树
        if (A[k] > A[right])             // 验证父节点 <= 右子节点
            return false;
        if (!IsMinHeap(A, right, len)) // 递归检查右子树，若失败则返回
            return false;
    }
    return true;
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    printf("%s", IsMinHeap(A, 1, n) ? "Yes" : "No");

    return 0;
}
