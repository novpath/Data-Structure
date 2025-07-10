#include <cstdio>
#include <cstdlib>
#define NULL nullptr

enum EntryType { Legitimate, Empty };

typedef struct HashEntry {
    int Element;
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

int Hash(HashTable H, int key)
{
    return key % H->TableSize;
}

int Find(HashTable H, int key)  // 返回 key 的位置或者适合插入 key 的位置
{
    int cnt = 0;                // 冲突次数
    int pos = Hash(H, key);     // 先找到散列映射后的位置
    int next = pos;
    while (H->TheCells[next].Info != Empty && H->TheCells[next].Element != key) {
        // 若该位置已经被其他关键字占用，则根据冲突发生的奇偶次计算探测步长
        ++cnt;
        next = ((pos + cnt * cnt) % H->TableSize + H->TableSize) % H->TableSize;  // 平方探测
        if (cnt == H->TableSize) {
            next = -1;
            break;
        }
    }
    return next;
}

void InsertAndOutput(HashTable H, int key)
{
    static int first = 1;
    int pos = Find(H, key);
    /* 找到 key 的位置或者适合插入 key 的位置 */
    if (pos != -1 && H->TheCells[pos].Info == Empty) {  // 插入
        H->TheCells[pos].Info = Legitimate;
        H->TheCells[pos].Element = key;
    }
    if (first == 1) {
        first = 0;
    } else {
        printf(" ");
    }
    if (pos != -1)
        printf("%d", pos);   // 输出
    else
        printf("-");
}

int NextPrime(int n)
{
    if (n <= 2)
        return 2;
    for (int i = n; ; i++) {
        int isPrime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime == true)
            return i;
    }
}

int main()
{
    int mSize, n;
    scanf("%d %d", &mSize, &n);
    mSize = NextPrime(mSize);
    HashTable H = InitializeTable(mSize);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        InsertAndOutput(H, a);
    }

    free(H);
    return 0;
}
