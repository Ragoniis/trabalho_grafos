#ifndef CLEANERS
#define CLEANERS
#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>
void free_list(IntNode** list, unsigned v_number);
void free_matrix(char** matrix, unsigned v_number);
void clean_PQ(PriorityQueue* pq);
void free_w_list(WeightedN** list, unsigned v_number);
#endif
