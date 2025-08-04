#include <cstdio>

int Partition(int A[], int low, int high)
{
    int cmpCnt = 0, swapCnt = 0;
    // 一趟划分
    int pivot = A[low]; // 将当前表中第一个元素设为枢轴,对表进行划分
    while (++cmpCnt && low < high) {        // 循环跳出条件
        while (++cmpCnt && low < high && ++cmpCnt && A[high] >= pivot) --high;
        A[low] = A[high];       // 将比枢轴小的元素移动到左端
        ++swapCnt;
        while (++cmpCnt && low < high && ++cmpCnt && A[low] <= pivot) ++low;
        A[high] = A[low];       // 将比枢轴大的元素移动到右端
        ++swapCnt;
    }
    A[low] = pivot;             // 枢轴元素存放到最终位置
    ++swapCnt;
    printf("cmpCnt = %d, swapCnt = %d\n", cmpCnt, swapCnt);
    return low;                 // 返回存放枢轴的最终位置
}

void QuickSort(int A[], int low, int high)
{
    for (int i = 0; i < 13; i++) {
        printf("%d,", A[i]);
    }
    printf("\n");
    printf("low = %d high = %d\n", low, high);
    if (low < high) {                           // 递归跳出的条件
        // Partition () 就是划分操作，将表A[low...high] 划分为满足上述条件的两个子表
        int pivotpos = Partition(A, low, high); // 划分  #96行
        printf("pivotPos = %d\n", pivotpos);
        QuickSort(A, low, pivotpos - 1);        // 依次对两个子表进行递归排序  #97行
        QuickSort(A, pivotpos + 1, high);       // #98行
    }
}

int main()
{
    int A[13] = {48, 27, 96, 48, 25, 6, 90, 17, 84, 62, 49, 72, 17};
    QuickSort(A, 0, 12);

    return 0;
}
