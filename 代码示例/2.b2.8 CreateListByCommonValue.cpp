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

LinkList CreateListByCommonValue(LinkList LA, LinkList LB) {
    LNode *p = LA->next, *q = LB->next;
    LNode *LC = (LNode *)malloc(sizeof(LNode));         // 建立链表 C
    LNode *r = LC;                                      // r 指向链表 C 的尾结点
    while (p != NULL && q != NULL) {                    // 扫描到任一链表结束
        if (p->data > q->data) {
            q = q->next;                                // 所指链表元素小的指针后移
        } else if (p->data < q->data) {
            p = p->next;
        } else {
            LNode * s = (LNode *)malloc(sizeof(LNode)); // 新建结点
            s->data = p->data;
            r->next = s;                                // *s 接到 LC 尾部
            r = s;
            p = p->next;                                // 继续向后扫描
            q = q->next;
        }
    }
    r->next = NULL;                                     // 链表 C 的尾结点指针置空
    return LC;
}

int main()
{
	LNode *LA = (LNode *)malloc(sizeof(LNode));
	LNode *LB = (LNode *)malloc(sizeof(LNode));;
	InitList(LA);
	InitList(LB);
	
	for (int i = 0; i < 10; i++) {
		ListInsert(LA, i + 1, i);
	}
	for (int i = 0; i < 10; i++) {
		ListInsert(LB, i + 1, 2 * i);
	}
	
	LNode *LC = CreateListByCommonValue(LA, LB);
	PrintList(LC);
	
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
