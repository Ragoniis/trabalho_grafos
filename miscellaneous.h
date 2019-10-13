#ifndef MISCELLANEOUS
#define MISCELLANEOUS
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "data_structures.h"
// Estruturas e Funcões para o prim
typedef struct edge{
        unsigned vertex1;
        unsigned vertex2;
        double weight;
        struct edge *next;
}Edge;
void print_list_int(IntNode** list,unsigned v_number);
void print_matrix(char** matrix,unsigned v_number);
void print_stack(Stack* stack);
void print_queue(Queue* q);
void printHeap(PriorityQueue* pq);
void print_list_w_int(WeightedN** list,unsigned v_number);
void print_array(unsigned* array,unsigned max);
unsigned max_array(unsigned* array,unsigned v_number);
void print_w_matrix(double** matrix,unsigned v_number);
Edge* put_edge(Edge* p ,unsigned vertex1, unsigned vertex2 , double weight);
unsigned especial_max_array(double* array,unsigned v_number);
#endif
