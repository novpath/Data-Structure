#include <cstdio>
#include <cstdlib>
#define NULL nullptr

struct Element {
    int value;   // 原始值
    int index;   // 原始位置索引（稳定性关键）
};

int DoubleCmp(Element x, Element y)
{
    if (x.value != y.value) {
        return (x.value > y.value) ? 1 : -1;
    }
    return (x.index > y.index) ? 1 : ((x.index == y.index) ? 0 : -1);
}

int Partition(Element A[], int low, int high)
{
    Element pivot = A[low];  // 枢轴元素（包含索引）
    while (low < high) {
        // 从右向左找第一个小于枢轴的元素（值小，或值等但索引小）
        while (low < high && DoubleCmp(A[high], pivot) > 0)
            --high;
        A[low] = A[high];
        // 从左向右找第一个大于枢轴的元素（值大，或值等但索引大）
        while (low < high && DoubleCmp(A[low], pivot) < 0)
            ++low;
        A[high] = A[low];
    }
    A[low] = pivot;  // 枢轴归位
    return low;
}

void QuickSort(Element A[], int low, int high)
{
    if (low < high) {
        int pivotPos = Partition(A, low, high);
        QuickSort(A, low, pivotPos - 1);
        QuickSort(A, pivotPos + 1, high);
    }
}

void StableQuickSort(int arr[], int n)
{
    // 1. 创建带索引的元素数组
    Element *elements = (Element *) malloc(n * sizeof(Element));
    if (elements == NULL)
        return;
    for (int i = 0; i < n; i++) {
        elements[i].value = arr[i];
        elements[i].index = i;  // 记录原始位置
    }
    // 2. 执行快速排序
    QuickSort(elements, 0, n - 1);
    // 3. 回写排序结果
    for (int i = 0; i < n; i++)
        arr[i] = elements[i].value;
    free(elements);
}

// 打印数组辅助函数
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    // 测试用例：包含重复元素
    int arr[] = {5, 2, 9, 5, 2, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Before Sorting:\n");
    printArray(arr, n);
    // 执行稳定排序
    StableQuickSort(arr, n);

    printf("After Sorting:\n");
    printArray(arr, n);

    return 0;
}
