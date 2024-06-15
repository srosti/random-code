#include <stdio.h>
#include <stdlib.h>

typedef struct my_node {
    int data;
    struct my_node* left;
    struct my_node* right;
} node;

node* create_node(node *current_node, int data) {

    node *new_node  = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node* insert(node* current_node, int data) {
    if (current_node == NULL) {
        current_node = create_node(current_node, data);
    }
    else if (data < current_node->data) {
        current_node->left = insert(current_node->left, data);
    }
    else if (data > current_node->data) {
        current_node->right = insert(current_node->right, data);
    }
    return current_node;
}

void dump_tree(node *root) {
    if (root != NULL) {
        dump_tree(root->left);
        printf("%d", root->data);
        dump_tree(root->right);
    }

}

void main() {
    node* root = NULL;
    root = insert(root, 20);
    insert(root, 10);
    insert(root, 15);
    dump_tree(root);
}