#include <stdio.h>
#define MaxSize 100
typedef char ElementType;
typedef struct {
    ElementType data[MaxSize]; // 静态数组存放栈中元素
    int top;                   // 栈顶指针
} SqStack;

void InitStack(SqStack &S) {
    S.top = -1;            // 初始化栈顶指针
}

bool StackEmpty(const SqStack &S) {
    return S.top == -1;
}

bool Push(SqStack &S, ElementType x) {
    if (S.top == MaxSize - 1)     // 栈满，报错
        return false;
    S.data[++S.top] = x;          // 指针先加 1，再入栈
    return true;
}

bool Pop(SqStack &S, ElementType &x) {
    if (S.top == -1)        // 栈空，报错
        return false;
    x = S.data[S.top--];    // 先出栈，指针再减 1
    return true;
}

bool GetTop(const SqStack &S, ElementType &x) {
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

void InfixToPostfix(const char* infix, char* postfix) {
    SqStack S;
    InitStack(S);
    int postIndex = 0;
    char c;
    for (int i = 0; (c = infix[i]) != '\0'; i++) {
        if (c == '(') {
            Push(S, c);
        } else if (c == ')') {
            while (!StackEmpty(S)) {
                char top;
                GetTop(S, top);
                if (top == '(') {
                    Pop(S, top);
                    break;
                }
                Pop(S, top);
                postfix[postIndex++] = top;
                postfix[postIndex++] = ' ';
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            bool isUnary = false;       // 检查是否为单目运算符
            if (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '+' || infix[i - 1] == '-'
                || infix[i - 1] == '*' || infix[i - 1] == '/') {
                isUnary = (c == '+' || c == '-');
            }
            if (isUnary) {  // 单目负号作为操作数的一部分处理
                if (c == '-') {
                    postfix[postIndex++] = c;
                }           // 单目正号直接跳过，处理后面的数字
                continue;
            }
            while (!StackEmpty(S)) {  // 处理普通运算符
                char top;
                GetTop(S, top);
                if (top != '(' && GetPriority(top) >= GetPriority(c)) {
                    Pop(S, top);
                    postfix[postIndex++] = top;
                    postfix[postIndex++] = ' ';
                } else {
                    break;
                }
            }
            Push(S, c);
        } else {                                         // 处理操作数
            while ((c >= '0' && c <= '9') || c == '.') { // 处理数字和小数点
                postfix[postIndex++] = c;
                i++;
                c = infix[i];
            }
            postfix[postIndex++] = ' ';
            i--;
        }
    }

    while (!StackEmpty(S)) {
        char top;
        Pop(S, top);
        postfix[postIndex++] = top;
        postfix[postIndex++] = ' ';
    }
    postfix[postIndex - 1] = '\0'; // 字符串结束符
}

int main() {
    char infix[MaxSize], postfix[MaxSize];
    scanf("%s", infix);
    InfixToPostfix(infix, postfix);
    printf("%s", postfix);
    return 0;
}