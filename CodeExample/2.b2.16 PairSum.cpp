/**
 * leetcode 2130 - Accepted
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 
int pairSum(struct ListNode* head) {
    struct ListNode *fast = head, *slow = head, *p;
    int pairsum;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        p = slow;
        slow = slow->next;
        p->next = head;
        head = p;
    }
    p = head;
    pairsum = p->val + slow->val;
    while (slow != NULL) {
        if (p->val + slow->val > pairsum)
            pairsum = p->val + slow->val;
        p = p->next;
        slow = slow->next;
    }

    return pairsum;
}
