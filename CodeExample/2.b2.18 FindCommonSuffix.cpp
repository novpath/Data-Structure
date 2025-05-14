/**
 * AcWing 66 -Accepted
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *findFirstCommonNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *p = headA, *q = headB;
    int len1 = 0, len2 = 0;
    while (p != NULL) {
        len1++;
        p = p->next;
    }
    while (q != NULL) {
        len2++;
        q = q->next;
    }
    for (p = headA; len1 > len2; len1--)
        p = p->next;
    for (q = headB; len2 > len1; len2--)
        q = q->next;
    
    while (p != q && p != NULL) {
        p = p->next;
        q = q->next;
    }
    
    return p;
}
