#include <cstdio>

#define NULL nullptr

void PostInToPreorder(int postorder[], int l1, int h1, int inorder[], int l2, int h2, int preorder[], int l3, int h3,
                      int n)
{
    if (l1 > h1 || l2 > h2 || l3 > h3)
        return;
    preorder[l3] = postorder[h1];
    int i = l2;
    while (inorder[i] != postorder[h1])
        i++;
    int len = i - l2;
    PostInToPreorder(postorder, l1, l1 + len - 1, inorder, l2, l2 + len - 1, preorder, l3 + 1, l3 + len, n);
    PostInToPreorder(postorder, l1 + len, h1 - 1, inorder, l2 + len + 1, h2, preorder, l3 + len + 1, h3, n);
}

void CovertPostInToPreorder(int postorder[], int inorder[], int preorder[], int n)
{
    PostInToPreorder(postorder, 0, n - 1, inorder, 0, n - 1, preorder, 0, n - 1, n);
}

int main()
{
    int n, i;
    int postorder[31], preorder[31], inorder[31];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &postorder[i]);
    for (i = 0; i < n; i++)
        scanf("%d", &inorder[i]);
    CovertPostInToPreorder(postorder, inorder, preorder, n);
    printf("Preorder:");
    for (i = 0; i < n; i++)
        printf(" %d", preorder[i]);
    printf("\n");

    return 0;
}
