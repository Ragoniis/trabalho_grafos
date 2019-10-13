#ifndef ALGORITHMS2LIST
#define ALGORITHMS2LIST
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_structures.h"
#include "miscellaneous.h"
#include "cleaners.h"
#include <float.h>
typedef struct shortest_path_response
{
    double distance;
    Stack path;
} ShortestPathW;

void** dijkstra_list(WeightedN** list,unsigned v_number,unsigned s);
unsigned** bfs_w_list(WeightedN** list, unsigned index, unsigned v_number);
ShortestPathW shortest_path_w(WeightedN** list,unsigned v_number, unsigned start, unsigned end, char status);
void minimum_spanning_tree_list(WeightedN** list, unsigned v_number, char* s );
double eccentricity_list(WeightedN** list, unsigned v_number, unsigned vertex,unsigned status);
#endif
