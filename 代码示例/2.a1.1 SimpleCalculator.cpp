#include <stdio.h>

int main()
{
    int a, b;
    char c;
    scanf("%d", &a);
    scanf("%c", &c);
    
    int res = a;
    int flag = 0;


    while (c != '=') {
        scanf("%d", &b);
        if (c == '+') {
            res = a + b;
        } else if (c == '-') {
            res = a - b;
        } else if (c == '*') {
            res = a * b;
        } else if (c == '/') {
            if (b == 0) {
                flag = 1;
                break;
            } else {
                res = a / b;
            }
        } else {
            flag = 1;
        }
        a = res;
        scanf("%c", &c);
    }

    if (flag == 1)
        printf("ERROR\n");
    else
        printf("%d", res);
    
    return 0;
}
