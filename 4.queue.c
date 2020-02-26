/*************************************************************************
	> File Name: 4.queue.c
	> Author: 
	> Mail: 
	> Created Time: 2020年02月13日 星期四 19时11分34秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail, size, count;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->head = q->tail = q->count = 0;
    return q;
}

int empty(Queue *q) {
    return !q->count;
}

int front(Queue *q) {
    return q->data[q->head];
}


int expand(Queue *q) {
    int extr_size = q->size;
    int *p;
    while(extr_size) {
        p = (int *)malloc(sizeof(int) * (extr_size + q->size));
        if(p) break;
        extr_size /= 2;
    }
    if(p == NULL) return 0;
    for(int i = q->head, j = 0; j < q->count; j++) {
        p[j] = q->data[(i + j) % q->size];
    }
    q->size += extr_size;
    q->head = 0;
    q->tail = q->count;
    free(q->data);
    q->data = p;
    return 1;
}



int push(Queue *q, int val) {
    if(q == NULL) return 0;
    if(q->count == q->size) {
        if(!expand(q)) return 0;
        printf("expxan successfully! size = %d\n", q->size);
    } 
    q->data[q->tail++] = val;
    //q->tail = (q->tail + 1) % q->size;
    if(q->tail == q->size) q->tail -= q->size;
    q->count++;
    return 1;
}

void output(Queue *q) {
    printf("Queue(%d) = [", q->count);
    for(int i= q->head, j = 0; j < q->count; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % (q->size)]);
    }
    printf("]\n");
    return ;
}

int pop(Queue *q) {
    if(q == NULL) return 0;
    if(empty(q)) return 0;
    q->head++;
    if(q->head == q->size) q->head -= q->size;
    q->count--;
    return 1;
}

void clear(Queue *q) {
    if(q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Queue *queue = init(1);
    int op, val;
    for(int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Queue = %d\n", val, push(queue, val));
            } break;
            case 3: {
                printf("pop %d from Queue = ", front(queue));
                printf("%d\n", pop(queue));
            } break;
        }
        output(queue);
        printf("\n");
    }
    return 0;
}
