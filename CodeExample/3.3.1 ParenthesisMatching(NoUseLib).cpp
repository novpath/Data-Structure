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
        	S.data[++S.top] = str[i]; // 扫描到左括号，入栈
        } else {
            if (S.top == -1)  		  // 扫描到右括号，且当前栈空
                return false;   	  // 匹配失败
            char topElem;
            topElem = S.data[S.top--];// 栈顶元素出栈
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }
    return (S.top == -1);           // 检索完全部括号后，栈空说明匹配成功
}

int main()
{
	char str[10] = "[([][])]";
	printf("%d", BracketCheck(str, 8));

    return 0;
}

