#ifndef CLEANERS
#define CLEANERS
#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "output.h"
void free_list(IntNode** list, unsigned v_number, unsigned array_number);
void free_matrix(char** matrix, unsigned v_number, unsigned array_number);
void clean_PQ(PriorityQueue* pq);
void free_w_list(WeightedN** list, unsigned v_number, unsigned array_number);
void free_w_matrix(double** matrix, unsigned v_number, unsigned array_number);
#endif
