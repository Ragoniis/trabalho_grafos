#ifndef ALGORITHMS
#include "data_structures.h"
#define ALGORITHMS
unsigned** bfs_list(IntNode** list, unsigned index, unsigned v_number);
unsigned** bfs_matrix(char** matrix, unsigned index,unsigned v_number);
unsigned* dfs_list(IntNode** list, unsigned index, unsigned v_number);
unsigned** sorted_bfs_list(IntNode** list, unsigned index,unsigned v_number);
unsigned diameter_matrix(char** matrix, unsigned v_number);
unsigned diameter_list(IntNode** list, unsigned v_number);
unsigned pseudo_diameter_list(IntNode** list, unsigned v_number);
unsigned shortest_path(unsigned v2,unsigned* marking){
#endif
