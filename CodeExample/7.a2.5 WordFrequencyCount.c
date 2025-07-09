#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXTable 50000
#define KEYLENGTH 15
#define MAXWORDLEN 80

typedef char ElementType[KEYLENGTH + 1];
typedef int Index;

typedef struct LNode {
    ElementType Data;
    int Count;
    struct LNode *Next;
} LNode, *PtrToLNode, *Position, *List;

typedef struct TblNode {
    int TableSize;
    List Heads;
} TblNode, *HashTable;

HashTable CreateTable()
{
    HashTable H = (HashTable) malloc(sizeof(struct TblNode));
    if (H == NULL)
        return NULL;
    H->TableSize = MAXTable;
    H->Heads = (List) malloc(H->TableSize * sizeof(struct LNode));
    if (H->Heads == NULL) {
        free(H);
        return NULL;
    }
    for (int i = 0; i < H->TableSize; i++) {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Count = 0;
        H->Heads[i].Next = NULL;
    }
    return H;
}

int CharConvert(char c)
{
    if (c >= '0' && c <= '9') return (c - '0');
    if (c == '_') return 36;
    if (c >= 'a' && c <= 'z') return (c - 'a' + 10);
    if (c >= 'A' && c <= 'Z') return (c - 'A' + 10); // 处理大写字母
    return 36; // 默认处理为下划线
}

int Hash(ElementType Key)
{
    int h = 0;
    for (int i = 0; i < 3; i++) {
        if (Key[i] == '\0') {
            h *= 37;
            if (i < 2) h *= 37;
            break;
        }
        h = h * 37 + CharConvert(Key[i]);
    }
    return h % MAXTable;
}

bool IsWordChar(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_'))
        return true;
    return false;
}

int GetAWord(ElementType word)
{
    char tempword[MAXWORDLEN + 1], c;
    int len = 0;
    int ret;

    while ((ret = scanf("%c", &c)) == 1 && c != '#') {
        if (IsWordChar(c)) {
            if (c >= 'A' && c <= 'Z') c = (char) (c - 'A' + 'a');
            if (len < MAXWORDLEN) // 防止缓冲区溢出
                tempword[len++] = c;
        } else if (len > 0) { // 已读取单词，遇到分隔符
            break;
        }
    }
    if (ret != 1 || c == '#') return -1;
    tempword[len] = '\0';
    if (len > KEYLENGTH) {
        tempword[KEYLENGTH] = '\0';
    }
    strcpy(word, tempword);
    return len;
}

void Show(HashTable H, double percent)
{
    if (H == NULL) return;

    int diffwordcount = 0;
    int maxf = 0;
    Position L;

    for (int i = 0; i < H->TableSize; i++) {
        diffwordcount += H->Heads[i].Count;
        L = H->Heads[i].Next;
        while (L) {
            if (maxf < L->Count) maxf = L->Count;
            L = L->Next;
        }
    }

    if (diffwordcount == 0) return;

    printf("%d\n", diffwordcount);
    int lowerbound = (int) ((double) diffwordcount * percent);
    int count = 0;
    for (int j = maxf; j >= 1; j--) {
        for (int k = 0; k < H->TableSize; k++) {
            L = H->Heads[k].Next;
            while (L) {
                if (j == L->Count) {
                    printf("%d:%s\n", L->Count, L->Data);
                    count++;
                }
                if (count >= lowerbound) return;
                L = L->Next;
            }
        }
    }
}

Position Find(HashTable H, ElementType Key)
{
    if (H == NULL) return NULL;
    Index Pos = Hash(Key);
    Position P = H->Heads[Pos].Next;
    while (P && strcmp(P->Data, Key) != 0)
        P = P->Next;
    return P;
}

void InsertAndCount(HashTable H, ElementType Key)
{
    if (H == NULL) return;
    Position P = Find(H, Key);
    if (P == NULL) {
        Position NewCell = (Position) malloc(sizeof(struct LNode));
        if (NewCell == NULL) return;
        strncpy(NewCell->Data, Key, KEYLENGTH);
        NewCell->Data[KEYLENGTH] = '\0';
        NewCell->Count = 1;
        Index Pos = Hash(Key);
        H->Heads[Pos].Count++;
        // 有序插入链表
        Position Prev = &(H->Heads[Pos]);
        Position Curr = H->Heads[Pos].Next;
        while (Curr && strcmp(Curr->Data, Key) < 0) {
            Prev = Curr;
            Curr = Curr->Next;
        }
        NewCell->Next = Curr;
        Prev->Next = NewCell;
    } else {
        P->Count++;
    }
}

void DestroyTable(HashTable H)
{
    if (H == NULL) return;

    for (int i = 0; i < H->TableSize; i++) {
        Position P = H->Heads[i].Next;
        while (P) {
            Position Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads);
    free(H);
}

int main()
{
    ElementType word;

    HashTable H = CreateTable();
    if (H == NULL) {
        fprintf(stderr, "Failed to create hash table\n");
        return 1;
    }

    while (1) {
        int length = GetAWord(word);
        if (length == -1) break;
        if (length > 0) {
            InsertAndCount(H, word);
        }
    }
    Show(H, 0.1); // 10% = 0.1
    DestroyTable(H);
    return 0;
}
