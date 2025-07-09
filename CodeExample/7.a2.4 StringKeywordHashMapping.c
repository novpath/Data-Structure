#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxStringLen 8
#define MaxHashCh 3
#define MaxChBit 5
#define Mask ((1 << (MaxHashCh * MaxChBit))-1)

typedef char ElementType[MaxStringLen + 1];

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

int Hash(char *Key, int P)  // 字符串 key 最后 D 位位移法散列函数
{
    int h = 0;
    while (*Key != '\0')
        h = (h << MaxChBit) + (*Key++ - 'A');
    return ((h & Mask) % P);
}

int Find(HashTable H, char *Key)    // 返回 key 的位置或者适合插入 key 的位置
{
    int inc, cnt = 0;           /* 冲突次数 */
    int pos = Hash(Key, H->TableSize);  // 先找到散列映射后的位置
    int next = pos;
    while (H->TheCells[next].Info != Empty && (strcmp(H->TheCells[next].Element, Key))) {
        // 若该位置已经被其他关键字占用，则根据冲突发生的奇偶次计算探测步长
        if (++cnt % 2) // 奇数次冲突
            inc = ((cnt + 1) * (cnt + 1)) >> 2;
        else
            inc = -(cnt * cnt) >> 2;
        next = pos + inc;  // 平方探测
        if (next < 0) next += H->TableSize;
        else if (next >= H->TableSize)
            next -= H->TableSize;
    }
    return next;
}

void InsertAndOutput(ElementType key, HashTable H)
{
    int pos = Find(H, key);
    /* 找到 key 的位置或者适合插入 key 的位置 */
    if (H->TheCells[pos].Info == Empty) {  // 插入
        H->TheCells[pos].Info = Legitimate;
        strcpy(H->TheCells[pos].Element, key);
    }
    printf("%d", pos);   // 输出
}

int main()
{
    int n, p;
    ElementType key;
    scanf("%d %d", &n, &p);
    HashTable H = InitializeTable(p);  // 创建散列表
    scanf("%s", &key);
    InsertAndOutput(key, H);          // 输出第 1 个关键字的位置
    for (int i = 1; i < n; i++) {
        scanf("%s", &key);
        printf(" ");            // 后续输出数字之前有空格
        InsertAndOutput(key, H);
    }

    free(H);
    return 0;
}
