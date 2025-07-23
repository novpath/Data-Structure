#include <cstdio>
#include <cstdlib>
#include <cstring>
#define NULL nullptr
#define KeyLength 141
#define StrLength 141

typedef struct LNode {
    int count;
    char str[KeyLength];
    struct LNode *next;
    int lastVisit;
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
        H->head[i].count = 0;
        H->head[i].next = NULL;
        H->head[i].str[0] = '\0';
        H->head[i].lastVisit = -1;
    }
    return H;
}

int Hash(HashTable H, const char *str)
{
    int hash = 0;
    while (*str) {
        hash = hash * 131 + (*str++);
    }
    return (hash % H->tableSize + H->tableSize) % H->tableSize;
}

LinkList Find(HashTable H, const char *str)
{
    int pos = Hash(H, str);
    LinkList p = H->head[pos].next;
    while (p && strcmp(p->str, str) != 0)
        p = p->next;

    return p;
}

void Insert(HashTable H, const char *str, int lastVist)
{
    LinkList p = Find(H, str);
    if (p != NULL) {
        if (p->lastVisit != lastVist)
            p->count++;
        p->lastVisit = lastVist;
    } else {
        LinkList newNode = (LinkList) malloc(sizeof(LNode));
        strcpy(newNode->str, str);
        newNode->count = 1;
        newNode->lastVisit = lastVist;
        int pos = Hash(H, str);
        LinkList pre = H->head[pos].next;
        if (pre == NULL) {
            newNode->next = H->head[pos].next;
            H->head[pos].next = newNode;
        } else {
            while (pre->next && strcmp(str, pre->next->str) > 0) {
                pre = pre->next;
            }
            newNode->next = pre->next;
            pre->next = newNode;
        }
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

bool IsNum(const char c)
{
    return c >= '0' && c <= '9';
}

bool IsAlpha(const char c)
{
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

void GetTopic(HashTable H, const char *str, int lastVisit)
{
    int i = 0, idx = 0;        // 字符串遍历索引和 keyword 数组的索引
    int state = 0;             // 状态机: 0=等待第一个# 1=已找到第一个#
    char keyword[KeyLength];   // 存储提取的关键字
    int meetSpace = 0;         // 标记上一个字符是否为空格

    while (str[i] != '\0') {
        // 状态0: 等待第一个#
        if (state == 0 && str[i] == '#') {
            state = 1; // 找到第一个#，进入提取状态
            idx = 0;   // 初始化
        }
        if (state == 1) {
            // 处理有效字符（字母/数字/空格）
            char c = str[i];
            // 字母转小写
            if (IsAlpha(c) && c >= 'A' && c <= 'Z') {
                c = (char) (c - 'A' + 'a');
            }
            if (IsNum(c) || IsAlpha(c)) {    // 数字和字母直接添加
                keyword[idx++] = c;
                meetSpace = 0;
            } else {  // 空格处理：多个空格合并为一个
                if (!meetSpace && idx > 0) {
                    keyword[idx++] = ' ';
                    meetSpace = 1;
                }
            }
            // 找到两个#号时或者关键字溢出时结束提取
            if (str[i] == '#' && idx != 0 || idx >= KeyLength - 1) {
                state = 0;
                // 确保字符串以null结尾
                keyword[--idx] = '\0';
                // 将热词插入散列表
                Insert(H, keyword, lastVisit);
            }
        }
        i++;
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
    int n;
    char str[StrLength];
    scanf("%d", &n);
    HashTable H = InitializeTable(NextPrime(n));
    if (H == NULL)
        return -1;
    for (int i = 0; i < n; i++) {
        scanf(" %[^\n]", str);
        GetTopic(H, str, i);
    }
    LinkList p;
    int maxCount = 0;
    char hotTopic[KeyLength] = "";
    for (int i = 0; i < H->tableSize; i++) {
        p = H->head[i].next;
        while (p) {
            if (p->count > maxCount)
                maxCount = p->count;
            p = p->next;
        }
    }
    int maxTopicsNum = 0;
    for (int i = 0; i < H->tableSize; i++) {
        p = H->head[i].next;
        while (p) {
            if (p->count == maxCount) {
                maxTopicsNum++;
                if (strcmp("\0", hotTopic) == 0 || strcmp(p->str, hotTopic) < 0)
                    strcpy(hotTopic, p->str);
            }
            p = p->next;
        }
    }

    if (hotTopic[0] >= 'a' && hotTopic[0] <= 'z')
        hotTopic[0] = (char) (hotTopic[0] - 'a' + 'A');
    printf("%s\n", hotTopic);
    printf("%d\n", maxCount);
    if (maxTopicsNum >= 2)
        printf("And %d more ...", maxTopicsNum - 1);

    DestroyHashTable(H);
    return 0;
}
