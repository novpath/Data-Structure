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
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Merge(List L1, List L2)
{
    List p = L1->Next, q = L2->Next, r;    // 设工作指针分别为 p 和 q

    List L = (List)malloc(sizeof(struct Node));
    r = L;
    
    while (p != NULL && q != NULL) {
        if (p->Data < q->Data) {
            r->Next = p;
            r = p;
            p = p->Next;
        } else {
            r->Next = q;
            r = q;
            q = q->Next;
        }
    }
    while (p) {
        r->Next = p;
        r = p;
        p = p->Next;
    }
    while (q) {
        r->Next = q;
        r = q;
        q = q->Next;
    }
    r->Next = NULL;
    L1->Next = NULL;
    L2->Next = NULL;
    
    return L;
}
