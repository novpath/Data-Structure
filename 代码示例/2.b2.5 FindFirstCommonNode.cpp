/**
 * AcWing 66 原题 - Accepted
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int Length (struct ListNode *L)
{ 
    int len = 0;        // 计数变量，初始为 0
    struct ListNode *p = L;
    while (p != NULL) { 
        p = p->next;    // 不能写成 p++， p++是指向下一个指针类型位置，而 next 是指向下一结构
        len++;          // 每访问一个结点，计数加 1
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
