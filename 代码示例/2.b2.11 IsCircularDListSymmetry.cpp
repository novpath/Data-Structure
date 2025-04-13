#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct DNode {            // 定义双链表结点类型
    ElementType data;             // 数据域
    struct DNode *prior, *next;   // 前驱和后继指针
} DNode, *DLinkList;

bool InitDLinkList(DLinkList &L);
bool InsertNextDNode(DNode *p, DNode *s);
void PrintDList(DLinkList L);

bool IsCircularDListSymmetry(DLinkList L)
{
    DNode *p = L->next, *q = L->prior;
    while (p != q && q->next != p) {
        if (p->data != q->data) {
            return 0;
        } else {
            p = p->next;
            q = q->prior;
        }
    }
    return 1;
}

int main()
{
	DNode *L = (DNode *)malloc(sizeof(DNode));
	InitDLinkList(L);
	DNode *p = L;
	
	DNode *s = (DNode *)malloc(sizeof(DNode));
	s->data = 1;
	InsertNextDNode(p, s);
	
	DNode *s1 = (DNode *)malloc(sizeof(DNode));
	s1->data = 2;
	InsertNextDNode(p, s1);
	
	DNode *s2 = (DNode *)malloc(sizeof(DNode));
	s2->data = 2;
	InsertNextDNode(p, s2);
	
	DNode *s3 = (DNode *)malloc(sizeof(DNode));
	s3->data = 1;
	InsertNextDNode(p, s3);
	
	PrintDList(L);
	
	printf("%d", IsCircularDListSymmetry(L));
	
	return 0;
}

bool InitDLinkList(DLinkList &L)
{
    L = (DNode *)malloc(sizeof(DNode));  // 分配一个头结点
    if (L == NULL)                       // 内存不足，分配失败
        return false;
    L->prior = L;                        // 头结点的 prior 指向头结点
    L->next = L;                         // 头结点的 next 指向头结点
    return true;
}

bool InsertNextDNode(DNode *p, DNode *s)
{
    s->next = p->next;
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

void PrintDList(DLinkList L)
{
	DLinkList p = L->next;
	while(p != L) {
		printf("%d ", p->data);
		p = p->next;
	}
}
