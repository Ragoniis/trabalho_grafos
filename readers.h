#ifndef READER
#define READER
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
double** read_matrix_w(unsigned* v_number_pointer, unsigned* array_number,char* status,char* file_name);
WeightedN** read_list_w_int(unsigned* v_number_pointer, unsigned* array_number,char* status, char* file_name);
IntNode** read_list_int(unsigned* v_number_pointer, unsigned* array_number, char* file_name);
char** readMatrix(unsigned* v_number_pointer, unsigned* array_number, char* file_name);
#endif
