#include <stdio.h>

#define MAXTABLESIZE 100000  /* 允许开辟的最大散列表长度 */
typedef int ElementType;     /* 关键词类型用整型 */
typedef int Index;           /* 散列地址类型 */
typedef Index Position;      /* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum { Legitimate, Empty, Deleted } EntryType;

typedef struct HashEntry Cell; /* 散列表单元类型 */
struct HashEntry {
    ElementType Data; /* 存放元素 */
    EntryType Info;   /* 单元状态 */
};

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    Cell *Cells;   /* 存放散列单元数据的数组 */
};

HashTable BuildTable(); /* 裁判实现，细节不表 */
Position Hash(ElementType Key, int TableSize)
{
    return (Key % TableSize);
}

#define ERROR (-1)
Position Find(HashTable H, ElementType Key);

int main()
{
    ElementType Key;

    HashTable H = BuildTable();
    scanf("%d", &Key);
    Position P = Find(H, Key);
    if (P == ERROR)
        printf("ERROR: %d is not found and the table is full.\n", Key);
    else if (H->Cells[P].Info == Legitimate)
        printf("%d is at position %d.\n", Key, P);
    else
        printf("%d is not found.  Position %d is returned.\n", Key, P);

    return 0;
}

/* 你的代码将被嵌在这里 */
Position Find(HashTable H, ElementType key)
{
    Position currentPos;            // 从散列地址开始
    Position newPos = currentPos = Hash(key, H->TableSize);
    while (H->Cells[newPos].Info != Empty && H->Cells[newPos].Data != key) { // 单元不空但不是 key
        newPos++;                   // 线性探测
        if (newPos >= H->TableSize) // 表尾折返回表头
            newPos -= H->TableSize;
        if (newPos == currentPos) return ERROR; // 回到出发地，说明表满了
    }
    return newPos;      // 此时或者遇到空单元，或者找到 key
}
