#ifndef CLEANERS
#define CLEANERS
#include "data_structures.h"
void free_list(IntNode** list, unsigned v_number);
void free_matrix(char** matrix, unsigned v_number);
void clean_PQ(PriorityQueue* pq);
#endif
