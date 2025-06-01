#include <cstdio>
#define NULL nullptr

typedef struct node {
    char data[10];              // 存储操作数或操作符
    struct node *left, *right;
} BTree;

void BtreeToExp(BTree *root, int depth)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
        printf("%s", root->data);
    else {
        if (depth > 1) printf("(");
        BtreeToExp(root->left, depth + 1);
        printf("%s", root->data);
        BtreeToExp(root->right, depth + 1);
        if (depth > 1) printf(")");
    }
}

void ExpressionTreeToInfix(BTree *root)
{
    BtreeToExp(root, 1);
}


int main()
{
    BTree d = {"d", NULL, NULL};
    BTree op3 = {"-", NULL, &d};
    BTree c = {"c", NULL, NULL};
    BTree b = {"b", NULL, NULL};
    BTree a = {"a", NULL, NULL};
    BTree op2 = {"*", &c, &op3};
    BTree op1 = {"+", &a, &b};
    BTree root = {"*", &op1, &op2};

    ExpressionTreeToInfix(&root);
    printf("\n");

    BTree D = {"d", NULL, NULL};
    BTree C = {"c", NULL, NULL};
    BTree OP3 = {"-", &C, &D};
    BTree B = {"b", NULL, NULL};
    BTree A = {"a", NULL, NULL};
    BTree OP2 = {"-", NULL, &OP3};
    BTree OP1 = {"*", &A, &B};
    BTree ROOT = {"+", &OP1, &OP2};

    ExpressionTreeToInfix(&ROOT);

    return 0;
}
