#include "output.h"
#include <stdio.h>
#include <stdlib.h>

unsigned* degree_find_matrix(char** matrix,unsigned v_number){
    unsigned* degree_array;
    unsigned degree;
    unsigned max_degree = ~(0x0);
    if((degree_array = (unsigned * )malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
    }

    for(register unsigned j = 0; j<v_number; j++){
        degree =0;
        for(unsigned i =0; i<v_number;i++){
            //printf(" linha i%d coluna j%d %d\n",j,i,matrix[j][i]);
            if(matrix[j][i]==1){
                degree++;
            }
        }
        degree_array[j] = degree;
    }
    int cmpfunc (const void * a, const void * b);
    qsort(degree_array,v_number,sizeof(unsigned),cmpfunc);
    //printf("max degree %d\n",max_degree);
    return degree_array;
}

unsigned* degree_find_list(IntNode** list, unsigned v_number){
    unsigned* degree_array;
    unsigned degree;
    IntNode* linked_list;
    if((degree_array = (unsigned * )malloc(sizeof(unsigned)*v_number)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    for(unsigned i =0; i< v_number; i++){
        degree =0;
        linked_list= list[i];
        while (linked_list!= NULL){
            linked_list = linked_list->next;
            degree++;
        }
        degree_array[i] =degree;
    }
    int cmpfunc (const void * a, const void * b);
    qsort(degree_array,v_number,sizeof(unsigned),cmpfunc);
    return degree_array;
}

int cmpfunc (const void * a, const void * b){
        unsigned ai = *( unsigned* )a;
        unsigned bi = *( unsigned* )b;
        int r;
        r = (ai<bi) ? -1 :  1;
        return r;
}
