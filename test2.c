#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "data_structures.h"
#include "algorithms.h"
#include "cleaners.h"
#include "miscellaneous.h"
#include "output.h"
#include "readers.h"
#include "algorithms2_list.h"
#include "algorithms2_matrix.h"
#include "algorithms3_list.h"
#include "algorithms3_matrix.h"


unsigned v_number_global;
unsigned array_number = 0;
//Estudos de Caso Matriz
/*
int main(void){
    double** matrix;
    char status;
    matrix = read_matrix_dw(&v_number_global,&array_number,&status,"test2.txt");
    double** anwser;
    anwser = all_paths_bellman_ford_matrix(matrix,v_number_global);
    free_w_matrix(matrix,v_number_global,array_number);
    if(!anwser){
        printf("Negative Cycles\n");
        exit(1);
    }
    for (unsigned i =0; i<v_number_global;i++){
        printf("Linha i:%d",i);
        for(unsigned j = 0;j<v_number_global;j++){
            if(anwser[i][j] == DBL_MAX){
                printf("--inf--");
            }else {
                printf("--(%f )--",anwser[i][j]);
            }
        }
        printf("\n");
    }
    free_w_matrix(anwser,v_number_global,array_number);
    return 0;
}

//Estudos de Caso Lista
*/
int main(void){
    WeightedN**list;
    char status;
    list = read_list_dw_int(&v_number_global,&array_number,&status,"ER_50.txt");
    double** anwser;
    anwser = all_paths_bellman_ford_list(list,v_number_global);
    if(!anwser){
        printf("Negative Cycles\n");
        exit(1);
    }
    for (unsigned i =0; i<v_number_global;i++){
        printf("Linha i:%d",i);
        for(unsigned j = 0;j<v_number_global;j++){
            if(anwser[i][j] == DBL_MAX){
                printf("--inf--");
            }else {
                printf("--(%f )--",anwser[i][j]);
            }
        }
        printf("\n");
    }
    free_w_list(list,v_number_global,array_number);
    free_w_matrix(anwser,v_number_global,array_number);
    return 0; 
}

/*
int main(void){
    IntNode** list;
    list = read_list_int(&v_number_global,&array_number,"grafo_teste_5.txt");
    BipartiteGraphList* teste;
    MatchingEdge* e,* keeper;
    teste = check_bipartiteness_list(list,v_number_global);
    if(teste == NULL){
        printf("Não é bipartido \n");
        return 1;
    }
    // for (unsigned i = 0; i<v_number_global; i++){
    //     printf(" %i", teste->sets[i]);
    // }
    e = matching_list(teste,v_number_global);
    unsigned count =0;
    keeper = e;
    while(e != NULL){
        //printf("V1:%u e V2:%u\n",e->v1,e->v2);
        count++;
        e = e->next;
    }
    printf("Count: %u\n",count);
    free_ell(keeper);
    free(teste->sets);
    free_list(teste->graph,v_number_global,array_number);
    free(teste);
    
    return 0;
}
*/