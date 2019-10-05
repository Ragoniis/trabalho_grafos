#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//Globais pro arquivo
unsigned v_number_global;
FILE *fp;
long unsigned array_number =0;
//Globais pro projeto

//Estruturas de dados
typedef struct int_node
{
    /* data */
    unsigned int value;
    struct int_node* next;

} IntNode;

typedef struct stack
{
    IntNode* top;
}Stack;

typedef struct queue
{
    IntNode* rear;
    IntNode* top;
} Queue;

