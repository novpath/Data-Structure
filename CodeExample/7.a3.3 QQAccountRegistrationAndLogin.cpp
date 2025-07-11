#include <cstdio>
#include <cstdlib>
#include <cstring>
#define NULL nullptr
#define AccountLen 11
#define PasswordLen 17

typedef struct HashEntry {
    char account[AccountLen];
    char password[PasswordLen];
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
        strcpy(H->TheCells[--TableSize].account, "0");
    return H;
}

int Hash(HashTable H, int key)
{
    return key % H->TableSize;
}

int Find(HashTable H, const char *key)  // 返回 key 的位置或者适合插入 key 的位置
{
    int inc = 0, cnt = 0;         // 冲突次数
    int pos = Hash(H, atoi(key + 1));     // 先找到散列映射后的位置
    int next = pos;
    while (strcmp(H->TheCells[next].account, "0") != 0 && strcmp(H->TheCells[next].account, key) != 0) {
        // 若该位置已经被其他关键字占用，则根据冲突发生的奇偶次计算探测步长
        if (++cnt % 2) {
            inc = ((cnt + 1) * (cnt + 1)) >> 2;
        } else {
            inc = (-cnt * cnt) >> 2;
        }
        next = ((pos + inc) % H->TableSize + H->TableSize) % H->TableSize;  // 平方探测
    }
    return next;
}

void Insert(HashTable H, const char *account, const char *password)
{
    int pos = Find(H, account);
    /* 找到 key 的位置或者适合插入 key 的位置 */
    if (strcmp(H->TheCells[pos].account, "0") == 0) {  // 插入
        strcpy(H->TheCells[pos].account, account);
        strcpy(H->TheCells[pos].password, password);
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
        if (isPrime == true && i % 4 == 3)
            return i;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    HashTable H = InitializeTable(NextPrime(n));
    if (H == NULL)
        return -1;
    for (int i = 0; i < n; i++) {
        char op[2];
        char account[11];
        char password[17];
        scanf("%s %s %s", op, account, password);
        int pos = Find(H, account);
        if (*op == 'L') {
            if (strcmp(H->TheCells[pos].account, "0") == 0) {
                printf("ERROR: Not Exist\n");
            } else if (strcmp(H->TheCells[pos].password, password) == 0) {
                printf("Login: OK\n");
            } else {
                printf("ERROR: Wrong PW\n");
            }
        } else if (*op == 'N') {
            if (strcmp(H->TheCells[pos].account, account) == 0) {
                printf("ERROR: Exist\n");
            } else {
                Insert(H, account, password);
                printf("New: OK\n");
            }
        }
    }

    free(H->TheCells);
    free(H);
    return 0;
}
