#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表 */

ElementType Find( List L, int m );

int main()
{
    List L;
    int m;
    L = Read();
    scanf("%d", &m);
    printf("%d\n", Find(L,m));
    Print(L);
    return 0;
}

/* 你的代码将被嵌在这里 */
ElementType Find( List L, int m )
{
    PtrToNode p = L->Next, q = p;    // 指针 p、q 指向第一个结点
    int cnt = 0;
    while (p != NULL) {              // 遍历链表至结束
        if (cnt < m)                 // 计数，若 cnt<m 只移动 p
            cnt++;
        else
            q = q->Next;             // m 步之后 p、q 同步移动
        p = p->Next;
    }
    if (cnt < m)                     // 查找失败返回 ERROR
        return ERROR;
    else                             // 查找成功返回结果
        return (q->Data);
}
