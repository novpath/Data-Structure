#include <cstdio>
#include <cstdlib>
#include <cstring>
#define NULL nullptr
#define IDLength 19

typedef struct LNode {
    int mileage;
    char id[IDLength];
    struct LNode *next;
} LNode, *LinkList;

typedef struct HashTbl {
    int tableSize;
    LinkList head;
} HashTbl, *HashTable;

HashTable InitializeTable(int tableSize)
{
    HashTable H = (HashTable) malloc(sizeof(LNode));
    if (H == NULL)
        return NULL;
    H->tableSize = tableSize;
    H->head = (LinkList) malloc(sizeof(LNode) * H->tableSize);
    for (int i = 0; i < tableSize; i++) {
        H->head[i].mileage = 0;
        H->head[i].next = NULL;
        H->head[i].id[0] = '\0';
    }
    return H;
}

int Hash(HashTable H, int key)
{
    return key % H->tableSize;
}

int AtoiID(const char *key)
{
    int H = 0;
    H = (key[9] - '0') * 10 + (key[11] - '0');
    H = H * 10 + (key[13] - '0');
    H = H * 10 + (key[15] - '0');
    H = H * 10 + (key[16] - '0');
    H = H * 10 + ((key[17] == 'x') ? 10 : (key[17] - '0'));
    return H;
}

LinkList Find(HashTable H, const char *id)
{
    int pos = Hash(H, AtoiID(id));
    LinkList p = H->head[pos].next;
    while (p && strcmp(p->id, id) != 0)
        p = p->next;

    return p;
}

void Insert(HashTable H, const char *id, int mileage)
{
    LinkList p = Find(H, id);
    if (p != NULL) {
        p->mileage += mileage;
    } else {
        LinkList newNode = (LinkList) malloc(sizeof(LNode));
        strcpy(newNode->id, id);
        newNode->mileage = mileage;
        int pos = Hash(H, AtoiID(id));
        newNode->next = H->head[pos].next;
        H->head[pos].next = newNode;
    }
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

void DestroyHashTable(HashTable H)
{
    for (int i = 0; i < H->tableSize; i++) {
        LinkList p = H->head[i].next;
        while (p != NULL) {
            LinkList t = p;
            p = p->next;
            free(t);
        }
    }
    free(H->head);
    free(H);
}

int main()
{
    int n, k;
    char ID[IDLength];
    int mileage;
    scanf("%d %d", &n, &k);
    HashTable H = InitializeTable(NextPrime(n));
    if (H == NULL)
        return -1;
    for (int i = 0; i < n; i++) {
        scanf("%s %d", ID, &mileage);
        Insert(H, ID, mileage >= k ? mileage : k);
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", ID);
        LinkList p = Find(H, ID);
        while (p != NULL) {
            if (strcmp(p->id, ID) == 0) {
                printf("%d\n", p->mileage);
                break;
            }
            p = p->next;
        }
        if (p == NULL)
            printf("No Info\n");
    }

    DestroyHashTable(H);
    return 0;
}
