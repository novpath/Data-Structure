#include <stdio.h>

#define MaxSize 100
typedef char ElementType;

typedef struct {
    ElementType data[MaxSize]; // 静态数组存放栈中元素
    int top;                   // 栈顶指针
} SqStack;

void InitStack(SqStack &S)
{
    S.top = -1;            // 初始化栈顶指针
}

bool StackEmpty(const SqStack &S)
{
    return S.top == -1;
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

bool GetTop(const SqStack &S, ElementType &x)
{
    if (S.top == -1)        // 栈空，报错
        return false;
    x = S.data[S.top];      // x 记录栈顶元素
    return true;
}

int GetPriority(char op) { // 获取运算符优先级
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // 括号或其他字符
    }
}

void InfixToPostfix(const char* infix, char* postfix)    // 中缀转后缀函数
{
    SqStack S;
    InitStack(S);
    int postIndex = 0;
    char c;
    for (int i = 0; (c = infix[i]) != '\0'; i++) {
        if (c == '(') {
            Push(S, c);
        } else if (c == ')') {  // 弹出直到 '('，括号不入栈
            while (!StackEmpty(S)) {
                char top;
                GetTop(S, top);
                if (top == '(') {
                    Pop(S, top);
                    break;
                } else {
                    Pop(S, top);
                    postfix[postIndex++] = top;
                }
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') { // 处理运算符优先级
            while (!StackEmpty(S)) {
                char top;
                GetTop(S, top);
                if (top != '(' && GetPriority(top) >= GetPriority(c)) {
                    Pop(S, top);
                    postfix[postIndex++] = top;
                } else {
                    break;
                }
            }
            Push(S, c);
        } else { // 操作数直接加入后缀表达式
            postfix[postIndex++] = c;
        }
    }

    while (!StackEmpty(S)) { // 弹出栈中剩余运算符
        char top;
        Pop(S, top);
        postfix[postIndex++] = top;
    }
    postfix[postIndex] = '\0'; // 字符串结束符
}

int main()
{
    char infix[MaxSize], postfix[MaxSize];
    printf("Please input infix expression:");
    scanf("%s", infix);
    InfixToPostfix(infix, postfix);
    printf("Postfix expression is: %s\n", postfix);
    return 0;
}