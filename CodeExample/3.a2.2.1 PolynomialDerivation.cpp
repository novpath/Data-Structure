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
    int c, e;
    LNode *p = (LNode *)malloc(sizeof(LNode));
    p->next = NULL;
    r = p;
    while (scanf("%d %d", &c, &e) == 2)
        Attach(c, e, r);
    return p;
}

LinkList Derivation(const LinkList L)
{
    LinkList D = (LinkList)malloc(sizeof(LNode));
    LinkList p = L->next;
    LinkList r = D;
    D->next = NULL;
    while (p != NULL) {
        if (p->coef * p->exp != 0)
            Attach(p->coef * p->exp, p->exp - 1, r);
        p = p->next;
    }

    return D;
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
    LinkList P = ReadPoly();
    LinkList PD = Derivation(P);
    PrintPoly(PD);

    FreePoly(PD);
    FreePoly(P);
    return 0;
}