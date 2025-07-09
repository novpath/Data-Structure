#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define KEYLENGTH 15                   /* 关键词字符串的最大长度 */
typedef char ElementType[KEYLENGTH + 1]; /* 关键词类型用字符串 */
typedef int Index;                     /* 散列地址类型 */
typedef enum { false, true } bool;

typedef struct LNode *PtrToLNode;

struct LNode {
    ElementType Data;
    PtrToLNode Next;
};

typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    List Heads;    /* 指向链表头结点的数组 */
};

Index Hash(ElementType Key, int TableSize)
{
    return (Key[0] - 'a') % TableSize;
}

HashTable BuildTable(); /* 裁判实现，细节不表 */
bool Delete(HashTable H, ElementType Key);

int main()
{
    ElementType Key;

    HashTable H = BuildTable();
    scanf("%s", Key);
    if (Delete(H, Key) == false)
        printf("ERROR: %s is not found\n", Key);
    if (Delete(H, Key) == true)
        printf("Are you kidding me?\n");
    return 0;
}

/* 你的代码将被嵌在这里 */
bool Delete(HashTable H, ElementType key)
{
    Index pos = Hash(key, H->TableSize);   // 计算散列值
    Position P = H->Heads + pos;           // 指向对应链表的头结点
    /* 当 P 的下一个结点不是 key 时 */
    while (P->Next && strcmp(P->Next->Data, key))
        P = P->Next;       // 逐一扫描链表
    if (!P->Next)          // 如果直到表尾都没找到
        return false;
    Position t = P->Next;  // 找到了 P 的下一个结点是 key，将其删除
    P->Next = t->Next;
    free(t);
    printf("%s is deleted from list Heads[%d]\n", key, pos);
    return true;
}
