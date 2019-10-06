#ifndef READER
#include "data_structures.h"
#include <stdio.h>
#define READER
IntNode** read_list_int(unsigned v_number,FILE* fp, unsigned* array_number);
char** readMatrix(unsigned v_number, FILE* fp, unsigned* array_number);
#endif
