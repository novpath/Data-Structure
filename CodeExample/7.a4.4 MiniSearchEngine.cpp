#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#define NULL nullptr
#define MaxNextPrime 500009
#define Mask 32767
typedef char Element[51]; // 每行字符最多50个

typedef struct LNode {    // 行号结点
    int LineID;
    struct LNode *nextLine;
} LNode, *LinkList;

char word[101][101][51];  // 注意由于将#号也存入在word数组中，故文件行号最大101行
int F[101];
int L[101][101];
int ans = 0;

typedef struct FNode {   // 文件结点
    int fileID;
    struct FNode *nextFile;
    LinkList line;
} FNode, *FList;

typedef struct HashEntry {  // 哈希结点
    Element word;
    int flag;
    FList next;
} HashEntry;

typedef struct HashTbl {    // 哈希表
    int TableSize;
    struct HashEntry *TheCells;
} HashTbl, *HashTable;

LNode *CreateLNode(int LineID)  // 创建行号结点
{
    LNode *l = (LNode *) malloc(sizeof(LNode));
    l->LineID = LineID;
    l->nextLine = NULL;
    return l;
}

FNode *CreateFNode(int fileID, LNode *l)  // 创建文件结点
{
    FNode *f = (FNode *) malloc(sizeof(FNode));
    f->fileID = fileID;
    f->nextFile = NULL;
    f->line = l;
    return f;
}

HashTable Create(int size)    // 哈希表初始化
{
    HashTable H = (HashTable) malloc(sizeof(HashTable));
    if (H == NULL)
        return NULL;
    H->TableSize = size;
    H->TheCells = (struct HashEntry *) malloc(sizeof(HashEntry) * size);
    while (size) {
        H->TheCells[--size].next = NULL;
        H->TheCells[size].flag = 0;
    }
    return H;
}

int Hash(HashTable H, Element Key)     // 哈希函数
{
    unsigned int h = 0;
    while (*Key != '\0') {
        h = h << 5 + (*Key++ - 'a');
    }
    return (int) (h & Mask) % H->TableSize;
}

int FindPos(HashTable H, Element Key) // 寻找存储位置
{
    int pos = Hash(H, Key);
    while (H->TheCells[pos].flag && strcmp(H->TheCells[pos].word, Key) != 0) {
        pos++;
        if (pos == H->TableSize)
            pos -= H->TableSize;
    }
    return pos;
}

void Insert(HashTable H, Element Key, int fileID, int LineID)  // 单词插入
{
    int pos = FindPos(H, Key);
    if (!H->TheCells[pos].flag) {                              // 位置为空则插入
        strcpy(H->TheCells[pos].word, Key);
        H->TheCells[pos].flag = 1;
        LNode *l = CreateLNode(LineID);
        FNode *f = CreateFNode(fileID, l);
        H->TheCells[pos].next = f;
    } else if (strcmp(H->TheCells[pos].word, Key) == 0) {     // 位置不空且存储单词一致
        FNode *p = H->TheCells[pos].next;
        FNode *s = NULL;
        while (p && p->fileID != fileID) {                    // 文件号不空且文件号不等
            s = p;
            p = p->nextFile;
        }
        if (!p) {                                   // 文件指针空，尾插
            LNode *l = CreateLNode(LineID);
            FNode *f = CreateFNode(fileID, l);
            s->nextFile = f;
        } else if (p->fileID == fileID) {           // 文件号一致，则比较行号
            LNode *q = p->line;
            LNode *r = NULL;;
            while (q && q->LineID != LineID) {
                r = q;
                q = q->nextLine;
            }
            if (!q) {
                LNode *l = CreateLNode(LineID);   // 行号指针空，尾插
                r->nextLine = l;
            }
        }
    }
}

void GetWord(HashTable H, Element word, int fileID, int LineID) // 分词
{
    int i = 0, k = 0;
    Element str;
    while (word[i] != '\0') {
        if (isalpha(word[i])) {
            str[k++] = (char) tolower(word[i]);
        } else {
            if (isalpha(word[i + 1])) {
                str[k] = '\0';
                Insert(H, str, fileID, LineID);
                k = 0;
            }
        }
        i++;
    }
    str[k] = '\0';
    Insert(H, str, fileID, LineID);
}

