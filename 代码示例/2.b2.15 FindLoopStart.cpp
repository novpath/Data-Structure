/**
 * leetcode LCR 022 原题-Accepted 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *fast = head, *slow = head;             // 设置快慢两个指针
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;                        // 每次走一步
        fast = fast->next->next;                  // 每次走两步
        if (slow == fast) break;                  // 相遇
    }
    if (fast == NULL || fast->next == NULL)
        return NULL;                              // 没有环, 返回 NULL
    struct ListNode *p1=head, *p2=slow;                     // 分别指向开始点、相遇点
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;                                   // 返回入口点
}
