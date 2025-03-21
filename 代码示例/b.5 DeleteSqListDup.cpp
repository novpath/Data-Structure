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
void PrintSqList(SqList &L);
bool DeleteSqListDup1(SqList &L);
bool DeleteSqListDup2(SqList &L);
bool DeleteSqListDup3(SqList &L); 

int main()
{
    SqList L;          //����һ��˳���
    
    InitList(L);       //��ʼ��˳���
    ListInsert(L, 1, 1); ListInsert(L, 2, 1); ListInsert(L, 3, 2); ListInsert(L, 4, 3);
    ListInsert(L, 5, 3); ListInsert(L, 6, 3); ListInsert(L, 7, 4); ListInsert(L, 8, 4);
    ListInsert(L, 9, 4); ListInsert(L, 10, 4); ListInsert(L, 11, 5); ListInsert(L, 12, 6);
    
    DeleteSqListDup1(L);
    PrintSqList(L);
    
    printf("\n");
    InitList(L);       //��ʼ��˳���
    ListInsert(L, 1, 1); ListInsert(L, 2, 1); ListInsert(L, 3, 2); ListInsert(L, 4, 3);
    ListInsert(L, 5, 3); ListInsert(L, 6, 3); ListInsert(L, 7, 4); ListInsert(L, 8, 4);
    ListInsert(L, 9, 4); ListInsert(L, 10, 4); ListInsert(L, 11, 5); ListInsert(L, 12, 6);
    
    DeleteSqListDup2(L);
    PrintSqList(L);
    
    printf("\n");
    InitList(L);       //��ʼ��˳���
    ListInsert(L, 1, 1); ListInsert(L, 2, 1); ListInsert(L, 3, 2); ListInsert(L, 4, 3);
    ListInsert(L, 5, 3); ListInsert(L, 6, 3); ListInsert(L, 7, 4); ListInsert(L, 8, 4);
    ListInsert(L, 9, 4); ListInsert(L, 10, 4); ListInsert(L, 11, 5); ListInsert(L, 12, 6);
    
    DeleteSqListDup3(L);
    PrintSqList(L);

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

void PrintSqList(SqList &L)
{
	for(int i = 0; i < L.length; i++)
	    printf("%d ", L.data[i]);
}

bool DeleteSqListDup1(SqList &L)
{
    if(L.length == 0)
        return false;
    int nodupcnt = 1;
    for(int i = 1; i < L.length; i++) {    // �� i = 1 ��ʼ����֤�±�Ϸ������� i = 0 ���ô���
        if(L.data[i] != L.data[i - 1]) {
            L.data[nodupcnt] = L.data[i];
            nodupcnt++;
        }
    }
    L.length = nodupcnt;
}

bool DeleteSqListDup2(SqList &L)
{
    if(L.length == 0)
        return false;
    int dupcnt = 0;
    for(int i = 1; i < L.length; i++) {    // �� i = 1 ��ʼ����֤�±�Ϸ������� i = 0 ���ô���
        if(L.data[i] == L.data[i - 1])
            dupcnt++;
        else
            L.data[i - dupcnt] = L.data[i];
    }
    L.length -= dupcnt;
}

bool DeleteSqListDup3(SqList &L)
{
    if(L.length == 0)
        return false;
    int i, j;                                 // i �洢��һ������ͬ��Ԫ�أ�j Ϊ����ָ��
    for(i = 0, j = 1; j < L.length; j++) 
        if(L.data[i] != L.data[j])            // ��һ��Ԫ�������ͬ��ǰһ��Ԫ��
            L.data[++i] = L.data[j];          // �����Ԫ��
    L.length = i + 1;
    return true;
}
