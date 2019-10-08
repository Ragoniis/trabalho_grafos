#include <stdio.h>
#include <stdlib.h>
#include "miscellaneous.h"

void print_array(unsigned* array,unsigned max){
    printf("[ ");
    for(unsigned i =0;i<(max-1);i++){
        printf(" %u ,",array[i]);
    }
    printf(" %u ]\n",array[max-1]);
}

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

void print_list_w_int(WeightedN** list,unsigned v_number){
    WeightedN* index;
    unsigned int i;
    printf("Lista ->[\n");
    for (i =0; i<v_number; i++ ){
        printf("Index %d ->  ",i);
        index = list[i];
        while (index!= NULL){
            printf("value :%d weight: %f", index->value,index->weight);
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
        printf("--> %d ",v.value);
    }
    printf("\n");
}

void printHeap(PriorityQueue* pq){
    unsigned infinite = ~(0x0);
    HeapNode element;
    printf("\n  [");
    if(pq->last_element == (infinite-1)){
        printf("]\n");
        return;
    }
    for(unsigned i =0; i<=(pq->last_element);i++){
        element = (pq->heap)[i];
        printf("K:%lf V:%u,",element.key,element.value);
    }
    printf("]\n");
}
