#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MaxLen 261

typedef struct BiTNode {
    char filename[MaxLen];
    struct BiTNode *child, *sib;
    int isdir;
} BiTNode, *BiTree;

BiTree createNode(const char *name, int isdir)
{
    BiTree node = (BiTree) malloc(sizeof(BiTNode));
    strcpy(node->filename, name);
    node->child = node->sib = nullptr;
    node->isdir = isdir;
    return node;
}

BiTree insert(BiTree root, const char *name, int isdir)
{
    if (root == nullptr) return nullptr;

    BiTree prev = nullptr;
    BiTree curr = root->child;
    while (curr != nullptr &&
           (curr->isdir > isdir ||
            (curr->isdir == isdir && strcmp(curr->filename, name) < 0))) {
        prev = curr;
        curr = curr->sib;
    }
    if (curr != nullptr && strcmp(curr->filename, name) == 0 && curr->isdir == isdir) {
        return curr;
    }
    BiTree newNode = createNode(name, isdir);
    newNode->sib = curr;

    if (prev == nullptr) {
        root->child = newNode;
    } else {
        prev->sib = newNode;
    }

    return newNode;
}

void Preorder(BiTree node, int depth)
{
    if (node == nullptr) return;
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
    printf("%s\n", node->filename);

    Preorder(node->child, depth + 1);
    Preorder(node->sib, depth);
}

int main()
{
    int n;
    scanf("%d", &n);
    BiTree root = createNode("root", 1);

    for (int i = 0; i < n; ++i) {
        char path[MaxLen];
        scanf("%s", path);

        int lastSlash = path[strlen(path) - 1] == '\\';
        char *parts[100];
        int part_count = 0;
        char *token = strtok(path, "\\");
        while (token != nullptr) {
            parts[part_count++] = token;
            token = strtok(nullptr, "\\");
        }

        BiTree current = root;
        for (int j = 0; j < part_count; ++j) {
            int isdir = (j != part_count - 1) || lastSlash;
            current = insert(current, parts[j], isdir);
        }
    }

    Preorder(root, 0);
    free(root);
    return 0;
}
