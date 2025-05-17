#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int coef;
    int exp;
    struct LNode *next;
} LNode, *LinkList;

void Attach(int c, int e, LinkList &r)
{
    LNode *P = (LNode *)malloc(sizeof(LNode));
    P->coef = c;
    P->exp = e;
    P->next = NULL;
    r->next = P;
    r = P;
}

LinkList ReadPoly()
{
    LinkList r;
    int n, c, e;
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->next = NULL;
    r = p;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &c, &e);
        Attach(c, e, r);
    }

    return p;
}

LinkList Add(LinkList P1, LinkList P2)
{
    LinkList p1 = P1->next, p2 = P2->next, r;
    LNode *P = (LNode *)malloc(sizeof(LNode));
    r = P;
    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            Attach(p1->coef, p1->exp, r);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            Attach(p2->coef, p2->exp, r);
            p2 = p2->next;
        } else {
            if (p1->coef + p2->coef != 0)
                Attach(p1->coef + p2->coef, p1->exp, r);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1) {
        Attach(p1->coef, p1->exp, r);
        p1 = p1->next;
    }
    while (p2) {
        Attach(p2->coef, p2->exp, r);
        p2 = p2->next;
    }
    return P;
}

LinkList Mult(LinkList P1, LinkList P2)
{
    LinkList P = (LinkList)malloc(sizeof(LNode));
    P->next = NULL;
    if (!P1->next || !P2->next) return P;  // 处理空输入

    LinkList p1 = P1->next;                // 从第一个数据节点开始
    while (p1) {
        LinkList p2 = P2->next;            // 从第一个数据节点开始
        LinkList r = P;
        while (p2) {
            int c = p1->coef * p2->coef;
            int e = p1->exp + p2->exp;
            while (r->next && r->next->exp > e) // 寻找插入位置
                r = r->next;
            if (r->next && r->next->exp == e) { // 等于 e 时要特殊处理
                r->next->coef += c;
                if (r->next->coef == 0) {  // 合并后系数为零则删除
                    LinkList t = r->next;
                    r->next = t->next;
                    free(t);
                }
            } else {  // r->next->exp < e 时，插入新项结点
                LinkList t = (LinkList)malloc(sizeof(LNode));
                t->coef = c;
                t->exp = e;
                t->next = r->next;
                r->next = t;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return P;
}

void PrintPoly(LinkList P)
{
    if (!P) return;
    LinkList p = P->next;
    if (p == NULL) {
        printf("0 0\n");
        return;
    }
    while (p != NULL) {
        printf("%d %d", p->coef, p->exp);
        p = p->next;
        if (p != NULL)
            printf(" ");
    }
    printf("\n");
}

void FreePoly(LinkList P) {
    LinkList p = P;
    while (p) {
        LinkList t = p;
        p = p->next;
        free(t);
    }
}

int main()
{
    LinkList P1, P2, PP, PS;
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Mult(P1, P2);
    PrintPoly(PP);
    PS = Add(P1, P2);
    PrintPoly(PS);

    FreePoly(PS);
    FreePoly(PP);
    FreePoly(P1);
    FreePoly(P2);

    return 0;
}