#include <stdio.h>
#define MaxSize 100

typedef struct {
    char data[MaxSize];
    int top;
} SqStack;

bool BracketCheck(char str[], int length)
{
    SqStack S;
    S.top = -1;
    for (int i = 0; i < length; i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
        	S.data[++S.top] = str[i]; // ɨ�赽�����ţ���ջ
        } else {
            if (S.top == -1)  		  // ɨ�赽�����ţ��ҵ�ǰջ��
                return false;   	  // ƥ��ʧ��
            char topElem;
            topElem = S.data[S.top--];// ջ��Ԫ�س�ջ
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }
    return (S.top == -1);           // ������ȫ�����ź�ջ��˵��ƥ��ɹ�
}

int main()
{
	char str[10] = "[([][])]";
	printf("%d", BracketCheck(str, 8));

    return 0;
}

