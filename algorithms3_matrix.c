#include "algorithms3_matrix.h"

double** all_paths_bellman_ford_matrix(double** matrix,unsigned v_number){
    double** response;
    if((response = (double **)malloc (v_number*sizeof(double*)))==NULL){
        printf("Out of Memory Error");
        exit(1);
    }
    for(unsigned j =0;j<v_number; j++){
        if((response[j] = bellman_ford_matrix(matrix,v_number,j)) == NULL){
                free(response);
                return NULL;
        }
    }
    return response;

} 

double* bellman_ford_matrix(double** matrix,unsigned v_number,unsigned s){
    double* distance; 
    if((distance = (double *) malloc(v_number*sizeof(double))) == NULL){
        printf("Out of Memory Error");
        exit(1);
    }    
    for(unsigned i =0;i<v_number;i++){
        distance[i] = DBL_MAX;
    }
    distance[s]=0;
    double min;
    char changed=0;
    for(unsigned i =1;i<v_number;i++){
        changed =0;
        for(unsigned v=0; v<v_number; v++){
             //printf("OPa ai o %u\n",ll->value);
            for(unsigned w=0;w<v_number;w++){
                if((matrix[v][w]+distance[v])<distance[w]){
                    distance[w] = (matrix[v][w]+distance[v]);
                    changed= 1;
                }
            }
        }
        if(changed == 0){
            goto RETURN;
        }
    }
    changed =0;
    for(unsigned v=0; v<v_number; v++){
        //printf("OPa ai o %u\n",ll->value);
        for(unsigned w=0;w<v_number;w++){
            if((matrix[v][w]+distance[v])<distance[w]){
                distance[w] = (matrix[v][w]+distance[v]);
                changed= 1;
            }
        }
    }
    if(changed == 1){
        free(distance);
        return NULL;
    }
    RETURN:return distance;
}