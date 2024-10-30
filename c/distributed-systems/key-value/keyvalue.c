#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    KeyValue *entries;
    int capacity;
    int size;
} KeyValueStore;

KeyValueStore *create_key_value_store(int capacity) {
    KeyValueStore *store = (KeyValueStore *)malloc(sizeof(KeyValueStore));
    store->entries = (KeyValue *)malloc(capacity * sizeof(KeyValue));
    store->capacity = capacity;
    store->size = 0;

    return store;

}

void put(KeyValueStore *store, const char *key, const char *value) {

    // Find existing entry if it exists
    for (int i=0; i < store->size; i++) {
        if ( strcmp(store->entries[i].key, key) == 0) {
            free(store->entries[i].value);
            store->entries[i].value = strdup(value);
            return;
        }
    }


    // Key doesn't exist
    if (store->size < store->capacity) {
        store->entries[store->size].key = strdup(key);
        store->entries[store->size].value = strdup(value);
        store->size++;
    }
    else {
        printf("key store capacity exceeeded\n");
    }

}

int main() {
    KeyValueStore *keystore;

    keystore = create_key_value_store(10);
    put(keystore,"foo", "bar");
    put(keystore,"jazz", "hands");
    put(keystore,"foo", "baz");
    return 0;
}