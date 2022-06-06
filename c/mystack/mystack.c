#include <stdio.h>

typedef struct mystack {
    int top;
    int size;
    int min;
    int* stack;
} mystack_t;

mystack_t *mystack;

struct mystack_t *newStack(size) {

    mystack_t *newstack = (mystack_t *)malloc(sizeof(mystack_t));
    newstack->size = size;
    newstack->top = -1;
    newstack->min = -1;
    newstack->stack = (int *)malloc(size * sizeof(int));
    return newstack;
}

void push(int val) {

    mystack->top = mystack->top + 1;
    mystack->stack[mystack->top] = val;
    if (val < mystack->min || mystack->min == -1) {
        mystack->min = val;
    }

}

int pop() {
    return mystack->stack[mystack->top--];
}

int min() {
    return mystack->min;
}


int main() {

    mystack = newStack(50);
    printf("mystack=0x%X\n", mystack);
    push(12);
    push(20);
    printf("min=%d\n", min());
    push(16);
    push(3);
    printf("top=%d\n", pop());

    printf("min=%d\n", min());



}