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

bool IsSubsequence(LinkList LA, LinkList LB)
{
    LNode *pa = LA, *pb = LB;      // pa 为 A 链表的工作指针，pb 为 B 链表的工作指针，都无头结点
    LNode *pre = pa;               // p 指针记录每次比较 A 链表的开始结点的前驱
    while (pa && pb) {             
        if (pa->data == pb->data) {// 结点值相同则继续往后比较
            pa = pa->next;
            pb = pb->next;
        } else {
            pb = LB->next;         // B 链表每次匹配失败都从头开始比较
            pa = pre->next;        // pa 每次从 p 指针所指位置之后开始比较
            pre = pa;              // 记录下一次比较位置的前驱 
        }
    }
    if (pb == NULL)                // B 链表完全匹配
        return true;               // B 链表是 A 链表的子序列
    else                           
        return false;              // B 链表不是 A 链表的子序列
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
	for (int i = 0; i < 8; i++) {
		ListInsert(LB, i + 1, i + 2);
	}
	
	printf("%d\n", IsSubsequence(LA, LB));
	
	return 0;
}

bool InitList(LinkList &L)       // 不带头结点的单链表的初始化
{
    L = NULL;                    // 头指针为空，空表，暂时还没有任何结点
    return true;
}

bool ListInsert(LinkList &L, int i, ElementType e)
{
    if (i < 1)                         // i 值合法性检查
        return false;
    if (i == 1) {                      // 处理插入到首部(i = 1)的情况
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;                        // 头指针指向新的结点
        return true;
    }
    
    LNode *p = L;                    // 指针 p 指向当前扫描到的结点
    int j = 1;                       // 计数器从 1 开始
    while (p != NULL && j < i - 1) { // 循环找到第 i-1 个结点
        p = p->next;
        j++;
    }
    if (p == NULL)                     // i 值不合法
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e; 
    s->next = p->next;                 // 新结点先接上后继结点
    p->next = s;                       // 前驱结点接上新结点（同时断开原后继结点连接）
    return true;
}

void PrintList(LinkList &L)
{
	LinkList p = L;
	while(p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}
