#ifndef READER
#define READER
#include <stdio.h>
#include "data_structures.h"

WeightedN** read_list_w_int(unsigned v_number,FILE* fp, unsigned* array_number,char* status);
IntNode** read_list_int(unsigned v_number,FILE* fp, unsigned* array_number);
char** readMatrix(unsigned v_number, FILE* fp, unsigned* array_number);

#endif
