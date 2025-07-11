#include <cstdio>
#include <cstdlib>
#include <cstring>

#define KeyLength 11  // 电话号码长度
#define MaxD 5        // 参与散列映射计算的字符个数
typedef char ElementType[KeyLength + 1];

typedef struct LNode {
    ElementType data;
    struct LNode *next;
    int count;
} LNode, *LinkList;

typedef struct TblNode {
    int tableSize;
    LinkList head;
} TblNode, *HashTable;

int NextPrime(int n)
{
    if (n <= 2)
        return 2;
    for (int i = n; ; i++) {
        int isPrime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime)
            return i;
    }
}

int Hash(int key, int p)
{
    return key % p;
}

HashTable CreateHashTable(int TableSize)
{
    HashTable H = (HashTable) malloc(sizeof(TblNode));
    if (H == NULL)
        return NULL;
    H->tableSize = TableSize;
    H->head = (LinkList) malloc(H->tableSize * sizeof(LNode));
    for (int i = 0; i < H->tableSize; i++) {
        H->head[i].data[0] = '\0';
        H->head[i].next = NULL;
        H->head[i].count = 0;
    }
    return H;
}

LinkList Find(HashTable H, ElementType key)
{
    int pos = Hash(atoi(key + KeyLength - MaxD), H->tableSize);
    LinkList p = H->head[pos].next;
    while (p && strcmp(p->data, key))
        p = p->next;

    return p;
}

bool Insert(HashTable H, ElementType key)
{
    LinkList p = Find(H, key);
    if (p == NULL) {
        LinkList newCell = (LinkList) malloc(sizeof(LNode));
        strcpy(newCell->data, key);
        newCell->count = 1;
        int pos = Hash(atoi(key + KeyLength - MaxD), H->tableSize);
        newCell->next = H->head[pos].next;
        H->head[pos].next = newCell;
        return true;
    }
    p->count++;
    return false;
}

void ScanAndOutput(HashTable H)
{
    int MaxCnt = 0, PCnt = 0;
    ElementType MinPhone = "\0";
    for (int i = 0; i < H->tableSize; i++) {
        LinkList ptr = H->head[i].next;
        while (ptr) {
            if (ptr->count > MaxCnt) {
                MaxCnt = ptr->count;
                strcpy(MinPhone, ptr->data);
                PCnt = 1;
            } else if (ptr->count == MaxCnt) {
                PCnt++;
                if (strcmp(MinPhone, ptr->data) > 0)
                    strcpy(MinPhone, ptr->data);
            }
            ptr = ptr->next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if (PCnt > 1) printf(" %d", PCnt);
    printf("\n");
}

void DestroyHashTable(HashTable H)
{
    for (int i = 0; i < H->tableSize; i++) {
        LinkList p = H->head[i].next;
        while (p != NULL) {
            LinkList t = p->next;
            free(p);
            p = t;
        }
    }
    free(H->head);
    free(H);
}

int main()
{
    int n;
    ElementType key;
    scanf("%d", &n);
    HashTable H = CreateHashTable(n * 2);
    if (H == NULL)
        return -1;
    for (int i = 0; i < n; i++) {
        scanf("%s", key);
        Insert(H, key);
        scanf("%s", key);
        Insert(H, key);
    }
    ScanAndOutput(H);
    DestroyHashTable(H);
    return 0;
}
