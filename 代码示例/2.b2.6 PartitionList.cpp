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

LinkList PartitionList(LinkList &LA)
{
    if (LA == NULL || LA->next == NULL) return LA;
    LinkList LB = (LinkList)malloc(sizeof(LNode)); // 创建 LB 的头结点
    LB->next = NULL;                               // 初始化  LB 表
    
    LNode *p = LA->next, *q;                       // 工作指针指向第一个数据结点，q 用来之后暂存后继
    LNode *ra = LA;                                // 生成指向尾结点的指针 ra
    while (p != NULL) {
        ra->next = p;                              // 将 *p 链到 A 的表尾
        ra = p;
        p = p->next;
        if (p != NULL) {
            q = p->next;                           // 头插后，*p 将断链，因此用 q 记忆 *p 后继
            p->next = LB->next;                    // 将 *p 插入链表 LB 的表头
            LB->next = p;
            p = q;
        }
    }
    ra->next = NULL;    // A 链表尾部 next 域置空
    return LB;
}

int main()
{
	LNode *LA = (LNode *)malloc(sizeof(LNode));
	LNode *LB;
	InitList(LA);
	
	for (int i = 0; i < 10; i++) {
		ListInsert(LA, i + 1, i);
	}
	PrintList(LA);
	printf("\n");
	LB = PartitionList(LA);
	PrintList(LA);
	printf("\n");
	PrintList(LB);
	
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
