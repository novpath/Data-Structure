/**
 * AcWing 3756 ԭ��-Accepted 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 * 
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct ListNode LNode;
 
int Abs(int a)
{
    return (a > 0? a: -a);
}
 
LNode* filterList(LNode* head)
{
    int n = 10001;
    LNode *p = head, *q;                            // ����ָ�룬q ָ�� p ǰ��
    int *s = (int *)malloc(sizeof(int) * (n + 1));  // ���� n+1 ��λ�õĸ����ռ�
    for(int i = 0; i < n + 1; i++)             // ����Ԫ�س�ֵ��Ϊ��
        *(s + i) = 0;
    while (p != NULL) {
        if (*(s + Abs(p->val)) == 0) {        // �жϸý��� val �Ƿ���ֹ�
            *(s + Abs(p->val)) = 1;           // �״γ��֣��򽫸�λ�õ�������Ϊ 1
            q = p;                             // ����ָ�����
            p = p->next;    
        } else {                               // �ظ�����
            q->next = p->next;                 // ɾ����� p
            free(p);
            p = q->next;                       // �ָ�ָ�룬������һ�����
        }
    }
    free(s);                                   // �ͷ����������ռ�
    return head;
}
