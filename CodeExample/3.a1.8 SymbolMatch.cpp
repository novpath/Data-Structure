#include <stdio.h>

char l1, l2, r1, r2;
int top = -1;

bool SymbolMatch(const char str[])
{
    char s[100];
    int i = 0;
    while (str[i] != '\0') {
        int binary = 0;
        if (str[i] == '(' || str[i] == '[' || str[i] == '{' || (str[i] == '/' && str[i + 1] == '*')){
            if (str[i] != '/') {
                s[++top] = str[i];
                l1 = str[i];
            } else {                        // 为左注释符号时，入栈两个字符
                binary = 1;
                s[++top] = str[i];
                s[++top] = str[i + 1];
                l1 = str[i + 1];
                l2 = str[i];
            }
        } else if (str[i] == ')' || str[i] == ']' || str[i] == '}' || (str[i] == '*' && str[i + 1] == '/')){
            r1 = str[i];                    // 不知道符号栈是否空，记录可能出现单身的右符号
            r2 = str[i + 1];                // 不为右注释符，且栈空，则右括号单身
            if (str[i] != '*'){
                if (top == -1)
                    return false;
            } else {                         // 为右注释符，且栈空或者只有一个元素，则右注释单身
                binary = 1;
                if (top == 0 || top == -1)
                    return false;
            }
            l1 = s[top];
            l2 = s[top - 1];
            if (binary == 1)
                top = top - 2;
            else
                top--;
            if (l1 == '(' && r1 != ')')
                return false;
            if (l1 == '[' && r1 != ']')
                return false;
            if (l1 == '{' && r1 != '}')
                return false;
            if ((l1 == '*' && r1 != '*') || (l2 == '/' && r2 != '/'))
                return false;
        }
        if (binary == 0)
            i++;
        else
            i = i + 2;
    }
    return (top == -1);
}

int main()
{
    int i = 0;
    char str[1000];
    while ((str[i] = getchar()) != '.' || (str[i + 1] = getchar()) != '\n')
        i++;
    str[i + 1] = '\0';
    if (SymbolMatch(str)) {
        printf("YES\n");
    } else {
        printf("NO\n");
        if (top == -1) {
            if (r1 == '*') {
                printf("?-%c%c\n", r1, r2);
            } else {
                printf("?-%c\n", r1);
            }
        } else {
            if (l1 == '*')
                printf("%c%c-?\n", l2, l1);
            else
                printf("%c-?\n", l1);
        }
    }
    return 0;
}