#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct DNode {          // 混合定义双链表结点类型
    ElementType data;           // 数据域
    int freq;
    struct DNode *prior, *next;   // 前驱和后继指针
} DNode, *DLinkList;

bool InitDLinkList(DLinkList &L);
bool DListInsert(DLinkList &L, int i, ElementType e);
void PrintList(DLinkList L);

DLinkList Locate(DLinkList &L, ElementType x)
{
    DNode *p = L->next, *q;
    while (p != NULL && p->data != x) 
        p = p->next;
    if (p == NULL) {
        return p;
    } else {
        p->freq++;
        if (p->prior == L || p->prior->freq > p->freq) { return p; }
        if (p->next != NULL)
            p->next->prior = p->prior;
        p->prior->next = p->next;
        q = p->prior;
        while (q != L && q->freq <= p->freq) {
            q = q->prior;
        }
        p->next = q->next;
        p->prior = q;
        if (q->next != NULL)
            q->next->prior = p;
        q->next = p;
    }
    
    return p;
}

int main()
{
	DNode *L = (DNode *)malloc(sizeof(DNode));
	InitDLinkList(L);
	
	DListInsert(L, 1, 1);
	DListInsert(L, 2, 2);
	DListInsert(L, 3, 3);
	DListInsert(L, 4, 4);
	DListInsert(L, 5, 5);
	
	Locate(L, 5);
	Locate(L, 4);
	
	PrintList(L);
	
	return 0;
}

bool InitDLinkList(DLinkList &L)
{
    L = (DNode *)malloc(sizeof(DNode));  // 分配一个头结点
    if (L == NULL)                       // 内存不足，分配失败
        return false;
    L->prior = NULL;                     // 头结点的 prior 永远指向 NULL
    L->next = NULL;                      // 头结点之后暂时还没有节点
    return true;
}

/* 不带头结点的双链表插入 */
bool DListInsert(DLinkList &L, int i, ElementType e)
{
    if (i < 1)                        // 检查位置合法性
        return false;
    
    DNode *p = L;                     // p指向头结点
    int j = 0;                        // 当前p指向的是第0个结点（头结点）
    
    while (p != NULL && j < i - 1) {  // 寻找第i-1个结点
        p = p->next;
        j++;
    }
    if (p == NULL)                    // i超过链表长度+1或无效位置
        return false;
    
    DNode *s = (DNode *)malloc(sizeof(DNode));
    if (s == NULL)                   // 内存分配失败处理
        return false;
    
    s->data = e;
    s->next = p->next;               // 新结点后继指向原第i个结点
    s->prior = p;                    // 新结点前驱指向第i-1个结点
    
    if (p->next != NULL) {           // 如果原第i个结点存在
        p->next->prior = s;          // 原第i个结点的前驱改为新结点
    }
    
    p->next = s; // 第i-1个结点的后继改为新结点
    return true;
}

void PrintList(DLinkList L)
{
	DLinkList p = L->next;
	while(p != NULL) {
		printf("[%d-%d]->", p->data, p->freq);
		p = p->next;
	}
}
