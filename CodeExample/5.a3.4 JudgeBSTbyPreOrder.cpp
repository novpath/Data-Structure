#include <cstdio>

bool JudgeBSTbyPreOrder(int pre[], int l1, int h1, int post[], int l2, int h2, bool isMirror)
{
    if (l1 > h1) return true;
    int root = pre[l1];
    post[h2] = root;                            // 根节点放在后序最后位置
    if (l1 == h1) return true;                  // 单节点情况
    int i = l1 + 1;
    if (!isMirror) {                            // 根据模式划分左右子树边界
        while (i <= h1 && pre[i] < root) i++;
    } else {
        while (i <= h1 && pre[i] >= root) i++;
    }
    int j = i;                                  // 验证剩余元素是否符合当前模式
    while (j <= h1) {
        if ((!isMirror && pre[j] < root) || (isMirror && pre[j] >= root)) {
            return false;
        }
        j++;
    }

    int leftSize = i - l1 - 1;                   // 计算左右子树区间
    bool left = JudgeBSTbyPreOrder(pre, l1 + 1, i - 1, post, l2, l2 + leftSize - 1, isMirror);
    bool right = JudgeBSTbyPreOrder(pre, i, h1, post, l2 + leftSize, h2 - 1, isMirror);  // 递归处理左右子树
    return left && right;
}

int main()
{
    int n;
    scanf("%d", &n);
    int pre[n], post[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    bool valid = JudgeBSTbyPreOrder(pre, 0, n - 1, post, 0, n - 1, false);
    if (!valid) {           // 先尝试标准 BST 模式，如果失败再尝试镜像模式
        valid = JudgeBSTbyPreOrder(pre, 0, n - 1, post, 0, n - 1, true);
    }

    if (valid) {
        printf("YES\n");
        for (int i = 0; i < n; i++)
            printf("%d%c", post[i], (i == n - 1) ? '\n' : ' ');
    } else {
        printf("NO\n");
    }

    return 0;
}
