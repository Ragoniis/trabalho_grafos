#include <stdio.h>
#include <stdlib.h>
#include "miscellaneous.h"
unsigned infinite = ~(0x0);

void print_list_int(IntNode** list,unsigned v_number){
    IntNode* index;
    unsigned int i;
    printf("Lista ->[\n");
    for (i =0; i<v_number; i++ ){
        printf("Index %d ->  ",i);
        index = list[i];
        while (index!= NULL){
            printf("%d ", index->value);
            index = index->next;
        }
        printf("\n");
    }
    printf("] \n");

}

void print_matrix(char** matrix,unsigned v_number){
    for (unsigned i= 0;  i< v_number; i++){
        for(unsigned j = (i+1); j< v_number;j++ ){
            printf("linha %d coluna %d %i \n",i,j,matrix[i][j]);}
    }
}

void print_queue(Queue* q){
    IntNode v;
    while((q->top) != NULL){
        v = queue_pop(q);
        printf("%d \n",v.value);
    };
}

void print_stack(Stack* stack){
    IntNode v;
    while((stack->top) != NULL){
        v = stack_pop(stack);
        printf("%d \n",v.value);
    }
}

void printHeap(PriorityQueue* pq){
    HeapNode element;
    printf("\n  [");
    if(pq->last_element == infinite){
        printf("]\n");
        return;
    }
    for(unsigned i =0; i<=(pq->last_element);i++){
        element = (pq->heap)[i];
        printf("K:%u V:%u,",element.key,element.value);
    }
    printf("]\n");
}
