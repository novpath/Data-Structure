#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

enum EntryType { Legitimate, Empty };

typedef struct HashEntry {
    ElementType Element;
    enum EntryType Info;
} HashEntry;

typedef struct HashTbl {
    int TableSize;
    struct HashEntry *TheCells;
} HashTbl, *HashTable;

HashTable InitializeTable(int TableSize)
{
    HashTable H = (HashTable) malloc(sizeof(struct HashTbl));
    if (H == NULL)
        return NULL;
    H->TableSize = TableSize;
    H->TheCells = (HashEntry *) malloc(sizeof(struct HashEntry) * H->TableSize);
    while (TableSize)
        H->TheCells[--TableSize].Info = Empty;
    return H;
}

int Hash(ElementType Key, int P)  // 除留余数法散列函数
{
    return Key % P;
}

int Find(HashTable H, ElementType Key)    // 返回 key 的位置或者适合插入 key 的位置
{
    int pos = Hash(Key, H->TableSize);  // 先找到散列映射后的位置
    while (H->TheCells[pos].Info != Empty && H->TheCells[pos].Element != Key) {
        pos++;    // 若该位置已经被其他关键字占用，则线性探测下一个位置
        if (pos == H->TableSize)
            pos -= H->TableSize;
    }
    return pos;
}

void InsertAndOutput(ElementType key, HashTable H)
{
    int pos = Find(H, key);
    /* 找到 key 的位置或者适合插入 key 的位置 */
    if (H->TheCells[pos].Info == Empty) {  // 插入
        H->TheCells[pos].Info = Legitimate;
        H->TheCells[pos].Element = key;
    }
    printf("%d", pos);   // 输出
}

int main()
{
    int n, p, key;
    scanf("%d %d", &n, &p);
    HashTable H = InitializeTable(p);  // 创建散列表
    scanf("%d", &key);
    InsertAndOutput(key, H);          // 输出第 1 个关键字的位置
    for (int i = 1; i < n; i++) {
        scanf("%d", &key);
        printf(" ");            // 后续输出数字之前有空格
        InsertAndOutput(key, H);
    }
    printf("\n");

    free(H);
    return 0;
}
