#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {  // 混合定义单链表的结点类型
    ElementType data;   // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList; 

bool InitList(LinkList &L);
bool ListInsert(LinkList &L, int i, ElementType e);
void PrintList(LinkList &L);

LinkList ReverseLinkList(LinkList &L)
{
    if (L == NULL || L->next == NULL)  // L 合法性检查
        return L;
    LNode *p = L->next, *q;            // p 为工作指针，r 为 p 的后继，以防断链
    L->next = NULL;                    // 头结点 L 的 next 域置为 NULL
    while (p != NULL) {                // 依次将元素结点摘下
        q = p->next;                   // 暂存 p 的后继
        p->next = L->next;             // 将 p 结点插入到头结点之后
        L->next = p;
        p = q;
    }
    return L; 
}

LinkList TriPtrReverse(LinkList L)
{
    if (L == NULL)      // 空表的时候直接返回，提高健壮性
        return L;
    LNode *pre, *p = L->next, *r = p->next;
    p->next = NULL;     // 处理第一个结点
    while (r != NULL) { // r 为空，则说明 p 为最后一个结点
        pre = p;
        p = r;
        r = r->next;
        p->next = pre;  // 指针反转
    }
    L->next = p;        // 处理最后一个结点
    return L;
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	ListInsert(L, 1, 1);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 4);
	ListInsert(L, 5, 5);
    ReverseLinkList(L); 
	
	PrintList(L);
	printf("\n");
	ListInsert(L, 6, 6);
	ListInsert(L, 7, 7);
	ListInsert(L, 8, 8);
	ListInsert(L, 9, 9);
	ListInsert(L, 10, 10);
	TriPtrReverse(L);
	PrintList(L);
	
	return 0;
}

bool InitList(LinkList &L)              // 带头结点的单链表的初始化
{
    L = (LNode *)malloc(sizeof(LNode)); // 创建头结点
    if (L == NULL)                      // 内存不足，分配失败
        return false;
    L->next = NULL;                     // 头结点的指针域为空
    return true;
}

bool ListInsert(LinkList &L, int i, ElementType e)
{
    if (i < 1)                       // i 值合法性检查
        return false;
    LNode *p = L;                    // 指针 p 指向当前扫描到的结点
    int j = 0;                       // 记录当前结点的位序，头结点是第 0 个结点
    while (p != NULL && j < i - 1) { // 循环找到第 i-1 个结点
        p = p->next;
        j++;
    }
    if (p == NULL)                   // i 值不合法
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e; 
    s->next = p->next;               // 新结点先接上后继结点
    p->next = s;                     // 前驱结点接上新结点（同时断开原后继结点连接）
    return true;
}

void PrintList(LinkList &L)
{
	LinkList p = L->next;
	while(p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}
