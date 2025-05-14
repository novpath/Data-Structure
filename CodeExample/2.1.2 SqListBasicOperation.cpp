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

int main()
{
    SqList L;          //声明一个顺序表
    int e = 0;
    printf("%d\n", e);
    
    InitList(L);       //初始化顺序表
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    if(LocateElem(L,2))
        printf("Success, location is %d.\n", LocateElem(L,2));
    else
        printf("Error, no exist.\n");
    ListInsert(L, 3, 3);
    ListDelete(L, 2, e);
    printf("%d\n", e);
    if(LocateElem(L,2))
        printf("Success, location is %d.\n", LocateElem(L,2));
    else
        printf("Error, no exist.\n");
    GetElem(L,0);
    printf("1th = %d.\n", GetElem(L,1));

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
