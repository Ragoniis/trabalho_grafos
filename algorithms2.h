#ifndef ALGORITHMS2
#define ALGORITHMS2
#include "data_structures.h"
typedef struct shortest_path_response
{
    unsigned distance;
    Stack path;
} ShortestPathW;
unsigned** dijkstra_list(WeightedN** list,unsigned v_number,unsigned s);
unsigned** bfs_w_list(WeightedN** list, unsigned index, unsigned v_number);
ShortestPathW shortest_path_w(WeightedN** list,unsigned v_number, unsigned start, unsigned end, char status);
#endif
