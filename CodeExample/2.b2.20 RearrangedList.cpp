/**
 * AcWing 3757 - Accepted
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode LNode;
 
void rearrangedList(LNode* head) {
    LNode *p = head, *q = p, *r, *s;
    while (q->next != NULL && q->next->next != NULL) {
        p = p->next;
        q = q->next->next;
    }
    q = p->next;
    p->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }
    s = head;
    q = p->next;
    p->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = s->next;
        s->next = q;
        s = q->next;
        q = r;
    }
}
