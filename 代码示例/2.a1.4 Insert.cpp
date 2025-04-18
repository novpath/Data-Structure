#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表 */

List Insert( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    L = Read();
    scanf("%d", &X);
    L = Insert(L, X);
    Print(L);
    return 0;
}

List Insert(List L, ElementType X)
{
    List p = L;
    while (p->Next != NULL && p->Next->Data < X)   // 遍历完整个链表或者找到插入位置，结束循环
        p = p->Next;
    List s = (List)malloc(sizeof(struct Node));    // 申请新结点
    s->Data = X;
    s->Next = p->Next;                             // 插入新结点
    p->Next = s;

    return L;
}
