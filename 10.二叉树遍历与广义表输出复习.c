/*************************************************************************
	> File Name: 10.binary_tree复习.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月17日 星期一 13时40分11秒
 ************************************************************************/
#include <time.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;

    


} Node, *pNode;


pNode get_node(int val) {
    pNode node = (pNode)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
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


void output(pNode root) {
    if(root == NULL) return ;
    printf("%d", root->data);
    if(root->lchild == NULL && root->rchild == NULL) {
        return ;
    }
    printf("(");
    if(root->lchild) {
        output(root->lchild);
    }
    if(root->rchild) {
        printf(",");
        output(root->rchild);
    }
    printf(")");
    return ;
}


void pre_order(pNode root) {
    if(root == NULL) return ;
    printf("%d ", root->data);
    if(root->lchild) pre_order(root->lchild);
    if(root->rchild) pre_order(root->rchild);
    return ;
}
void in_order(pNode root) {
    if(root == NULL) return ;
    if(root->lchild) in_order(root->lchild); 
    printf("%d ", root->data);
    if(root->rchild) in_order(root->rchild);
    return ;
}
void post_order(pNode root) {
    if(root == NULL) return ;
    if(root->lchild) post_order(root->lchild);
    if(root->rchild) post_order(root->rchild);
    printf("%d ", root->data);
    return ;
}


void clear(pNode root) {
    if(root == NULL) return ;
    if(root->lchild) clear(root->lchild);
    if(root->rchild) clear(root->rchild);
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
        printf("广义表输出：");
        output(root);
        printf("\n");
    }
    printf("前序遍历：");
    pre_order(root);
    printf("\n中序遍历：");
    in_order(root);
    printf("\n后序遍历：");
    post_order(root);
    printf("\n");
    
    clear(root);

    return 0;
}
