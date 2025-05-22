#include <stdio.h>
#define MaxLen 255 // 预定义最大串长为 255
typedef struct {
    char ch[MaxLen]; // 每个分量存储多个字符
    int length; // 串的实际长度
} SString;

void GetNextval(const SString &T, int nextval[])
{
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            if (T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
}

void GetNext(const SString &T, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            next[i] = j; // 若 p_i=p_j，则 next[j+1]=next[j]+1
        } else {
            j = next[j]; // 否则令 j=next[j]，循环继续
        }
    }
}

int KMPSearch(const SString &S, const SString &T, int next[], int position)
{
    int i = position, j = 1;
    while (i <= S.length && j <= T.length) {
        if (j == 0 || S.ch[i] == T.ch[j]) {
            ++i;
            ++j; // 继续比较后继字符
        } else {
            j = next[j]; // 模式串向右移动
        }
    }
    if (j > T.length)
        return i - T.length;
    return 0;
}

int main()
{
    char ch = 0;
    SString str, pattern;
    str.length = 0;
    while ((ch = getchar()) != '\n') {
        str.ch[++str.length] = ch;
    }
    pattern.length = 0;
    while ((ch = getchar()) != '\n') {
        pattern.ch[++pattern.length] = ch;
    }
    int next[MaxLen] = {
            0,
    };
    int nextval[MaxLen] = {
            0,
    };
    GetNextval(pattern, nextval);
    GetNext(pattern, next);
    printf("First Matching Index:%d\n", KMPSearch(str, pattern, nextval, 1));
    int result, position = 1, cnt = 0;
    while ((result = KMPSearch(str, pattern, nextval, position)) != 0) {
        cnt++;
        position = result + 1;
    }
    printf("Matching SebStrings Num is %d", cnt);

    return 0;
}
