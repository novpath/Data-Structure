#include <cstdio>

void Union(int S[], int Root1, int Root2)
{
    if (Root1 == Root2) return;
    if (S[Root2] > S[Root1]) {             // Root2 结点数更少
        S[Root1] += S[Root2];              // 累加集合树的结点总数
        S[Root2] = Root1;                  // 小树合并到大树
    } else {                               // Root1 结点数更少
        S[Root2] += S[Root1];              // 累加结点总数
        S[Root1] = Root2;                  // 小树合并到大树
    }
}

int Find(int S[], int x)
{
    int root = x;
    while (S[root] >= 0)    // 循环找到根
        root = S[root];
    while (x != root) {     // 压缩路径
        int t = S[x];       // t 指向 x 的父节点
        S[x] = root;        // x 直接挂到根结点下面
        x = t;
    }
    return root;            // 返回根结点编号
}

int main()
{
    return 0;
}
