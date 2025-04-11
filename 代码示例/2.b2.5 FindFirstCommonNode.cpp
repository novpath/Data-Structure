/**
 * AcWing 66 ԭ�� - Accepted
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int Length (struct ListNode *L)
{ 
    int len = 0;        // ������������ʼΪ 0
    struct ListNode *p = L;
    while (p != NULL) { 
        p = p->next;    // ����д�� p++�� p++��ָ����һ��ָ������λ�ã��� next ��ָ����һ�ṹ
        len++;          // ÿ����һ����㣬������ 1
    } 
    return len;
}
 
struct ListNode *findFirstCommonNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *p = headA, *q = headB;
    int len1 = Length(headA);
    int len2 = Length(headB);
    int k = (len1 > len2 ? len1 - len2 : len2 - len1);
    if (len1 > len2) {
        for (int i = 0; i < k; i++) p = p->next;
    } else {
        for (int i = 0; i < k; i++) q = q->next;
    }
    while (p != NULL) {
        if (p == q) return p;
        p = p->next;
        q = q->next;
    }
    return NULL;
}
