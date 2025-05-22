#include <stdio.h>
#define MaxLen 255      // 预定义最大串长为 255

typedef struct {
    char ch[MaxLen]; // 每个分量存储一个字符
    int length; // 串的实际长度
} SString;

bool SubString(SString &Sub, const SString &S, int pos, int len)
{
    if (pos + len - 1 > S.length) // 子串范围越界
        return false;
    for (int i = pos; i < pos + len; i++)
        Sub.ch[i - pos + 1] = S.ch[i];
    Sub.length = len;
    return true;
}

int StrCompare(const SString &S, const SString &T)
{
    for (int i = 1; i <= S.length && i <= T.length; i++) {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    }
    return S.length - T.length;
}

int Index(const SString &S, const SString &T)
{
    int i = 1, n = S.length, m = T.length;
    SString sub; // 用于暂存子串
    while (i <= n - m + 1) {
        SubString(sub, S, i, m);
        if (StrCompare(sub, T) != 0)
            ++i;
        else
            return i; // 返回子串在主串中的位置
    }
    return 0; // S 中不存在与 T 相等的子串
}

int main()
{
    SString Str;
    Str.length = 0;
    return 0;
}
