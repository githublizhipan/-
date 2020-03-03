/*************************************************************************
	> File Name: 11.中序遍历加线索化.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月17日 星期一 15时08分47秒
 ************************************************************************/
#include <time.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
    int ltag, rtag;
} Node, *pNode;


pNode get_node(int val) {
    pNode node = (pNode)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
    node->ltag = node->rtag = 0;
    return node;
}

pNode insert_node(pNode root, int val) {
    pNode node = get_node(val);
    if(root == NULL) {
        root = node;
        return root;
    }
    if(val == root->data) return root;
    if(val > root->data) {
        root->rchild = insert_node(root->rchild, val); //???????????????????
    } else {
        root->lchild = insert_node(root->lchild, val);
    }
    return root;
}


//加线索化
void build(pNode root) {
    if (root == NULL) return ;
    static pNode pre = NULL;
    build(root->lchild);
    if (root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = 1;
    }
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = 1;
    }
    pre = root;
    build(root->rchild);
    return ;
    /*
    if(root == NULL) return ;
    static pNode pre = NULL;
    build(root->lchild);
    if(root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = 1;
    }
    if(pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = 1;
    }
    pre = root;
    build(root->rchild);
    return ;
    */
}



pNode most_left(pNode p) {
    while(p && p->ltag == 0 && p->lchild != NULL) p = p->lchild;
    return p;
}

void output(pNode root) {
    Node *p = most_left(root);
    while(p) {
        printf("%d ", p->data);
        if(p->rtag == 1) {
            p = p->rchild;
        } else {
            p = most_left(p->rchild); //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
        }
    }
    return ;
    
}

void in_order(pNode root) {
    if(root == NULL) return ;
    if(root->lchild) in_order(root->lchild); 
    printf("%d ", root->data);
    if(root->rchild) in_order(root->rchild);
    return ;
}
void clear(pNode root) {
    if(root == NULL) return ;
    
    if(root->ltag == 0) clear(root->lchild);
    if(root->rtag == 0) clear(root->rchild);
    free(root);
    return ;
}

#define op 5
int main() {
    srand(time(0));
    int val;
    pNode root = NULL;
    for(int i = 1; i <= op; i++) {
        val = rand() % 100 + 1;
        root = insert_node(root, val);
    }
    
    printf("递归中序遍历：");
    in_order(root);
    printf("\n");
    
    
    printf("加线索化的中序遍历：");
    output(root);
    printf("\n");
    
    clear(root);
    return 0;
}

    
