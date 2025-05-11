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

bool DeleteListMin(LinkList &L)
{
    if (L == NULL || L->next == NULL)
        return false;
    LNode *prep = L, *p = prep->next;  // p 为工作指针，pre 指向其前驱
    LNode  *premin = L, *min = p;      // 保存最小值结点及其前驱
    while (p != NULL) {
        if (p->data < min->data) {
            min = p;                   // 找到更小的结点更新前驱指针及指针
            premin = prep;
        }
        prep = p;                       // 继续扫描下一个结点
        p = p->next;
    }
    premin->next = min->next;           // 删除最小值结点
    free(min);
    return true;
}

int main()
{
	LNode *L = (LNode *)malloc(sizeof(LNode));
	InitList(L);
	ListInsert(L, 1, 2);
	ListInsert(L, 2, 2);
	ListInsert(L, 3, 3);
	ListInsert(L, 4, 1);
	ListInsert(L, 5, 5);
	DeleteListMin(L);
	
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
