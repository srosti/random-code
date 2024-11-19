/* Circular Buffer Example

Explanation
Structure Definition:

buffer is the array holding the elements.
head points to the next position for insertion.
tail points to the next position for removal.
count tracks the number of elements in the buffer.
Functions:

initBuffer: Initializes the buffer.
isFull and isEmpty: Check the buffer's state.
enqueue: Adds elements to the buffer if not full.
dequeue: Removes elements from the buffer if not empty.
printBuffer: Displays the current buffer contents.
Test Program:

Demonstrates enqueueing, dequeueing, and handling the circular nature of the buffer

*/

#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 10 // Size of the circular buffer

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;


// Initialize the circular buffer
void initBuffer (CircularBuffer *cbuf) {
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->count = 0;
}

bool isFull(CircularBuffer *cbuf) {
    return cbuf->count == BUFFER_SIZE;
}

bool isEmpty(CircularBuffer *cbuf) {
    return cbuf->count == 0;
}

bool enqueue(CircularBuffer *cbuf, int value) {
    if (isFull(cbuf)) {
        printf("Circular buffer is full\n");
        return false;
    }

    cbuf->buffer[cbuf->head] = value;
    // head starts at 0 then,9,8,7,6,5,4,3,2,1,0
    cbuf->head=(cbuf->head+1) % BUFFER_SIZE;
    cbuf->count++;
    return true;
}

bool dequeue(CircularBuffer *cbuf, int *value) {
    if (isEmpty(cbuf)) {
        printf("Circular buffer is empty\n");
        return false;
    }
    *value = cbuf->buffer[cbuf->tail];
    // tail starts at 0, then 9,8,7,6, etc
    cbuf->tail = (cbuf->tail +1) % BUFFER_SIZE;
    cbuf->count--;
    return true;
}

void printBuffer(CircularBuffer *cbuf) {
    printf("Buffer-> ");
    for(int i=0; i<cbuf->count; i++) {
        int buffer_index = (cbuf->tail+i) % BUFFER_SIZE;
        printf(" [%d]", cbuf->buffer[buffer_index]);
    }
    printf("\n");
}


void main() {
    CircularBuffer cb;
    int value;
    initBuffer(&cb);
    enqueue(&cb, 0);
    enqueue(&cb, 1);
    enqueue(&cb, 2);
    enqueue(&cb, 3);
    printBuffer(&cb);
    dequeue(&cb, &value);
    printf("dequeued value=%d]\n",value);
    printBuffer(&cb);

}