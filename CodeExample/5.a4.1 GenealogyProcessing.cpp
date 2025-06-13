#include <cstdio>
#include <cstring>
#define NameLen 11
#define MaxNumber 101

typedef char ElementType[NameLen];

typedef struct {
    ElementType Name;
    int parent;
    int space;
} Genealogy;

Genealogy G[MaxNumber];
int n, m;
void InPut();
int GetName(ElementType line);
int FindPos(ElementType str);
bool JudgeChild(int x, int y);
bool JudgeSibling(int x, int y);
bool JudgeDescendant(int x, int y);
bool IsAlpha(char ch);
void Judge();

int main()
{
    InPut();
    Judge();
    return 0;
}

int GetName(ElementType line)
{
    char c;
    int space = 0;
    scanf("%c", &c);
    while (!IsAlpha(c) && c != ' ')
        scanf("%c", &c);
    while (c == ' ') {
        space++;
        scanf("%c", &c);
    }
    int i = 0;
    while (IsAlpha(c)) {
        line[i++] = c;
        scanf("%c", &c);
    }
    line[i] = '\0';
    return space;
}

int FindPos(ElementType str)
{
    for (int i = 0; i < n; i++) {
        if (strcmp(str, G[i].Name) == 0)
            return i;
    }
    return -1;
}

bool JudgeChild(int x, int y)
{
    return (G[x].parent == y);
}

bool JudgeSibling(int x, int y)
{
    return (G[x].parent == G[y].parent);
}

bool JudgeDescendant(int x, int y)
{
    if (y == 0)
        return true;
    while (G[x].parent != -1 && G[x].parent != y)
        x = G[x].parent;
    return (G[x].parent == y);
}

void InPut()
{
    ElementType line;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        G[i].space = GetName(line);
        strcpy(G[i].Name, line);
        if (G[i].space == 0) {
            G[i].parent = -1;
        } else {
            for (int j = i - 1; j >= 0; j--) {
                if (G[i].space - G[j].space == 2) {
                    G[i].parent = j;
                    break;
                }
            }
        }
    }
}

bool IsAlpha(char ch)
{
    return (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z');
}

void Judge()
{
    for (int i = 0; i < m; i++) {
        int flag = 0;
        ElementType strX, strY, REL, article;
        scanf("%s is %s %s of %s", strX, article, REL, strY);
        int x = FindPos(strX), y = FindPos(strY);
        if (!strcmp(REL, "child"))
            flag = JudgeChild(x, y);
        else if (!strcmp(REL, "parent"))
            flag = JudgeChild(y, x);
        else if (!strcmp(REL, "sibling"))
            flag = JudgeSibling(x, y);
        else if (!strcmp(REL, "descendant"))
            flag = JudgeDescendant(x, y);
        else if (!strcmp(REL, "ancestor"))
            flag = JudgeDescendant(y, x);
        if (flag)
            printf("True");
        else
            printf("False");
        if (i != m - 1)
            printf("\n");
    }
}
