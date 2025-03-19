#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50    //����󳤶ȵĶ���

typedef int ElementType;

typedef struct { 
    ElementType data[MAXSIZE];   //˳����Ԫ��
    int length;                  //˳���ĵ�ǰ����
} SqList;                        //˳���Ľṹ���Ͷ���

void InitList(SqList &L);
ElementType LocateElem(SqList L, ElementType e);
ElementType GetElem(SqList L, int i);
bool ListInsert(SqList &L, int i, int e);
bool ListDelete(SqList &L, int i, ElementType &e);

int main()
{
    SqList L;          //����һ��˳���
    int e = 0;
    printf("%d\n", e);
    
    InitList(L);       //��ʼ��˳���
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
     L.length = 0;      //˳����ʼ����Ϊ 0
}

ElementType LocateElem(SqList L, ElementType e)
{ 
    int i;
    for(i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1;        //�±�Ϊ i ��Ԫ�ص��� e���ҵ�����λ�� i + 1
    return 0;                    //����ʧ�ܣ����� 0
}

ElementType GetElem(SqList L, int i)
{
    return L.data[i - 1];
}

bool ListInsert(SqList &L, int i, int e)
{ 
    if (L.length == MAXSIZE) {          // ��ռ����������ܲ���
        printf("Sequence list full!\n"); 
        return false; 
    } 
    if (i < 1 || i > L.length + 1) {      // ������λ�õĺϷ��ԣ�ע����Բ��� length λ��(ĩβ)
        printf("Illegal location!\n");
        return false; 
    } 
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];     // �� ai�� an ��������ƶ�
    L.data[i - 1] = e;                 // ��Ԫ�ز���
    L.length++;                        // ����һ
    return true; 
}

bool ListDelete(SqList &L, int i, ElementType &e)
{ 
    if (i < 1 || i > L.length) {     // ���ձ�ɾ��λ�õĺϷ���
        printf ("The %d-th element does not exist.\n", i); 
        return false; 
    }
    e = L.data[i - 1];               // ��ɾ��Ԫ�ظ�ֵ�����ñ��� e
    for (int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];   // �� ai+1~an ˳����ǰ�ƶ�
    L.length--;                      // ���Ա��ȼ� 1
    return true; 
}
