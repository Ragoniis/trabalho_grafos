#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"


IntNode* put_inode(IntNode* p ,unsigned int value){
    IntNode* new_pointer;
    if (new_pointer = (IntNode *) malloc(sizeof(IntNode))){
        new_pointer->value = value;
        new_pointer->next = p;
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}

IntNode queue_pop(Queue* q){
    IntNode* p_v;
    IntNode vertice;
    p_v = q->top;
    q->top = p_v->next;
    vertice = *(p_v);
    free(p_v);
    return (vertice);
}


void queue_push(Queue* q, unsigned index){
    
    IntNode* last = q->rear;
    IntNode* new_pointer;
    if (new_pointer = (IntNode *) malloc(sizeof(IntNode))){
        if(q->top){
            new_pointer->value = index;
            new_pointer->next = NULL;
            last->next = new_pointer;
            q->rear = new_pointer;
        }else {
            new_pointer->value =index;
            new_pointer->next = NULL;
            q->rear = new_pointer;
            q->top = new_pointer;
        }
        //return new_pointer;
    }else
    {
        printf("Fatal error Out of memory");
        exit(1);
    }
}

void print_queue(Queue* q){
    IntNode v;
    while((q->top) != NULL){
        v = queue_pop(q);
        printf("%d \n",v.value);
    };
}



IntNode stack_pop(Stack* stack){
    IntNode* v_p;
    IntNode v;
    v_p = stack->top;
    stack->top = v_p->next;
    v = *(v_p);
    free(v_p);
    return v;
}

void stack_push(Stack* stack, IntNode v){
    IntNode* top = stack->top;
    IntNode* new_pointer;
    if (new_pointer = (IntNode *) malloc(sizeof(IntNode))){
        new_pointer->value = v.value;
        new_pointer->next = top;
        stack->top = new_pointer;
    }
    else
    {
        printf("Fatal error Out of memory");
        exit(1);
    }
}

void print_stack(Stack* stack){
    IntNode v;
    while((stack->top) != NULL){
        v = stack_pop(stack);
        printf("%d \n",v.value);
    }
}


