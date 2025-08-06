#include <cstdio>
#include <cstdlib>

int IsInsertion(int A[], int B[], int N);  /* 判断是否插入排序 */
void PrintResults(int B[], int N);        /* 输出结果序列 */
void NextInsertion(int B[], int N, int K);/* 执行下一步插入 */
int MergeLength(int B[], int N);          /* 找出归并段长度 */
void NextMerge(int B[], int N);           /* 执行下一步归并 */

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
        NextMerge(B, N);       /* 否则执行下一步归并 */

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
    printf("\n");
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

int MergeLength(int B[], int N)
{
    int i, L;
    for (L = 2; L <= N; L *= 2) {
        for (i = L; i < N; i += L * 2)
            if (B[i - 1] > B[i]) break;
        if (i < N) break;
    }
    return L;
}

void NextMerge(int B[], int N)
{
    int i, p1, p2;
    int *Tmp = (int *) malloc(sizeof(int) * N);
    printf("Merge Sort\n");
    /* 找出当前归并段长度 */
    int L = MergeLength(B, N);
    int p = 0;                               /* p指向Tmp中当前处理的位置 */
    for (i = 0; i < (N - L - L); i += L * 2)     /* 两两归并长度为L的段 */
    {
        p1 = i;
        p2 = i + L;              /* p1和p2分别指向两个段的当前处理位置 */
        while (p1 < (i + L) && p2 < (i + L + L)) {
            if (B[p1] > B[p2]) Tmp[p++] = B[p2++];
            else Tmp[p++] = B[p1++];
        }
        while (p1 < (i + L)) Tmp[p++] = B[p1++];
        while (p2 < (i + L + L)) Tmp[p++] = B[p2++];
    }
    if ((N - 1) > L)                        /* 如果最后剩2段，执行归并 */
    {
        p1 = i;
        p2 = i + L;
        while (p1 < (i + L) && p2 < N) {
            if (B[p1] > B[p2]) Tmp[p++] = B[p2++];
            else Tmp[p++] = B[p1++];
        }
        while (p1 < (i + L)) Tmp[p++] = B[p1++];
        while (p2 < N) Tmp[p++] = B[p2++];
    } else                                 /* 最后只剩1段 */
        while (i < N) Tmp[i] = B[i++];
    PrintResults(Tmp, N);
    free(Tmp);
}
