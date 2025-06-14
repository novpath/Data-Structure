#include <cstdio>
#include <cstring>

#define MAXN 100001
#define MaxPriorNum 10001
#define MaxLen 11

typedef struct mes {
    char message[MaxLen];
    int prior;
} mes;

mes H[MAXN];
int size;

void Create()
{
    size = 0;
    H[0] = {"\0", MaxPriorNum};
}

void Insert(mes x)
{
    if (size == MAXN)
        return;
    int i;
    for (i = ++size; H[i / 2].prior > x.prior; i /= 2)
        H[i] = H[i / 2];
    H[i] = x;
}

mes Delete(mes H[])
{
    if (size == 0) {
        printf("EMPTY QUEUE!");
        return H[0];
    }

    mes minItem = H[1];
    mes lastItem = H[size--];
    int parent, child;
    for (parent = 1; parent * 2 <= size; parent = child) {
        child = parent * 2;

        if (child != size && H[child + 1].prior < H[child].prior) {
            child++;
        }

        if (lastItem.prior <= H[child].prior) break;
        H[parent] = H[child];
    }
    H[parent] = lastItem;

    return minItem;
}

int main()
{
    int n;
    scanf("%d", &n);
    char op[5];
    mes elem;
    for (int i = 0; i < n; i++) {
        scanf("%s", op);
        if (!strcmp(op, "PUT")) {
            char name[MaxLen];
            int prior = MaxPriorNum;
            scanf("%s %d", name, &prior);
            elem = {"init", prior};
            strcpy(elem.message, name);
            Insert(elem);
        } else if (!strcmp(op, "GET")) {
            elem = Delete(H);
            if (elem.message[0] != '\0')
                printf("%s\n", elem.message);
        }
    }

    return 0;
}
