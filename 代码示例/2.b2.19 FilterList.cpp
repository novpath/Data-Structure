/**
 * AcWing 3756 原题-Accepted 
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
    LNode *p = head, *q;                            // 工作指针，q 指向 p 前驱
    int *s = (int *)malloc(sizeof(int) * (n + 1));  // 申请 n+1 个位置的辅助空间
    for(int i = 0; i < n + 1; i++)             // 数组元素初值置为零
        *(s + i) = 0;
    while (p != NULL) {
        if (*(s + Abs(p->val)) == 0) {        // 判断该结点的 val 是否出现过
            *(s + Abs(p->val)) = 1;           // 首次出现，则将该位置的数组置为 1
            q = p;                             // 工作指针后移
            p = p->next;    
        } else {                               // 重复出现
            q->next = p->next;                 // 删除结点 p
            free(p);
            p = q->next;                       // 恢复指针，处理下一个结点
        }
    }
    free(s);                                   // 释放申请的数组空间
    return head;
}
