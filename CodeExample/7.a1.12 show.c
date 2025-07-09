#include <stdio.h>
#include <stdlib.h>

#define KeyLength 15
typedef char ElementType[KeyLength + 1];

typedef struct LNode {
    ElementType data;
    struct LNode *next;
    int count;
} LNode, *LinkList;

typedef struct TblNode {
    int TableSize;
    LinkList Heads;
} TblNode, *HashTable;

void Show(HashTable H, double percent)
{
    int diffwordcount = 0; /* 不同的单词数量 */
    int maxf = 0; /* 最大的词频 */
    int maxCollision = 0; /* 最大冲突次数,初始化为 0 */
    int minCollision = 100; /* 最小冲突次数,初始化为 100 */
    LinkList L;
    int i, count = 0;
    for (i = 0; i < H->TableSize; i++) {
        /* 求不同的单词数量 */
        diffwordcount += H->Heads[i].count; /* 头结点 count 统计链表长度*/
        /* 统计最大和最小冲突次数 */
        if (maxCollision < H->Heads[i].count)
            maxCollision = H->Heads[i].count;
        if (minCollision > H->Heads[i].count)
            minCollision = H->Heads[i].count;
        /* 求最大的词频 */
        L = H->Heads[i].next; /* 从每个链表的表头开始 */
        while (L) {/* 遍历链表 */
            if (maxf < L->count) maxf = L->count;
            L = L->next;
        }
    }/* 结束for循环 */
    printf("共有%d个不同的单词,词频最大是%d;\n", diffwordcount, maxf);
    printf("最大冲突次数是%d,最小冲突次数是%d.\n", maxCollision, minCollision);
    /* 求每个词频等级拥有的不同单词数量 */
    /* 根据最大的词频,分配一个整数数组 */
    int *diffwords = (int *) malloc((maxf + 1) * sizeof(int));  /* 每个词频对应的不同单词数量 */
    /* 统计词频从 1 到 maxf 的单词数量 */
    for (i = 0; i <= maxf; i++)
        diffwords[i] = 0;
    for (i = 0; i < H->TableSize; i++) {
        L = H->Heads[i].next;
        while (L) {/* 遍历链表 */
            diffwords[L->count]++; /* 该词频增加一个单词 */
            L = L->next;
        }
    }
    /* 求特定的词频,使得大于等于该词频的单词总和超过给定的比例 */
    int lowerbound = (int) (diffwordcount * percent);
    for (i = maxf; i >= 1 && count < lowerbound; i--)
        count += diffwords[i];
    /* 按词频从大到小输出单词 */
    for (int j = maxf; j >= i; j--) /* 对每个词频 */
        for (int k = 0; k < H->TableSize; k++) {/* 遍历整个散列表 */
            L = H->Heads[k].next;
            while (L) {
                if (j == L->count)   /* 发现一个单词的词频与当前词频相等 */
                    /* 输出该单词及词频 */
                    printf(" %-15s :%d\n", L->data, L->count);
                L = L->next;
            }
        }
    free(diffwords);
}

void InsertAndCount(HashTable H, ElementType key)
{
    Position p, newCell;
    Index pos;
    p
}

int main()
{
    FILE *fp;
    HashTable H;
    ElementType word;
    int TableSize = 100;       // 散列表的估计大小，可以根据应用更改
    int length, wordcount = 0;
    char docment[30] = "HarryPotter.txt";

    H = CreateTable(TableSize);
    if ((fp = fopen(docment, "r")) == NULL)
        printf("Can't open file\n");

    while (!feof(fp)) {
        length = GetAword(fp, word);  // 读取一个单词
        if (length > 3) {   // 只考虑大于 3 个字符的单词
            wordcount++;
            InsertAndCount(H, word);
        }
    }
    fclose(fp);

    printf("The document exists %d valid words", wordcount);
    Show(H, 10.0 / 100);    // 显示词频前 10% 的所有单词
    DestroyTable(H);

    return 0;
}
