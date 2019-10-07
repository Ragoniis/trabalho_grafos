#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_structures.h"
#include "algorithms2.h"
#include "miscellaneous.h"


struct shortest_path_response
{
    unsigned distance;
    unsigned* path;
};

struct shortest_path_response shortest_path_w(WeightedN** list,unsigned v_number, unsigned start, unsigned end, char status){
    if(status == 2){

    }

}
unsigned** bfs_w_list(WeightedN** list, unsigned v_number,unsigned index){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    unsigned* level;
    register const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    
    if((marking = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
    }
    if((level = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
    }
    Queue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number; i++){
        marking[i] = none;
        level[i] = none;
    }
    
    marking[index] = explored;
    level[index] =0;
    queue_push(&q,index);
    WeightedN* linked_list;
    IntNode v;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        linked_list=list[v.value];
        while (linked_list!= NULL){
            if((marking[linked_list->value]) == none){
                marking[linked_list->value] = v.value;
                level[linked_list->value] = level[v.value] +1;
                queue_push(&q,linked_list->value);
            }
            linked_list = linked_list->next;
        }

    }
    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    array[0]=  marking;
    array[1]=  level;
    return array;

}

// retorna array com o vetor dist na posição 0 e parent na 1
unsigned** dijkstra_list(WeightedN** list,unsigned v_number,unsigned s){
    unsigned infinite = ~(0x0);
    unsigned* dist;
    unsigned* parent;
    if(!(dist = (unsigned*) malloc(sizeof(unsigned)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    if(!(parent = (unsigned*) malloc(sizeof(unsigned)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    for(unsigned i =0;i<v_number;i++){
        dist[i] = infinite;
        parent[i] = infinite;
    }
    PriorityQueue* pq;
    if(!(pq = (PriorityQueue*) malloc(sizeof(PriorityQueue)))){
        printf("Out of memory");
        exit(1);
    }
    initialize_PQ(pq,v_number);
    unsigned* position_array = pq->position_array;
    HeapNode* heap = pq->heap;
    decrease_key(pq,s,0.0);
    HeapNode* v;
    WeightedN* pointer;
    unsigned heap_position;
    while((v = extract_min(pq))){
        pointer = list[v->value];
        dist[v->value] = v->key;
        while (pointer!= NULL){
            heap_position = position_array[pointer->value];
            if(heap[heap_position].key > (v->key + pointer->weight)){
                decrease_key(pq,pointer->value,(v->key + pointer->weight));
                parent[pointer->value] = v->value;
            }
            pointer = pointer->next;
        }
    }
    unsigned** response;
    if(!(response = (unsigned**) malloc(sizeof(unsigned*)*2))){
        printf("Out of memory");
        exit(1);
    }
    response[0] = dist;
    response[1] = parent;
    return response;

}


