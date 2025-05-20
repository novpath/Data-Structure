#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxSize 31
typedef double ElementType;
typedef struct {
    ElementType data[MaxSize]; // 静态数组存放栈中元素
    int top;                   // 栈顶指针
} SqStack;

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

bool IsNum(char c)
{
    if (c >= '0' && c <= '9' || c == '.')
        return true;
    return false;
}

bool IsOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

bool IsSignBit (char c)
{
    if (c == '+' || c == '-')
        return true;
    return false;
}

double CalculatePrefix(const char* prefix)    // 前缀表达式求值
{
    SqStack S;
    S.top = -1;
    double ret = 0;
    int i = 0;
    while (prefix[i + 1] != '\0')
        i++;
    int cnt = 0;
    double num = 0;
    while (i >= 0) {
        if (IsNum(prefix[i])) {
            if (prefix[i] != '.') {
                num += (prefix[i] - '0') * pow(10, cnt);
                cnt++;
            } else {
                num /= pow(10, cnt);
                cnt = 0;
            }
            if (i == 0 || prefix[i - 1] == ' ') {
                Push(S, num);
                num = cnt = 0;
            }
            if (IsSignBit(prefix[i - 1])) {
                if (prefix[i - 1] == '-' && num != 0)
                    num = -num;
                Push(S, num);
                num = cnt = 0;
                i--;
            }
        } else if (IsOperator(prefix[i])) {
            double result = 0, X = 0, Y = 0;
            Pop(S, X);
            Pop(S,Y);
            switch (prefix[i]) {
                case '+': result = X + Y; break;
                case '-': result = X - Y; break;
                case '*': result = X * Y; break;
                case '/': {
                    if (Y == 0) {
                        printf("ERROR\n");
                        exit(0);
                    }
                    result = X / Y; break;
                }
                default: break;
            }
            Push(S, result);
        }
        i--;
    }
    Pop(S, ret);
    return ret;
}

int main()
{
    char prefix[MaxSize];
    int i = 0;
    while ((prefix[i] = getchar()) != '\n')
        i++;
    prefix[i] = '\0';
    printf("%.1lf\n", CalculatePrefix(prefix));
    return 0;
}