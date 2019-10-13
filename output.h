#ifndef OUTPUT
#define OUTPUT
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "data_structures.h"
unsigned* degree_find_matrix(char** matrix,unsigned v_number);
unsigned* degree_find_list(IntNode** list, unsigned v_number);
unsigned* degree_find_matrix_w(double** matrix,unsigned v_number);
unsigned* degree_find_list_w(WeightedN** list, unsigned v_number);
#endif
