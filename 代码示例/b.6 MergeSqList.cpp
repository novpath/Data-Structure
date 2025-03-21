#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50    //表最大长度的定义

typedef int ElementType;

typedef struct {
    ElementType data[MAXSIZE];   //顺序表的元素
    int length;                  //顺序表的当前长度
} SqList;                        //顺序表的结构类型定义

void InitList(SqList &L);
ElementType LocateElem(SqList L, ElementType e);
ElementType GetElem(SqList L, int i);
bool ListInsert(SqList &L, int i, int e);
bool ListDelete(SqList &L, int i, ElementType &e);
void PrintSqList(SqList &L);
bool MergeSqList(SqList La, SqList Lb, SqList &Lc);


int main()
{
    SqList La;          //声明一个顺序表 La
    SqList Lb;          //声明一个顺序表 Lb
    SqList Lc;          //声明一个顺序表 Lc
    
    InitList(La);       //初始化顺序表
    ListInsert(La, 1, 1); ListInsert(La, 2, 3); ListInsert(La, 3, 5); ListInsert(La, 4, 7);
    ListInsert(La, 5, 9); ListInsert(La, 6, 11); ListInsert(La, 7, 14); ListInsert(La, 8, 16);
    
    InitList(Lb);       //初始化顺序表
    ListInsert(Lb, 1, 2); ListInsert(Lb, 2, 4); ListInsert(Lb, 3, 6); ListInsert(Lb, 4, 8);
    ListInsert(Lb, 5, 10); ListInsert(Lb, 6, 12); 
    
    MergeSqList(La, Lb, Lc);
    PrintSqList(Lc);

    return 0;
}

void InitList(SqList &L)    
{ 
     L.length = 0;      //顺序表初始长度为 0
}

ElementType LocateElem(SqList L, ElementType e)
{ 
    int i;
    for(i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1;        //下标为 i 的元素等于 e，找到返回位序 i + 1
    return 0;                    //查找失败，返回 0
}

ElementType GetElem(SqList L, int i)
{
    return L.data[i - 1];
}

bool ListInsert(SqList &L, int i, int e)
{ 
    if (L.length == MAXSIZE) {          // 表空间已满，不能插入
        printf("Sequence list full!\n"); 
        return false; 
    } 
    if (i < 1 || i > L.length + 1) {      // 检查插入位置的合法性，注意可以插入 length 位置(末尾)
        printf("Illegal location!\n");
        return false; 
    } 
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];     // 将 ai～ an 倒序向后移动
    L.data[i - 1] = e;                 // 新元素插入
    L.length++;                        // 表长加一
    return true; 
}

bool ListDelete(SqList &L, int i, ElementType &e)
{ 
    if (i < 1 || i > L.length) {     // 检查空表及删除位置的合法性
        printf ("The %d-th element does not exist.\n", i); 
        return false; 
    }
    e = L.data[i - 1];               // 被删除元素赋值给引用变量 e
    for (int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];   // 将 ai+1~an 顺序向前移动
    L.length--;                      // 线性表长度减 1
    return true; 
}

void PrintSqList(SqList &L)
{
	for(int i = 0; i < L.length; i++)
	    printf("%d ", L.data[i]);
}

bool MergeSqList(SqList La, SqList Lb, SqList &Lc)
{
    if(La.length + Lb.length > MAXSIZE)  // 合并后的新表长度超过最大范围则报错
        return false;
    int i = 0,  j = 0, k = 0;
    while(i < La.length && j < Lb.length) { // 两两比较，小的元素存入结果表 Lc
        if(La.data[i] <= Lb.data[j])
            Lc.data[k++] = La.data[i++];
        else
            Lc.data[k++] = Lb.data[j++];
    }
    
    while(i < La.length)                    // 没比完的顺序表拼接到 Lc 后面，两个 while 只会生效一个
        Lc.data[k++] = La.data[i++];
    while(j < Lb.length)
        Lc.data[k++] = Lb.data[j++];
    Lc.length = k;                          // 注意边界条件，k 的值为表长，因为处理完后还要自增一次。
    
    return true;
}
