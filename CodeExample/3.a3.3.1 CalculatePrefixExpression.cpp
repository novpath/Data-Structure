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

double CalculatePrefix(const char* prefix)    // 前缀表达式求值
{
    SqStack S;
    double ret = 0;
    int i = 0, cnt = 0;
    while (prefix[i] != '\0')
        i++;
    while (i >= 0) {
        if (prefix[i] >= '0' && prefix[i] <= '9') {
            while (prefix[i - cnt] >= '0' && prefix[i - cnt] <= '9') {
                cnt++;
            }
            double num = 0;
            for (int j = 0; j < cnt; j++) {
                num = 10 * num + prefix[i + cnt - j] - '0';
            }
            Push(S, num);
        } else {
            double result, a, b;
            Pop(S, a);
            Pop(S,b);
        }
        i++;
    }
    return ret;
}

int main()
{
    char prefix[MaxSize];
    scanf("[^\n]", prefix);
    printf("%f", CalculatePrefix(prefix));
    return 0;
}