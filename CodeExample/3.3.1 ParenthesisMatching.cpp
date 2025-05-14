#include <stdio.h>

#define MaxSize 100
typedef char ElementType;
typedef struct {
    char data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S);    // 初始化栈
bool StackEmpty(SqStack S);    // 判断栈是否为空
bool Push(SqStack &S, char x); // 新元素入栈
bool Pop(SqStack &S, char &x); // 栈顶元素出栈，用 x 返回

bool BracketCheck(char str[], int length)
{
    SqStack S;
    InitStack(S);
    for (int i = 0; i < length; i++) {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
            Push(S, str[i]);    // 扫描到左括号，入栈
        } else {
            if (StackEmpty(S))  // 扫描到右括号，且当前栈空
                return false;   // 匹配失败
            char topElem;
            Pop(S, topElem);    // 栈顶元素出栈
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }
    return StackEmpty(S);       // 检索完全部括号后，栈空说明匹配成功
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
    S.top = -1;            // 初始化栈顶指针
}

bool StackEmpty(SqStack S)
{
    if (S.top == -1)       // 栈空
        return true;
    else                   // 不空
        return false;
}

bool Push(SqStack &S, ElementType x)
{
    if (S.top == MaxSize - 1)     // 栈满，报错
        return false;
    S.data[++S.top] = x;          // 指针先加 1，再入栈
    return true;
}

bool Pop(SqStack &S, ElementType &x)
{
    if (S.top == -1)        // 栈空，报错
        return false;
    x = S.data[S.top--];    // 先出栈，指针再减 1
    return true;
}

