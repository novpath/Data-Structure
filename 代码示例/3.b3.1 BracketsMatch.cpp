#include <stdio.h>

bool BracketsMatch(const char *str)
{
    char s[100];
    int top = -1;
    int i = 0;
    while (*(str + i) != '\0') {
        if (*(str + i) == '(' || *(str + i) == '[' || *(str + i) == '{') {
            s[++top] = *(str + i);
        } else {
            if (top == -1)
                return false;
            char x = s[top--];
            if (x == '(' && *(str + i) != ')')
                return false;
            if (x == '[' && *(str + i) != ']')
                return false;
            if (x == '{' && *(str + i) != '}')
                return false;
        }
        i++;
    }
    return (top == -1);
}

int main()
{
    char str[100];
    printf("Please enter a string: ");
    scanf("%s", str);
    printf("%d", BracketsMatch(str));

    return 0;
}