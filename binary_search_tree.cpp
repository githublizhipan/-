/*************************************************************************
	> File Name: 25.1binary_search_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: 2020年04月21日 星期二 19时25分47秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node {
    int key;
    struct Node *l, *r;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->l = p->r = NULL;
    return p;
}

Node *insert(Node *root, int key) {
    if (root == NULL)  return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->l = insert(root->l, key);
    else root->r = insert(root->r, key);
    return root;
}

Node *predeccessor(Node *root) {
    Node *temp = root->l;
    while (temp->r) temp = temp->r;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return root;
    if (root->key > key) {
        root->l = erase(root->l, key);
    } else if (root->key < key){
        root->r = erase(root->r, key);
    } else {
        if (root->l == NULL || root->r == NULL){
            Node *temp = root->l ? root->l : root->r;
            free(root);
            return temp;
        } else {
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->l = erase(root->l, temp->key);
        }
    }
    return root;
}


void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->l);
    clear(root->r);
    free(root);
    return ;
}

void output(Node *root) {
    if (root == NULL) return;
    output(root->l);
    printf("%d ", root->key);
    output(root->r);
    return;
}


int main () {
    srand(time(0));
    #define MAX_OP 30
    Node *root = NULL;
    for(int i = 0; i < MAX_OP; i++) {
        int op = rand() % 5, val = rand() % 20;
        switch(op) {
            case 2:
            case 3:
            case 4:
            case 0: {
                printf("inser %d to tree\n", val);
                root = insert(root, val);
                break;
            }
            case 1: {
                printf("erase %d from tree\n", val);
                root = erase(root, val);
                break;
            }
        }
        output(root);
        printf("\n");
    }
    return 0;
}
