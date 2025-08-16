#include <cstdio>
#include <cstdlib>
#define NULL nullptr
int IsInsertion(int A[], int B[], int N);  /* 判断是否插入排序 */
void PrintResults(int B[], int N);         /* 输出结果序列 */
void NextInsertion(int B[], int N, int K); /* 执行下一步插入 */
void NextHeapSort(int B[], int N);         /* 执行下一步归并 */

int main()
{
    int N, i, k;

    scanf("%d", &N);
    int *A = (int *) malloc(sizeof(int) * N);  /* A存原始序列 */
    int *B = (int *) malloc(sizeof(int) * N);  /* B存中间序列 */
    if (A == NULL || B == NULL)
        return -1;
    for (i = 0; i < N; i++) scanf("%d", &A[i]);
    for (i = 0; i < N; i++) scanf("%d", &B[i]);
    if (k = IsInsertion(A, B, N))         /* 如果是插入排序 */
        NextInsertion(B, N, k);          /* 执行下一步插入 */
    else
        NextHeapSort(B, N);       /* 否则执行下一步归并 */

    free(A);
    free(B);
    return 0;
}

int IsInsertion(int A[], int B[], int N)
{
    int i;
    for (i = 1; i < N; i++)
        if (B[i] < B[i - 1]) break;         /* 发现顺序不对 */
    int k = i;                               /* 可能是插入排序的有序序列尾部位置 */
    for (; i < N; i++)
        if (B[i] != A[i]) break;          /* 发现后面序列有变化 */
    if (i == N) return k;                 /* 是插入排序，返回插入位置 */
    return 0;                             /* 不是插入排序 */
}

void PrintResults(int B[], int N)
{
    if (B == NULL)
        return;
    printf("%d", B[0]);
    for (int i = 1; i < N; i++) printf(" %d", B[i]);
}

void NextInsertion(int B[], int N, int K)
{
    int i;
    printf("Insertion Sort\n");
    int tmp = B[K];
    for (i = K - 1; i >= 0; i--) {
        if (tmp < B[i]) B[i + 1] = B[i];
        else break;
    }
    B[i + 1] = tmp;
    PrintResults(B, N);
}

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SiftDown(int B[], int k, int len)
{
    // 函数 SiftDown 对以元素 k 为根的子树进行调整
    int temp = B[k];                            // temp 暂存子树的根结点
    for (int i = 2 * k + 1; i < len; i *= 2) {  // 沿 key 较大的子结点向下筛选
        if (i < len - 1 && B[i] < B[i + 1])
            i++;                                // 取 key 较大的子结点的下标(如果一样大优先取左孩子)
        if (temp >= B[i]) break;                // 筛选结束
        B[k] = B[i];                            // 不满足上面的条件，则将B[i]调整到双亲结点上
        k = i;                                  // 修改 k 值，以便继续向下筛选
    }
    B[k] = temp; // 被筛选结点的值放入最终位置
}

void NextHeapSort(int B[], int len)
{
    printf("Heap Sort\n");
    int k;
    for (k = 1; k < len; k++) {
        if (B[k] > B[0]) {   // 找堆尾
            k = k - 1;
            break;
        }
    }
    Swap(B[k], B[0]);        // 堆底元素交换
    SiftDown(B, 0, len - 2); // 调整一次
    PrintResults(B, len);
}
