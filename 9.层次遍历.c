/*************************************************************************
	> File Name: 9.层次遍历.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月16日 星期日 21时39分12秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char data;
    struct Node *l, *r;
} Node, *pNode;

typedef struct Stack {
    pNode *data;
    int top, size;
} Stack;

typedef struct Queue {
    pNode *data;
    int head, tail, size, cnt;
} Queue;


//栈的操作
void init_stack(Stack *s, int len) {
    s->data = (pNode *)malloc(sizeof(pNode) * len); //???????????????????????????????????????????????????
    s->top = -1;
    s->size = len;
    return ;
}
int empty(Stack *s) {
    return s->top == -1;
}
int push(Stack *s, pNode p) {
    if(s->top + 1 >= s->size) {
        return 0;
    }
    s->data[++(s->top)] = p;
    return 1;
}
pNode top(Stack *s) {
    if(empty(s)) return NULL;
    return s->data[s->top];
}
int pop(Stack *s){
    if(empty(s)) return 0;
    s->top--;
    return 1;
}
void clear(Stack *s) {
    if(s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

//队列操作
void init_queue(Queue *q, int len) {
    q->data = (pNode*)malloc(sizeof(pNode) * (2 * len));
    q->size = len;
    q->head = 0;
    q->tail = -1;
    q->cnt = 0;
    return ;
}
int empty_queue(Queue *q) {
    return q->tail < q-> head; //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
}
int push_queue(Queue *q, pNode p) {
    if(q->tail >= q->size) return 0;
    q->data[++(q->tail)] = p; //xxxxxxxxxxxxxxxxxxxxxxxxtailduojialexxxxxxxxxxxxxxxxxxx
    q->cnt++;
    return 1;
}
int pop_queue(Queue *q) {
    if(empty_queue(q)) return 0;
    q->head++;
    return 1;
}
void clear_queue(Queue *q) {
    if(q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}




//树的操作
Node *get_node(char c) {
    Node *node = (Node *)malloc(sizeof(Node));  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    node->data = c;
    node->l = node->r = NULL;
    return node;
}
void clear_node(Node *node) {
    if(node == NULL) return ;
    if(node->l) clear_node(node->l);
    if(node->r) clear_node(node->r);
    free(node);
    return ;
}
pNode built_tree(char *str, int *node_num) {
    pNode temp = NULL, current_root = NULL;
    Stack *s = (Stack *)malloc(sizeof(Stack));  //?
    init_stack(s, strlen(str));
    int flag = 0;
    while(str[0]) {
        switch(str[0]) {
            case '(':
                push(s, temp);
                flag = 0;
                temp = NULL;
                break;
            case ',':
                flag = 1;
                temp = NULL;
                break;
            case ')':
                current_root = top(s);
                pop(s);
                break;
            case ' ':
                break;
            default:
                temp = get_node(str[0]);
                if(!empty(s) && flag == 0) {
                    s->data[s->top]->l = temp;             //xxxxxxxxxxxxxxxxxxxxxxxxxx
                } else if(!empty(s) && flag == 1){
                    s->data[s->top]->r = temp;           //xxxxxxxxxxxxxxxxxxxxxxxxx top(s)->r=..xxxxxxxxxxxxxxxxxxxx
                }
                ++(*node_num);
                break; //xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
        }
        str++; //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx导致我关机两次
    }
    if(temp && !current_root) current_root = temp; //xxxx***
    clear(s); //忘写
    return current_root;
}


void output(pNode node, int node_num) {
    if(node_num == 0) return ;
    printf("%c", node->data);
    Queue *q = (Queue *)malloc(sizeof(Queue));
    init_queue(q, node_num);
    push_queue(q, node);
    while(!empty_queue(q)) {
        if(q->data[q->head]->l == NULL && q->data[q->head]->r == NULL) {
            pop_queue(q);
            continue;
        }
        if(q->data[q->head]->l) {
            push_queue(q, q->data[q->head]->l);
            printf(" %c", q->data[q->head]->l->data);
        }
        if(q->data[q->head]->r) {
            push_queue(q, q->data[q->head]->r);
            printf(" %c", q->data[q->head]->r->data);
        }
        pop_queue(q);
    }
    printf("\n");
    clear_queue(q);
    return ;
}



void in_order(pNode p) {
    if(p->l) in_order(p->l);
    printf("%c", p->data);
    if(p->r) in_order(p->r);
}


int main(){
    char str[100];
    scanf("%[^\n]s", str);
    int node_num = 0;
    pNode tree = built_tree(str, &node_num);
    output(tree, node_num);
    clear_node(tree);
    return 0;
}
