#include <stdio.h>
#include <stdlib.h>
#define INITSIZE 10   //���ʼ���ȵĶ���

typedef struct {
    int *data;        //ָʾ��̬���������ָ��
    int MaxSize;      //˳������󳤶�
    int length;       //˳���ĵ�ǰ����
} SeqList;            //˳���Ľṹ���Ͷ���

void IncreaseSize(SeqList &L, int len);
void InitList(SeqList &L);

int main()
{
    SeqList L;          //����һ��˳���
    InitList(L);        //��ʼ��˳���
    //... ...���������
    IncreaseSize(L, 5); //��������
    return 0;
}

void IncreaseSize(SeqList &L, int len)
{
    int *p = L.data;
    L.data = (int *)malloc((L.MaxSize + len)*sizeof(int)); //������ malloc �����������ֶ�̬�ڴ���䷽ʽ
    for (int i = 0; i < L.length; i++)
        L.data[i] = p[i];             //���ݸ��Ƶ��µ��ڴ�ռ�
    L.MaxSize = L.MaxSize + len;      //˳�����󳤶����� len
    free(p);                          //�ͷ�ԭ�����ڴ�ռ�
}

void InitList(SeqList &L)    
{
    L.data = (int *)malloc(INITSIZE * sizeof(int));
    L.length = 0;
    L.MaxSize = INITSIZE;
}
