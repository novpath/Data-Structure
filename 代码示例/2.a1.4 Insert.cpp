#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* ϸ���ڴ˲��� */
void Print( List L ); /* ϸ���ڴ˲��� */

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
    while (p->Next != NULL && p->Next->Data < X)   // ������������������ҵ�����λ�ã�����ѭ��
        p = p->Next;
    List s = (List)malloc(sizeof(struct Node));    // �����½��
    s->Data = X;
    s->Next = p->Next;                             // �����½��
    p->Next = s;

    return L;
}
