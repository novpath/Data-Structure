#include <stdio.h>
#define MaxSize 100
typedef int ElementType;
typedef struct BiTNode {
    ElementType value; // 结点中的数据元素
    bool isEmpty; // 结点是否为空
} BiTNode;

BiTNode LowestCommonAncestor(const BiTNode *T, int i, int j)
{
    if (!T[i].isEmpty && !T[j].isEmpty) {
        while (i != j) {
            if (i > j)
                i /= 2;
            else
                j /= 2;
        }
    }
    return T[i];
}

int main()
{
    BiTNode t[MaxSize]; // 定义一个长度为 MaxSize 的数组 t
    for (int i = 0; i < MaxSize; i++)
        t[i].isEmpty = true;
    for (int i = 1; i <= 15; i++) {
        t[i].isEmpty = false;
        t[i].value = i;
    }
    int i, j;
    scanf("%d %d", &i, &j);
    printf("%d\n", LowestCommonAncestor(t, i, j).value);

    return 0;
}
