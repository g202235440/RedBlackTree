#include <stdio.h>
#include <stdlib.h>

// Red-Black Tree Node
struct node {
    int color; // red = 1, black = 0
    int data; // data value
    struct node* p, * left, * right;
};

// Red-Black Tree Structure
typedef struct rbtree {
    struct node* root;
    struct node* nil; // sentinel
} rbtree;

// Function to create a new node
struct node* create_node(rbtree* T, int data, int color) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->color = color;
    n->p = T->nil;
    n->left = T->nil;
    n->right = T->nil;
    return n;
}

// Left rotation function
void LeftR(rbtree* T, struct node* x) {
    struct node* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == T->nil) {
        T->root = y;
    }
    else if (x == x->p->left) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

// Right rotation function
void RightR(rbtree* T, struct node* y) {
    struct node* x = y->left;
    y->left = x->right;
    if (x->right != T->nil) {
        x->right->p = y;
    }
    x->p = y->p;
    if (y->p == T->nil) {
        T->root = x;
    }
    else if (y == y->p->right) {
        y->p->right = x;
    }
    else {
        y->p->left = x;
    }
    x->right = y;
    y->p = x;
}

// Function to fix Red-Black Tree after insertion
void RBInsertFixup(rbtree* T, struct node* z) {
    while (z->p->color == 1) { // While parent of z is red
        if (z->p == z->p->p->left) {
            struct node* y = z->p->p->right; // Uncle of z
            if (y->color == 1) { // Case 1: Uncle is red
                z->p->color = 0;
                y->color = 0;
                z->p->p->color = 1;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) { // Case 2: z is a right child
                    z = z->p;
                    LeftR(T, z);
                }
                // Case 3: z is a left child
                z->p->color = 0;
                z->p->p->color = 1;
                RightR(T, z->p->p);
            }
        }
        else {
            struct node* y = z->p->p->left; // Uncle of z
            if (y->color == 1) { // Case 1: Uncle is red
                z->p->color = 0;
                y->color = 0;
                z->p->p->color = 1;
                z = z->p->p;
            }
            else {
                if (z == z->p->left) { // Case 2: z is a left child
                    z = z->p;
                    RightR(T, z);
                }
                // Case 3: z is a right child
                z->p->color = 0;
                z->p->p->color = 1;
                LeftR(T, z->p->p);
            }
        }
    }
    T->root->color = 0; // Ensure the root is always black
}

// Function to insert a node in Red-Black Tree
void RBInsert(rbtree* T, struct node* z) {
    struct node* y = T->nil;
    struct node* x = T->root;
    while (x != T->nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == T->nil) {
        T->root = z;
    }
    else if (z->data < y->data) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = 1;
    RBInsertFixup(T, z);
}

// Function to print the tree (in-order traversal) using a loop and a stack
void print_tree(rbtree* T) {
    struct node* stack[100]; // 스택을 사용할 배열
    int top = -1;
    struct node* current = T->root;

    while (current != T->nil || top != -1) {
        while (current != T->nil) {
            stack[++top] = current; // 현재 노드를 스택에 저장
            current = current->left; // 왼쪽 자식으로 이동
        }
        current = stack[top--]; // 스택에서 노드를 꺼냄
        // 현재 노드 출력
        printf("%d(%s) ", current->data, current->color == 0 ? "B" : "R");
        current = current->right; // 오른쪽 자식으로 이동
    }
    printf("\n"); // 줄바꿈
}

int main() {
    // Initialize the Red-Black Tree
    rbtree T;
    T.nil = (struct node*)malloc(sizeof(struct node));
    T.nil->color = 0;
    T.root = T.nil;

    // Insert nodes into the Red-Black Tree
    int values[] = { 20, 15, 25, 10, 5, 1 };
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        struct node* new_node = create_node(&T, values[i], 1);
        RBInsert(&T, new_node);
    }

    // Print the Red-Black Tree
    printf("Red-Black Tree:\n");
    print_tree(&T);

    // Clean up memory (for demonstration purposes, not handling tree deallocation)
    free(T.nil);
    return 0;
}
