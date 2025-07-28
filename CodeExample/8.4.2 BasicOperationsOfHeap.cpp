#include <cstdio>

typedef int ElementType;

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SiftDown(ElementType A[], int k, int len)
{
    // 函数 SiftDown 对以元素 k 为根的子树进行调整
    A[0] = A[k];                            // A[0]暂存子树的根结点
    for (int i = 2 * k; i <= len; i *= 2) { // 沿 key 较大的子结点向下筛选
        if (i < len && A[i] < A[i + 1])
            i++;                            // 取 key 较大的子结点的下标(如果一样大优先取左孩子)
        if (A[0] >= A[i]) break;            // 筛选结束
        A[k] = A[i];                        // 不满足上面的条件，则将A[i]调整到双亲结点上
        k = i;                              // 修改 k 值，以便继续向下筛选
    }
    A[k] = A[0]; // 被筛选结点的值放入最终位置
}

void SiftUp(ElementType H[], int k)
{   // 对元素 k 进行上滤操作
    H[0] = H[k];         // 暂存需要上滤的元素
    int parent = k / 2;  // 父结点位置

    // 循环向上调整（当未到达根节点且父节点值小于待调整元素时）
    while (parent >= 1 && H[parent] < H[0]) {
        H[k] = H[parent];  // 将父结点下移
        k = parent;        // 更新当前位置为父结点位置
        parent = k / 2;    // 计算新的父结点位置
    }

    H[k] = H[0];  // 将暂存元素放入最终位置
}

void BuildMaxHeap(ElementType A[], int len)
{
    for (int i = len / 2; i > 0; i--) // 从 i=[n/2]~1, 反复调整堆
        SiftDown(A, i, len);
}

void HeapSort(ElementType A[], int len)
{
    BuildMaxHeap(A, len);              // 初始建堆
    for (int i = len; i > 1; i--) {    // n-1 趟的交换和建堆过程
        Swap(A[i], A[1]); // 输出堆顶元素(和堆底元素交换)
        SiftDown(A, 1, i - 1);   // 调整，把剩余的 i-1 个元素整理成堆
    }
}

void Insert(ElementType A[], int x, int &len) // 堆插入，len 为堆中数组的长度，也可以用结构体封装
{
    int i;
    A[0] = x;                                // 哨兵
    for (i = ++len; A[i / 2] < x; i /= 2)    // 只需要对比一次关键字即可
        A[i] = A[i / 2];
    A[i] = x;
}

void HeapInsert(ElementType A[], int x, int &len)  // 堆插入的上滤写法
{
    len = len + 1;       // 堆长度增加1
    A[len] = x;          // 新元素插入到堆末尾
    SiftUp(A, len);      // 对插入的元素进行上滤操作
}

ElementType Delete(ElementType H[], int k, int &len)
{
    if (len == 0 || k < 1 || k > len)
        return -1;              // 堆空或无效位置，返回-1

    ElementType deleted = H[k]; // 保存被删除的元素
    H[k] = H[len];              // 用最后一个元素覆盖位置k
    len--;                      // 堆大小减1

    if (k <= len) {             // 调整堆
        SiftDown(H, k, len);    // 向下调整
    }

    return deleted; // 返回被删除元素
}

int main()
{
    int A[] = {0, 53, 17, 78, 9, 45, 65, 87, 32};
    int len = sizeof(A) / sizeof(A[0]) - 1;
    BuildMaxHeap(A, len);
    for (int i = 1; i <= len; i++)
        printf("%d%c", A[i], i == len ? '\n' : ' ');
    HeapInsert(A, 100, len);
    for (int i = 1; i <= len; i++)
        printf("%d%c", A[i], i == len ? '\n' : ' ');
    Delete(A, 2, len);
    for (int i = 1; i <= len; i++)
        printf("%d%c", A[i], i == len ? '\n' : ' ');
    HeapSort(A, len);
    for (int i = 1; i <= len; i++)
        printf("%d%c", A[i], i == len ? '\n' : ' ');

    return 0;
}
