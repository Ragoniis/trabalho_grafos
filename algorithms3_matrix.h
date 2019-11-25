#ifndef ALGORITHMS3MATRIX
#define ALGORITHMS3MATRIX
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "data_structures.h"
#include "miscellaneous.h"
#include "cleaners.h"
double** all_paths_bellman_ford_matrix(double** matrix,unsigned v_number);
double* bellman_ford_matrix(double** matrix,unsigned v_number,unsigned s);
MatchingEdge* matching_matrix(BipartiteGraphMatrix* graph, unsigned v_number);
BipartiteGraphMatrix* check_bipartiteness_matrix(char** matrix, unsigned v_number);
#endif