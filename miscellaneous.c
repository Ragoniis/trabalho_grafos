#include <stdio.h>
#include <stdlib.h>
#include "miscellaneous.h"

void print_list_int(IntNode** list,unsigned v_number){
    IntNode* index;
    unsigned int i;
    printf("Lista ->[\n");
    for (i =0; i<v_number; i++ ){
        printf("Index %d ->  ",i);
        index = list[i];
        while (index!= NULL){
            printf("%d ", index->value);
            index = index->next;
        }
        printf("\n");
    }
    printf("] \n");

}

void print_matrix(char** matrix,unsigned v_number){
    for (unsigned i= 0;  i< v_number; i++){
        for(unsigned j = (i+1); j< v_number;j++ ){
            printf("linha %d coluna %d %i \n",i,j,matrix[i,j]);}
    }
}