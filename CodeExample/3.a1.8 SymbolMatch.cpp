#include <stdio.h>

char l1, l2, r1, r2;
int flag;

bool SymbolMatch(const char str[])
{
    char s[100];
    int top = -1;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{' || (str[i] == '/' && str[i + 1] == '*')){
            if (str[i] != '/') {
                s[++top] = str[i];
            } else {
                s[++top] = str[i];
                i++;
                s[++top] = str[i];
            }
        } else if (str[i] == ')' || str[i] == ']' || str[i] == '}' || (str[i] == '*' && str[i + 1] == '/') || (str[i] == '/' && str[i - 1] == '*')){
            l1 = s[top];
            l2 = s[top - 1];
            r1 = str[i];
            r2 = str[i + 1];
            flag = top;
            if (top == -1)
                return false;
            char x = s[top--];
            if (x == '(' && str[i] != ')')
                return false;  
            if (x == '[' && str[i] != ']')
                return false;  
            if (x == '{' && str[i] != '}')
                return false;
            if (x == '*' && str[i] != '*')
                return false;
            if (x == '/' && str[i] != '/')
                return false;
        }
        i++;  
    }  
    return (top == -1);  
}  
  
int main()  
{
    int i = 0;
    char str[1000];
    while ((str[i] = getchar()) != '.' || (str[i + 1] = getchar()) != '\n')
        i++;
    str[i] = '\0';
    if (SymbolMatch(str)) {
        printf("YES\n");
    } else {
        printf("NO\n");
        if (flag == -1) {
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