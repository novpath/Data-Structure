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
bool MergeSqList(SqList La, SqList Lb, SqList &Lc);


int main()
{
    SqList La;          //����һ��˳��� La
    SqList Lb;          //����һ��˳��� Lb
    SqList Lc;          //����һ��˳��� Lc
    
    InitList(La);       //��ʼ��˳���
    ListInsert(La, 1, 1); ListInsert(La, 2, 3); ListInsert(La, 3, 5); ListInsert(La, 4, 7);
    ListInsert(La, 5, 9); ListInsert(La, 6, 11); ListInsert(La, 7, 14); ListInsert(La, 8, 16);
    
    InitList(Lb);       //��ʼ��˳���
    ListInsert(Lb, 1, 2); ListInsert(Lb, 2, 4); ListInsert(Lb, 3, 6); ListInsert(Lb, 4, 8);
    ListInsert(Lb, 5, 10); ListInsert(Lb, 6, 12); 
    
    MergeSqList(La, Lb, Lc);
    PrintSqList(Lc);

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

bool MergeSqList(SqList La, SqList Lb, SqList &Lc)
{
    if(La.length + Lb.length > MAXSIZE)  // �ϲ�����±��ȳ������Χ�򱨴�
        return false;
    int i = 0,  j = 0, k = 0;
    while(i < La.length && j < Lb.length) { // �����Ƚϣ�С��Ԫ�ش������� Lc
        if(La.data[i] <= Lb.data[j])
            Lc.data[k++] = La.data[i++];
        else
            Lc.data[k++] = Lb.data[j++];
    }
    
    while(i < La.length)                    // û�����˳���ƴ�ӵ� Lc ���棬���� while ֻ����Чһ��
        Lc.data[k++] = La.data[i++];
    while(j < Lb.length)
        Lc.data[k++] = Lb.data[j++];
    Lc.length = k;                          // ע��߽�������k ��ֵΪ������Ϊ�������Ҫ����һ�Ρ�
    
    return true;
}
