#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

List ReadInput(); /* 裁判实现，细节不表 */
void PrintList( List L ); /* 裁判实现，细节不表 */
void K_Reverse( List L, int K );

int main()
{
    List L;
    int K;

    L = ReadInput();
    scanf("%d", &K);
    K_Reverse( L, K );
    PrintList( L );

    return 0;
}

/* 你的代码将被嵌在这里 */
void K_Reverse(List L, int K) {
    if (!L || K <= 1) return;
    List pre = L;
    List start = L->Next, p = start;
    while (p != NULL) {
        List end = p;
        int cnt = 1;
        while (cnt < K && end->Next != NULL) {
            end = end->Next;
            cnt++;
        }
        if (cnt < K) break;
        List nextGroup = end->Next;
        List p = start;
        while (p != nextGroup) {
            List tmp = p->Next;
            p->Next = pre->Next;
            pre->Next = p;
            p = tmp;
        }
        pre->Next = end;
        pre = start;
        start->Next = nextGroup;
    }
}