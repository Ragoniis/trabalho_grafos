#ifndef ALGORITHMS3LIST
#define ALGORITHMS3LIST
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "data_structures.h"
#include "miscellaneous.h"
#include "cleaners.h"
#include <float.h>
double** all_paths_bellman_ford_list(WeightedN** list,unsigned v_number);
double* bellman_ford_list(WeightedN** list,unsigned v_number,unsigned t);
MatchingEdge* matching_list(BipartiteGraphList* graph, unsigned v_number);
BipartiteGraphList* check_bipartiteness_list(IntNode** list, unsigned v_number);
#endif
