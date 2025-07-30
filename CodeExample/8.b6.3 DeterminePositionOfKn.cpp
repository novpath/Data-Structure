#include <cstdio>

typedef int ElementType;

int Partition(ElementType K[], int n)
{
    // 交换序列 K[1..n] 中的记录，使枢轴到位,并返回其所在位置
    int i = 1, j = n;         // 设置两个交替变量初值分别为 1 和 n
    ElementType pivot = K[j]; // 枢轴
    while (i < j) {           // 循环跳出条件
        while (i < j && K[i] <= pivot)
            i++;              // 从前往后找比枢轴大的元素
        if (i < j)
            K[j] = K[i];      // 移动到右端
        while (i < j && K[j] >= pivot)
            j--;              // 从后往前找比枢轴小的元素
        if (i < j)
            K[i] = K[j];      // 移动到左端
    }  // while
    K[i] = pivot;             // 枢轴存放在最终位置
    return i;                 // 返回存放枢轴的位置
}

int main()
{
    int n;
    scanf("%d", &n);
    ElementType K[n + 1];
    for (int i = 1; i <= n; i++)
        scanf("%d", &K[i]);
    Partition(K, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", K[i]);

    return 0;
}
