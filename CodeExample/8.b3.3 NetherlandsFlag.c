#include <stdio.h>

typedef enum { RED, WHITE, BLUE } color;     // 设置枚举数组
void Swap(color *a, color *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void FlagArrange(color a[], int n)
{
    int i = 0, j = 0, k = n - 1;
    while (j <= k) {
        switch (a[j]) {                        // 判断条块颜色
            case RED: Swap(&a[i], &a[j]); // 红色，则和 i 交换
                i++;
                j++;
                break;
            case WHITE: j++;
                break;
            case BLUE: Swap(&a[j], &a[k]); // 蓝色，则和 k 交换
                k--;                            // 这里没有 j++ 语句，以防止交换后 a[j] 仍为蓝色
                break;
        }
    }
}

int main()
{
    int a[9] = {BLUE, WHITE, RED, WHITE, BLUE, RED, RED, WHITE, BLUE};
    int size = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < size; i++)
        printf("%d%c", a[i], i == size - 1 ? '\n' : ' ');
    FlagArrange(a, size);
    for (int i = 0; i < size; i++)
        printf("%d%c", a[i], i == size - 1 ? '\n' : ' ');
    return 0;
}
