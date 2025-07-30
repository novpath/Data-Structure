#include <cstdio>
#include <cstdlib>

#define NULL nullptr
#define MAX_SIZE 8

typedef struct PriorityQueueElement {
    int value;    // 元素的值
    int priority; // 元素的优先级，priority 越大，优先级越高
} PriorityQueueElement;

typedef struct PQNode {
    PriorityQueueElement heap[MAX_SIZE]; // 用数组实现堆
    int size;                            // 当前堆中元素的数量
} PQNode, *PriorityQueue;

bool Enqueue(PriorityQueue pq, int value, int priority)
{
    if (pq->size >= MAX_SIZE)
        return false;
    int i;
    pq->heap[0] = {value, priority};                                // 哨兵
    for (i = ++pq->size; pq->heap[i / 2].priority < priority; i /= 2)  // 向上调整
        pq->heap[i] = pq->heap[i / 2];
    pq->heap[i] = {value, priority};
    return true;
}

PriorityQueueElement Dequeue(PriorityQueue pq)
{
    if (pq->size == 0) {
        PriorityQueueElement illegal = {-1, -1};
        return illegal;
    }
    int k = 1;
    PriorityQueueElement deleted = pq->heap[k]; // 保存被删除的元素
    pq->heap[k] = pq->heap[pq->size];           // 用最后一个元素覆盖位置k
    pq->size--;                                 // 堆大小减1

    pq->heap[0] = pq->heap[k];                   // heap[0]暂存子树的根结点
    for (int i = 2 * k; i <= pq->size; i *= 2) { // 沿 priority 较大的子结点向下筛选
        if (i < pq->size && pq->heap[i].priority < pq->heap[i + 1].priority)
            i++;                                 // 取 priority 较大的子结点的下标(如果一样大优先取左孩子)
        if (pq->heap[0].priority >= pq->heap[i].priority) break;   // 筛选结束
        pq->heap[k] = pq->heap[i];    // 不满足上面的条件，则将 pq->heap[i] 调整到双亲结点上
        k = i;                        // 修改 k 值，以便继续向下筛选
    }
    pq->heap[k] = pq->heap[0];        // 被筛选结点的值放入最终位置

    return deleted;
}

int main()
{
    PriorityQueue pq = (PriorityQueue) malloc(sizeof(PQNode));
    pq->size = 0;
    for (int i = 1; i <= 7; i++) {
        Enqueue(pq, 10 - i, i);
    }
    for (int i = 1; i <= 7; i++) {
        printf("(%d %d) ", pq->heap[i].value, pq->heap[i].priority);
    }
    printf("\n");
    Dequeue(pq);
    for (int i = 1; i <= 6; i++) {
        printf("(%d %d) ", pq->heap[i].value, pq->heap[i].priority);
    }

    free(pq);
    return 0;
}
