#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#define NULL nullptr
#define MaxNextPrime 500009
#define MaxS 10
#define MinS 3
#define MaxB 5

typedef char Element[MaxS + 1];

typedef struct FileEntry {
    int fileID;
    struct FileEntry *next;
} FileEntry, *FList;

typedef struct WordEntry {
    int words;
    struct WordEntry *next;
} WordEntry, *WList;

struct HashEntry {
    int fileID;
    Element word;
    FList invIndex;
};

typedef struct HashTbl {
    int tableSize;
    struct HashEntry *theCells;
} HashTbl, *HashTable;

HashTable InitialHashTable(int size);                   // 哈希表初始化
WList CreateWordList(int size);                         // 文件单词表初始化
int Hash(Element Key, int P);                           // 哈希函数
int Find(HashTable H, Element Key);                     // 获取存储位置
int FindAndInsert(HashTable H, Element Key, int FileID);// 插入哈希表（头插法）
void FileInsert(WList File, int Pos, int FileID);       // 插入文件单词表（头插法）
int GetWord(Element Word);                              // 获取单词
double CalSim(HashTable H, WList File, int F1, int F2); // 计算公共词汇量占两文件总词汇量的百分比

int main()
{
    int n, m, F1, F2;
    Element Word;

    scanf("%d", &n);
    HashTable H = InitialHashTable(MaxNextPrime);
    WList File = CreateWordList(n + 1);
    if (H == NULL || File == NULL)
        return -1;

    for (int i = 1; i <= n; i++) {
        while (GetWord(Word))
            FileInsert(File, FindAndInsert(H, Word, i), i);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &F1, &F2);
        printf("%.1lf%%%c", CalSim(H, File, F1, F2), i == m - 1 ? '\0' : '\n');
    }
    free(H->theCells);
    free(H);
    free(File);
    return 0;
}

HashTable InitialHashTable(int size)
{
    HashTable H = (HashTable) malloc(sizeof(struct HashTbl));
    if (H == NULL)
        return NULL;
    H->theCells = (HashEntry *) malloc(sizeof(struct HashEntry) * size);
    H->tableSize = size;
    while (size) {
        H->theCells[--size].invIndex = NULL;
        H->theCells[size].fileID = 0;
    }
    return H;
}

WList CreateWordList(int size)
{
    WList F = (WList) malloc(sizeof(struct WordEntry) * size);
    while (size) {
        F[--size].words = 0;
        F[size].next = NULL;
    }
    return F;
}

int Hash(Element Key, int P)
{
    int h = 0;
    while (*Key != '\0') {
        h = (h << MaxB) + (*Key++ - 'a');
    }
    return (h % P + P) % P;
}

int Find(HashTable H, Element Key)
{
    int Pos = Hash(Key, H->tableSize);
    while (H->theCells[Pos].fileID && strcmp(H->theCells[Pos].word, Key) != 0) {
        Pos++;
        if (Pos == H->tableSize)
            Pos -= H->tableSize;
    }
    return Pos;
}

int FindAndInsert(HashTable H, Element Key, int FileID)
{
    int Pos = Find(H, Key);
    if (H->theCells[Pos].fileID != FileID) {
        if (H->theCells[Pos].fileID == 0)
            strcpy(H->theCells[Pos].word, Key);
        H->theCells[Pos].fileID = FileID;

        FList node = (FList) malloc(sizeof(struct FileEntry));
        node->fileID = FileID;
        node->next = H->theCells[Pos].invIndex;
        H->theCells[Pos].invIndex = node;
        return Pos;
    }
    return -1;
}

void FileInsert(WList File, int Pos, int FileID)
{
    if (Pos < 0)return;
    WList W = (WList) malloc(sizeof(struct WordEntry));
    W->words = Pos;
    W->next = File[FileID].next;
    File[FileID].next = W;
    File[FileID].words++;
}

int GetWord(Element Word)
{
    char c;
    int p = 0;
    scanf("%c", &c);
    while (!isalpha(c) && (c != '#'))scanf("%c", &c);
    if (c == '#')return 0;
    while (isalpha(c) && (p < MaxS)) {
        Word[p++] = (char) tolower(c);
        scanf("%c", &c);
    }
    while (isalpha(c))scanf("%c", &c);
    if (p < MinS)
        return GetWord(Word);
    Word[p] = '\0';
    return 1;
}

double CalSim(HashTable H, WList File, int F1, int F2)
{
    int i;
    if (File[F1].words > File[F2].words) {
        i = F1;
        F1 = F2;
        F2 = i;
    }
    WList W = File[F1].next;
    i = 0;
    while (W) {
        FList F = H->theCells[W->words].invIndex;
        while (F) {
            if (F->fileID == F2)
                break;
            F = F->next;
        }
        if (F) i++;
        W = W->next;
    }
    return ((double) (i * 100) / (double) (File[F1].words + File[F2].words - i));
}
