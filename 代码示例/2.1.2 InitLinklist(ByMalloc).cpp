#include <stdio.h>
#include <stdlib.h>
#define INITSIZE 10   //表初始长度的定义

typedef struct {
    int *data;        //指示动态分配数组的指针
    int MaxSize;      //顺序表的最大长度
    int length;       //顺序表的当前长度
} SeqList;            //顺序表的结构类型定义

void IncreaseSize(SeqList &L, int len);
void InitList(SeqList &L);

int main()
{
    SeqList L;          //声明一个顺序表
    InitList(L);        //初始化顺序表
    //... ...链表插入满
    IncreaseSize(L, 5); //扩容链表
    return 0;
}

void IncreaseSize(SeqList &L, int len)
{
    int *p = L.data;
    L.data = (int *)malloc((L.MaxSize + len)*sizeof(int)); //建议用 malloc 而非其他几种动态内存分配方式
    for (int i = 0; i < L.length; i++)
        L.data[i] = p[i];             //数据复制到新的内存空间
    L.MaxSize = L.MaxSize + len;      //顺序表最大长度增加 len
    free(p);                          //释放原来的内存空间
}

void InitList(SeqList &L)    
{
    L.data = (int *)malloc(INITSIZE * sizeof(int));
    L.length = 0;
    L.MaxSize = INITSIZE;
}
