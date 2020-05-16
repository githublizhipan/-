/*************************************************************************
	> File Name: 28.AVL.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年04月23日 星期四 18时16分35秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define H(root) (root)->h
#define L(root) (root)->l
#define R(root) (root)->r
#define K(root) (root)->key

typedef struct Node {
    int key, h;
    struct Node *l, *r;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = NIL->h = 0;
    NIL->l = NIL->r = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->h = 1;
    p->l = p->r = NIL;
    return p;
}
void update_height(Node *root) {
    root->h = H(L(root))> H(R(root)) ? H(L(root)) : H(R(root)) + 1;
}

Node *left_rotate(Node *root) {
    Node *temp = root->r;
    root->r = temp->l;
    temp->l = root;
    update_height(root);
    update_height(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->l;
    root->l = temp->r;
    temp->r = root;
    update_height(root);
    update_height(temp);
    return temp;
}


Node *maintain(Node *root) {
    if (abs(H(L(root)) - H(R(root))) <= 1) return root;
    if (H(L(root)) > H(R(root))) {
        if(H(R(L(root))) > H(L(L(root)))) {
            root->l = left_rotate(root->l);
        }
        root = right_rotate(root);
    } else {
        if(H(L(R(root))) > H(R(R(root)))) {
            root->l = right_rotate(root->l);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) {
        root->l = insert(root->l, key);
    } else root->r = insert(root->r, key);
    update_height(root);
    return maintain(root);
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->l);
    clear(root->r);
    free(root);
} 
Node *predeccessor(Node *root) {
    Node *temp = root->l;
    while (temp->r != NIL) temp = temp->r;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) root->l = erase(root->l, key);
    else if (root->key < key) {
        root->r = erase(root->r, key);
    } else {
        if (root->l == NIL || root->r == NIL) {
            Node *temp = root->l == NIL ? root->r : root->l;
            free(root);
            return temp;
        } else {
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->l = erase(root->l, temp->key);
        }
    }
    return maintain(root);
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d %d %d)\n", K(root), K(L(root)), K(R(root)));
    output(root->l);
    output(root->r);
    return ;
}


int main() {
    #define MAX_OP 20
    Node *root = NIL;
    for(int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    output(root);
    int val;
    while(~scanf("%d", &val)) {
        root = erase(root, val);
        printf("erase %d from tree", val);
        output(root);
    }
    return 0;
}
