#ifndef ALGORITHMS2MATRIX
#define ALGORITHMS2MATRIX
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "data_structures.h"
#include "miscellaneous.h"
#include "cleaners.h"
unsigned** bfs_matrix_w(double** matrix, unsigned index,unsigned v_number);
void** dijkstra_matrix(double** matrix,unsigned v_number,unsigned s);
void minimum_spanning_tree_matrix(double** matrix, unsigned v_number, char* s );
double eccentricity_matrix(double** matrix, unsigned v_number, unsigned vertex,unsigned status);
ShortestPathW shortest_path_w_matrix(double** matrix,unsigned v_number, unsigned start, unsigned end, char status);
#endif
