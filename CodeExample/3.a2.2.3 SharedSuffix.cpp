#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

void ReadInput( List L1, List L2 ); /* 裁判实现，细节不表 */
void PrintSublist( PtrToNode StartP ); /* 裁判实现，细节不表 */
PtrToNode Suffix( List L1, List L2 );

int main()
{
    List L1, L2;
    PtrToNode P;

    L1 = (List)malloc(sizeof(struct Node));
    L2 = (List)malloc(sizeof(struct Node));
    L1->Next = L2->Next = NULL;
    ReadInput( L1, L2 );
    P = Suffix( L1, L2 );
    PrintSublist( P );

    return 0;
}

/* 你的代码将被嵌在这里 */
PtrToNode Suffix( List L1, List L2 )
{
    List p = L1->Next, q = L2->Next;
    int len1 = 0, len2 = 0;
    while (p != NULL) {                      // 求 str1 的长度
        len1++;
        p = p->Next;
    }
    while (q != NULL) {                      // 求 str2 的长度
        len2++;
        q = q->Next;
    }
    
    for (p = L1->Next; len1 > len2; len1--)  // 长的链表先移动
        p = p->Next;
    for (q = L2->Next; len2 > len1; len2--)  // 长的链表先移动
        q = q->Next;
        
    while (p != q && p != NULL) {            // 查找共同后缀的起始点
        p = p->Next;                         // 两指针同步移动
        q = q->Next;
    }
    
    return p;                                // 返回共同后缀的起始地址
}