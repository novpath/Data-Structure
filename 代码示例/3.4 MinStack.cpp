#define MaxSize 30001

typedef struct {
    int data[MaxSize];
    int top;
} MinStack;

MinStack Smin, Sdata;

MinStack* minStackCreate() {
    Smin.top = -1;
    Sdata.top = -1;
    return &Smin;
}

void minStackPush(MinStack* obj, int val) {
    Sdata.data[++Sdata.top] = val;
    obj->top++;
    if (obj->top == 0) {
        obj->data[obj->top] = val;
    } else {
        obj->data[obj->top] = (obj->data[obj->top-1] > val )? val: obj->data[obj->top-1];
    }
}

void minStackPop(MinStack* obj) {
    obj->top--;
    Sdata.top--;
}

int minStackTop(MinStack* obj) {
    return Sdata.data[obj->top];
}

int minStackGetMin(MinStack* obj) {
    return obj->data[obj->top];
}

void minStackFree(MinStack* obj) {
    obj->top = -1;
    Sdata.top = -1;
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/
