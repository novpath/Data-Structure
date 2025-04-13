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

LinkList LinkListUnion(LinkList &LA, LinkList &LB)
{
    LNode *pa = LA->next, *pb = LB->next;    // 设工作指针分别为 pa 和 pb
    LNode *pre = LA, *t;                     // 结果表中当前合并结点的前驱指针 pre，临时指针 t
    while (pa != NULL && pb != NULL) {
        if (pa->data == pb->data) {          // 交集并入结果表中
            pre->next = pa;                  // A 中结点链接到结果表
            pre = pa;
            pa = pa->next;
            t = pb;                          // B 中结点释放
            pb = pb->next;
            free(t);
        } else if (pa->data < pb->data) {    // 若 A 中当前结点值小于 B 中当前结点值
            t = pa;
            pa = pa->next;                   // 后移指针
            free(t);                         // 释放 A 中当前结点
        } else {
            t = pb;
            pb = pb->next;                   // 后移指针
            free(t);                         // 释放 B 中当前结点
        }
    }
    while (pa) {                         // B 已遍历完，A 未完
        t = pa;
        pa = pa->next;
        free(t);                         // 释放 A 中剩余结点
    }
    while (pb) {                         // A 已遍历完，B 未完
        t = pb;
        pb = pb->next;
        free(t);                         // 释放 B 中剩余结点
    }
    pre->next = NULL;                    // 置结果链表表尾指针为 NULL
    free(LB);                            // 释放 B 表的头结点
    
    return LA;
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
	
	LinkListUnion(LA, LB);
	PrintList(LA);
	
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
