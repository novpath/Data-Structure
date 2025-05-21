#include <stdio.h>
#define MaxLen 255 // 预定义最大串长为 255

typedef struct {
    char ch[MaxLen]; // 每个分量存储一个字符
    int length; // 串的实际长度
} SString;

int Index(const SString &S, const SString &T)
{
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length) {
        if (S.ch[i] == T.ch[j]) {
            ++i;
            ++j; // 继续比较后继字符
        } else {
            i = i - j + 2;
            j = 1; // 指针后退重新开始比较
        }
    }
    if (j > T.length)
        return i - T.length;
    return 0;
}

int KMPSearch(const SString &S, const SString &T, int next[])
{
    int i = 1, j = 1;
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
        } else
            j = nextval[j];
    }
}

int main()
{
    int str[100];
    scanf("%s", str);
    return 0;
}