int Merge(HashTable H, FNode *p)   // 求文件名交集，行号并集
{
    int w = 0;
    int tmpF[101];
    int tmpL[101];
    int v = 0;
    while (p && F[w] != -1) {
        if (F[w] > p->fileID) {
            p = p->nextFile;
        } else if (F[w] < p->fileID) {
            w++;
        } else if (F[w] == p->fileID) {
            tmpF[v++] = p->fileID;
            LNode *q = p->line;
            int u = 0, h = 0;
            while (q && L[p->fileID][u] != -1) {
                if (q->LineID < L[p->fileID][u]) {
                    tmpL[h++] = q->LineID;
                    q = q->nextLine;
                } else if (q->LineID > L[p->fileID][u]) {
                    tmpL[h++] = L[p->fileID][u];
                    u++;
                } else {
                    tmpL[h++] = q->LineID;
                    u++;
                    q = q->nextLine;
                }
            }
            while (q && L[p->fileID][u] == -1) {
                tmpL[h++] = q->LineID;
                q = q->nextLine;
            }
            while (!q && L[p->fileID][u] != -1) {
                tmpL[h++] = L[p->fileID][u];
                u++;
            }
            int i;
            for (i = 0; i < h; i++) {
                L[p->fileID][i] = tmpL[i];
            }
            L[p->fileID][i] = -1;
            w++;
            p = p->nextFile;
        }
    }
    int i;
    for (i = 0; i < v; i++) {
        F[i] = tmpF[i];
    }
    F[i] = -1;
    ans = v;
    return v;
}

void Out()   // 输出
{
    for (int i = 0; F[i] != -1; i++) {
        printf("%s\n", word[F[i]][0]);
        for (int t = 0; L[F[i]][t] != -1; t++) {
            int line = L[F[i]][t];
            printf("%s\n", word[F[i]][line]);
        }
    }
}

int Get(HashTable H, Element str)      // 求首个单词的文件名和行号
{
    int flag = 0;
    int pos = FindPos(H, str);
    FNode *p = H->TheCells[pos].next;
    if (!p) {
        flag = 1;
        printf("0\nNot Found\n");
    } else {
        int t = 0;
        while (p) {
            int s = 0;
            F[t++] = p->fileID;
            LNode *q = p->line;
            while (q) {
                L[p->fileID][s++] = q->LineID;
                q = q->nextLine;
            }
            L[p->fileID][s] = -1;
            p = p->nextFile;
        }
        F[t] = -1;
        ans = t;
    }
    return flag;
}

void GetAns(HashTable H)   // 最终结果
{
    int m;
    scanf("%d", &m);
    char str[10][11];
    char c;
    getchar();
    for (int i = 0; i < m; i++) {
        int flag = 0;
        int j = 0, k = 0;
        while (c = (char) getchar(), c != '\n') {
            if (isalpha(c))
                str[j][k++] = (char) tolower(c);
            else {
                str[j][k] = '\0';
                j++;
                k = 0;
            }
        }
        str[j][k] = '\0';
        j++;
        flag = Get(H, str[0]);
        if (!flag) {
            if (j > 1) {
                for (k = 1; k < j; k++) {
                    int pos = FindPos(H, str[k]);
                    FNode *p = H->TheCells[pos].next;
                    flag = Merge(H, p);
                    if (!flag) {
                        printf("0\nNot Found\n");
                        break;
                    }
                }
                if (flag) {
                    printf("%d\n", ans);
                    Out();
                }
            } else if (j == 1) {
                printf("%d\n", ans);
                Out();
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    getchar();
    HashTable H = Create(MaxNextPrime);
    if (H == NULL)
        return -1;
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (scanf(" %[^\n]", word[i][j]), strcmp(word[i][j], "#") != 0) {
            if (j)
                GetWord(H, word[i][j], i, j);
            j++;
        }
    }
    GetAns(H);

    return 0;
}
