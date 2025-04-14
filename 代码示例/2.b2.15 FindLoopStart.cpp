/**
 * leetcode LCR 022 ԭ��-Accepted 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *fast = head, *slow = head;             // ���ÿ�������ָ��
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;                        // ÿ����һ��
        fast = fast->next->next;                  // ÿ��������
        if (slow == fast) break;                  // ����
    }
    if (fast == NULL || fast->next == NULL)
        return NULL;                              // û�л�, ���� NULL
    struct ListNode *p1=head, *p2=slow;                     // �ֱ�ָ��ʼ�㡢������
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;                                   // ������ڵ�
}
