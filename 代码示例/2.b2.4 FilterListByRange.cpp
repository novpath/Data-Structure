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

void DeleteListSToT(LinkList &L, ElementType s, ElementType t)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *p = L->next, *pre = L;     // 初始化 p 和 pre
    while (p != NULL) {
        if (p->data >= s && p->data <= t) {
            pre->next = p->next;      // 待删结点从链表中断开
            free(p);                  // 释放待删结点空间
        } else {                      // 否则，pre 和 p 同步后移
            pre = p;
        }
        p = pre->next;                // 两种情况 p 指针都要后移一个结点
    }
}

void FilterListByRange(LinkList &L, ElementType s, ElementType t)
{
    if (L == NULL || L->next == NULL)
        return ;
    LNode *r = L, *p = L->next;           // r 指向尾结点(注意和尾指针的区别)，初始化 r、p 指针
    while (p != NULL) {                
        if (p->data < s || p->data > t) { // 不为 s~t 的结点尾插法连接到 L 尾部
            r->next = p;
            r = p;
            p = p->next;                  // p 指针后移
        } else {                          // 扫描到的结点值为 x 时将其释放
            LNode *q = p;
            p = p->next;                  // p 指针后移，和下一条语句顺序不可改变
            free(q);
        }
    }
    r->next = NULL;                       // 插入结束后置尾结点指针为 NULL
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	for (int i = 0; i < 10; i++) {
		ListInsert(L, i + 1, i);
	}
	DeleteListSToT(L, 2, 4);
	PrintList(L);
	printf("\n");
	FilterListByRange(L, 6, 7);
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
