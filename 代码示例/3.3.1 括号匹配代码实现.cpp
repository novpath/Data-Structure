#include <stdio.h>

#define MaxSize 100
typedef char ElementType;
typedef struct {
    char data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S);    // ��ʼ��ջ
bool StackEmpty(SqStack S);    // �ж�ջ�Ƿ�Ϊ��
bool Push(SqStack &S, char x); // ��Ԫ����ջ
bool Pop(SqStack &S, char &x); // ջ��Ԫ�س�ջ���� x ����

bool BracketCheck(char str[], int length)
{
    SqStack S;
    InitStack(S);
    for (int i = 0; i < length; i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            Push(S, str[i]);    // ɨ�赽�����ţ���ջ
        } else {
            if (StackEmpty(S))  // ɨ�赽�����ţ��ҵ�ǰջ��
                return false;   // ƥ��ʧ��
            char topElem;
            Pop(S, topElem);    // ջ��Ԫ�س�ջ
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }
    return StackEmpty(S);       // ������ȫ�����ź�ջ��˵��ƥ��ɹ�
}

int main()
{
	SqStack S;
	InitStack(S);
	char str[10] = "[([][])]";
	printf("%d", BracketCheck(str, 8));

    return 0;
}

void InitStack(SqStack &S)
{
    S.top = -1;            // ��ʼ��ջ��ָ��
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)       // ջ��
        return true;
    else                   // ����
        return false;
}

bool Push(SqStack &S, ElementType x)
{
    if (S.top == MaxSize - 1)     // ջ��������
        return false;
    S.data[++S.top] = x;          // ָ���ȼ� 1������ջ
    return true;
}

bool Pop(SqStack &S, ElementType &x)
{
    if (S.top == -1)        // ջ�գ�����
        return false;
    x = S.data[S.top--];    // �ȳ�ջ��ָ���ټ� 1
    return true;
}

