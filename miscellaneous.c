#include "miscellaneous.h"


//acha o caminho com u vetor de parent
void find_path(Stack* c,unsigned end, unsigned* parents){
    const unsigned no_parent = ~(0x1);
    IntNode v;
    v.value = end;
    unsigned parent;
    stack_push(c,v);
    while( (parent = parents[v.value])!= no_parent){
        v.value = parent;
        stack_push(c,v);
    }
    free(parents);
}


//Acha o máximo de uma array de doubles
double especial_max_array(double* array,unsigned v_number){
    //const unsigned infinite = ~(0x0);
    double* p ;
    register double max = 0.0;
    double* size = (array + v_number);
    for(p = array; p< size; p++)
        max = (*p>max) ? *p :max;
    return max;
}


unsigned max_array(unsigned* array,unsigned v_number){
    unsigned* p ;
    register unsigned max = 0;
    unsigned* size = (array + v_number);
    for(p = array; p< size; p++)
        max = (*p>max) ? *p :max;
    return max;
}

Edge* put_edge(Edge* p ,unsigned vertex1, unsigned vertex2 , double weight){
    Edge* new_pointer;
    if ((new_pointer = (Edge *) malloc(sizeof(Edge)))){
        new_pointer->vertex1 = vertex1;
        new_pointer->vertex2 = vertex2;
        new_pointer->weight = weight;
        new_pointer->next = p;
        return new_pointer;
    }
    exit(1);

}
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

void print_w_matrix(double** matrix,unsigned v_number){
    for (unsigned i= 0;  i< v_number; i++){
        for(unsigned j = (i+1); j< v_number;j++ ){
            printf("linha %d coluna %d %lf \n",i,j,matrix[i][j]);
        }
    }
}
void print_matrix(char** matrix,unsigned v_number){
    for (unsigned i= 0;  i< v_number; i++){
        for(unsigned j = 0; j< v_number;j++ ){
            printf("linha %d coluna %d %i \n",i,j,matrix[i][j]);
        }
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
        printf("--> %d ",(v.value+1));//+1 pela normalização do 1 para 0
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
        if(element.key == DBL_MAX){
            element.key = -1;   
        }
        printf("K:%lf V:%u,",element.key,element.value);
    }
    printf("]\n");
}
