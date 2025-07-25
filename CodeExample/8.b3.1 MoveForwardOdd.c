#include <stdio.h>

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reOrderArray(int *array, int length)
{
    int low = 0, high = length - 1;
    while (low < high) {                   // 循环跳出条件
        while (low < high && array[high] % 2 == 0) --high;    // 从右向左寻找第一个奇数
        while (low < high && array[low] % 2 == 1) ++low;      // 从左向右寻找第一个偶数
        if (low < high) Swap(&array[low], &array[high]); // 交换
    }
}

int main()
{
    int q[5] = {1, 2, 3, 4, 5};
    int size = sizeof(q) / sizeof(q[0]);
    for (int i = 0; i < size; i++)
        printf("%d%c", q[i], i == size - 1 ? '\n' : ' ');
    reOrderArray(q, size);
    for (int i = 0; i < size; i++)
        printf("%d%c", q[i], i == size - 1 ? '\n' : ' ');
    return 0;
}
