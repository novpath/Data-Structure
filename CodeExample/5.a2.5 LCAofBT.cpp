#include <cstdio>
#define MaxSize 1001
typedef int ElementType;

typedef struct BiTNode {
    ElementType value; // 结点中的数据元素
} BiTNode;

BiTNode LowestCommonAncestor(const BiTNode *T, int &i, int j)
{
    while (i != j) {
        if (i > j)
            i /= 2;
        else
            j /= 2;
    }
    return T[i];
}

int main()
{
    BiTNode t[MaxSize]; // 定义一个长度为 MaxSize 的数组 t
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &t[i].value);
    int i, j;
    scanf("%d %d", &i, &j);
    if (t[i].value == 0)
        printf("ERROR: T[%d] is NULL", i);
    else if (t[j].value == 0)
        printf("ERROR: T[%d] is empty", j);
    else {
        BiTNode t1 = LowestCommonAncestor(t, i, j);
        printf("%d %d\n", i, t1.value);
    }

    return 0;
}
