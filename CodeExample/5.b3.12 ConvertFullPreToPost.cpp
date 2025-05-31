#include <cstdio>
typedef char ElementType;

void PreToPost(ElementType pre[], int l1, int h1, ElementType post[], int l2, int h2)
{
    if (h1 >= l1) {
        post[h2] = pre[l1];
        int half = (h1 - l1) / 2;
        PreToPost(pre, l1 + 1, l1 + half, post, l2, l2 + half - 1); // 转换左子树
        PreToPost(pre, l1 + half + 1, h1, post, l2 + half, h2 - 1); // 转换右子树
    }
}

void ConvertFullPreToPost(ElementType pre[], ElementType post[])
{
    int i = 0;
    while (pre[i] != '\0')
        i++;
    PreToPost(pre, 0, i - 1, post, 0, i - 1);
    post[i] = '\0';
}

int main()
{
    char pre[100], post[100];
    scanf("%s", pre);
    ConvertFullPreToPost(pre, post);
    printf("%s\n", post);
    return 0;
}
