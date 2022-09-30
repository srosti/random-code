#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>

typedef struct cbuf_t cbuf_t;

struct cbuf_t {
    uint8_t *buffer;
    size_t  used;
    size_t  tail;
    size_t  head;
    size_t  max;
    bool full;
};

typedef cbuf_t* cbuf_handle_t;


cbuf_handle_t cbuf_init(uint8_t *buffer, size_t size);
void cbuf_free(cbuf_handle_t handle);
void cbuf_reset(cbuf_handle_t handle);
void cbuf_push(cbuf_handle_t handle, uint8_t data);
int cbuf_pop(cbuf_handle_t handle, uint8_t *data);
int cbuf_is_empty(cbuf_handle_t handle);
int cbuf_is_full(cbuf_handle_t handle);
int cbuf_capacity(cbuf_handle_t handle);
int cbuf_size(cbuf_handle_t handle);

#define CBUF_SIZE 4


cbuf_handle_t cbuf_init(uint8_t *buffer, size_t size) {

    cbuf_handle_t handle = malloc(sizeof(cbuf_t));

    assert(handle);
    handle->buffer = buffer;
    handle->max = size;
    cbuf_reset(handle);

    return handle;
}

void cbuf_free(cbuf_handle_t handle) {
    free(handle);
}

void cbuf_reset(cbuf_handle_t handle) {

    handle->head = 0;
    handle->tail = 0;
    handle->full = false;
    handle->used = 0;

}

int cbuf_is_empty(cbuf_handle_t handle) {
    if (!handle->full && (handle->head == handle->tail))
        return true;
    else
        return false;
}

int cbuf_is_full(cbuf_handle_t handle) {
    return handle->full;
}

void cbuf_increment(cbuf_handle_t handle) {

    if(handle->full){

    }

    handle->head++;
    handle->used++;

    if(handle->head == handle->max) {
        handle->head = 0;
    }

    if(handle->head == handle->tail) {
        handle->full = true;
    }
}

void cbuf_push(cbuf_handle_t handle, uint8_t data) {

    handle->buffer[handle->head] = data;
    cbuf_increment(handle);

}

int cbuf_pop(cbuf_handle_t handle, uint8_t *data) {

    int result = -1;

    assert(handle);
    assert(data);

    if(!cbuf_is_empty(handle)) {
        *data = handle->buffer[handle->tail];
        handle->tail = (handle->tail + 1) & handle->max;
        result = 0;
    }

    return result;

}

void cbuf_dump(cbuf_handle_t handle){

    for(int i=handle->tail; i<handle->head; i++ ) {
        printf("buffer[%d]=0x%01x\n",i,handle->buffer[i]);
    }
}

void main() {

    uint8_t *drvr_buf = malloc(CBUF_SIZE*sizeof(uint8_t));
    cbuf_handle_t cbuf_handle;
    uint8_t data;

    cbuf_handle = cbuf_init(drvr_buf, CBUF_SIZE);
    cbuf_push(cbuf_handle, 8);
    cbuf_push(cbuf_handle, 9);
    cbuf_push(cbuf_handle, 10);
    if( cbuf_pop(cbuf_handle, &data) ) {
       printf("cbuf_pop failed\n");
    }
    else {
        printf("data=0x%01x\n", data);
    }


    cbuf_dump(cbuf_handle);


    cbuf_free(cbuf_handle);
    free(drvr_buf);
    printf("hello world\n");
}