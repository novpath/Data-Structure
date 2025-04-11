/**
 * Leetcode 83 原题 - Accepted 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 
 /* 方法一：直接删除 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (head == NULL) return head;
    struct ListNode *p = head, *q;
    while (p -> next != NULL) {
        q = p->next;
        if (p->val == q->val) {
            p->next = q->next;
            free(q);
        } else {
            p = p->next;
        }
    }
    return head;
}

/* 方法二：尾插法 */ 
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (head == NULL) return head;
    struct ListNode *r = head;
    struct ListNode *p = r->next;
    while (p != NULL) {
        if (p->val != r->val) {
            r->next = p;
            r = p;
            p = p->next;
        } else {
           struct ListNode *q = p;
           p = p->next;
           free(q);
        }
    }
    r->next = NULL;
    return head;
}
