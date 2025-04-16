/**
 * AcWing 33 ¿‡À∆ - Accepted 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 * 
 * Note: The returned array must be malloced, assume caller calls free().
 */
 
struct ListNode* findKthToTail(struct ListNode* pListHead, int k) {
    struct ListNode *p = pListHead, *q = p;
    int cnt = 0;
    while (p != NULL) {
        if (cnt < k) {
            p = p->next;
            cnt++;
        } else {
            p = p->next;
            q = q->next;
        }
    }
    if (cnt < k)
        return NULL;
    else
        return q; 
}
