#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} LNode, *LinkList;

void InitList(LinkList &L)
{
    L = NULL;
}

void BuildList(LinkList &L)
{
    int n;
    LinkList r = L;
    scanf("%d", &n);
    while (n != -1) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = n;
        s->next = NULL;
        if (r == NULL) {
            r = s;
            L = s;
        } else {
            r->next = s;
            r = s;
        }
        scanf("%d", &n);
    }
}

LinkList IntersectLinkList(LinkList L1, LinkList L2)
{
    LNode *L = (LNode *)malloc(sizeof(LNode));
    L = NULL;
    LNode *p = L1, *q = L2, *r = L;
    while (p != NULL && q != NULL) {
        if (p->data == q->data) {
            LNode *s = (LNode *)malloc(sizeof(LNode));
            s->data = p->data;
            s->next = NULL;
            if (r == NULL) {
                r = s;
                L = s;
            } else {
                r->next = s;
                r = s;
            }
            p = p->next;
            q = q->next;
        } else if (p->data < q->data) {
            p = p->next;
        } else {
            q = q->next;
        }
    }
    
    return L; 
}

int main()
{
    LNode *L1;
    LNode *L2;
    InitList(L1);
    InitList(L2);
    BuildList(L1);
    BuildList(L2);
    LNode *L = IntersectLinkList(L1, L2);
    
    LNode *p = L;
    if (p == NULL)
        printf("NULL");
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL)
            printf(" ");
        p = p->next;
    }
    
    return 0;
}

