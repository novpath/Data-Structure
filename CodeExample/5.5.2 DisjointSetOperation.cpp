#include <cstdio>

#define SIZE 100
int UFSets[SIZE];         // 集合元素数组（双亲指针数组）

void Initial(int S[])
{
    for (int i = 0; i <= SIZE; i++)     // S 即并查集
        S[i] = -1;                      // 每个自成单元素集合
}

int Find(int S[], int x)
{
    while (S[x] > 0)     // 循环寻找x的根
        x = S[x];
    return x;            // 根的S[]小于0
}

void Union(int S[], int Root1, int Root2)
{
    if (Root1 == Root2) return;           //要求 Root1 与 Root2 是不同的集合
    S[Root2] = Root1;                     //将根 Root2 连接到另一根 Root1 下面
}

int main()
{
    return 0;
}
