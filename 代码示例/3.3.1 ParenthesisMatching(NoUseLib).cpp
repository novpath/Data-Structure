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
        	S.data[++S.top] = str[i]; // É¨Ãèµ½×óÀ¨ºÅ£¬ÈëÕ»
        } else {
            if (S.top == -1)  		  // É¨Ãèµ½ÓÒÀ¨ºÅ£¬ÇÒµ±Ç°Õ»¿Õ
                return false;   	  // Æ¥ÅäÊ§°Ü
            char topElem;
            topElem = S.data[S.top--];// Õ»¶¥ÔªËØ³öÕ»
            if (str[i] == ')' && topElem != '(')
                return false;
            if (str[i] == ']' && topElem != '[')
                return false;
            if (str[i] == '}' && topElem != '{')
                return false;
        }
    }
    return (S.top == -1);           // ¼ìË÷ÍêÈ«²¿À¨ºÅºó£¬Õ»¿ÕËµÃ÷Æ¥Åä³É¹¦
}

int main()
{
	char str[10] = "[([][])]";
	printf("%d", BracketCheck(str, 8));

    return 0;
}

