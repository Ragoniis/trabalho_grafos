#include "cleaners.h"


void free_ell(MatchingEdge* p){
    MatchingEdge* temp;
    while(p!= NULL){
        temp = p->next;
        free(p);
        p = temp;
    }
}
void free_w_list(WeightedN** list, unsigned v_number,unsigned array_number){
    FILE* out;
    out = fopen("output","w");
    fprintf(out,"Number of Vertices : %u \n",v_number);
    fprintf(out,"Number of Edges : %u \n",array_number);
    unsigned* degree;
    degree =degree_find_list_w(list,v_number);
    fprintf(out,"Minimal Degree : %u \n",degree[0]);
    fprintf(out,"Maximal Degree : %u \n",degree[v_number-1]);
    if(v_number%2){
        fprintf(out,"median : %u \n",degree[v_number/2]);
    }else{
        unsigned median;
        median = (degree[v_number/2] + degree[v_number/2 -1])/2;
        fprintf(out,"median : %u \n",median);
    }
    fclose(out);
    free(degree);
    WeightedN* p;
    WeightedN* pointer;
    //IntNode** size = list+v_number;
    for(unsigned i =0 ;i<v_number;i++){
        pointer = list[i];
        while((pointer)!=NULL){
            p = pointer->next;
            free(pointer);
            pointer = p;
        }
    }
    free(list);
}


void free_list(IntNode** list, unsigned v_number,unsigned array_number){
    FILE* out;
    out = fopen("output","w");
    fprintf(out,"Number of Vertices : %u \n",v_number);
    fprintf(out,"Number of Edges : %u \n",array_number);
    unsigned* degree;
    degree =degree_find_list(list,v_number);
    fprintf(out,"Minimal Degree : %u \n",degree[0]);
    fprintf(out,"Maximal Degree : %u \n",degree[v_number-1]);
    if(v_number%2){
        fprintf(out,"median : %u \n",degree[v_number/2]);
    }else{
        unsigned median;
        median = (degree[v_number/2] + degree[v_number/2 -1])/2;
        fprintf(out,"median : %u \n",median);
    }
    fclose(out);
    free(degree);
    IntNode* p;
    IntNode* pointer;
    //IntNode** size = list+v_number;
    for(unsigned i =0 ;i<v_number;i++){
        pointer = list[i];
        while((pointer)!=NULL){
            p = pointer->next;
            free(pointer);
            pointer = p;
        }
    }
    free(list);
}

void free_matrix(char** matrix, unsigned v_number,unsigned array_number){
    FILE* out;
    out = fopen("output","w");
    fprintf(out,"Number of Vertices : %u \n",v_number);
    fprintf(out,"Number of Edges : %u \n",array_number);
    unsigned* degree;
    degree =degree_find_matrix(matrix,v_number);
    fprintf(out,"Minimal Degree : %u \n",degree[0]);
    fprintf(out,"Maximal Degree : %u \n",degree[v_number-1]);
    if(v_number%2){
        fprintf(out,"median : %u \n",degree[v_number/2]);
    }else{
        unsigned median;
        median = (degree[v_number/2] + degree[v_number/2 -1])/2;
        fprintf(out,"median : %u \n",median);
    }
    fclose(out);
    free(degree);
    char** p;
    char **size = matrix + v_number;
    for ( p = matrix; p < size; p++)
    {
        free(*p);
    }
    free(matrix);
}

void free_w_matrix(double** matrix, unsigned v_number,unsigned array_number){
    FILE* out;
    out = fopen("output","w");
    fprintf(out,"Number of Vertices : %u \n",v_number);
    fprintf(out,"Number of Edges : %u \n",array_number);
    unsigned* degree;
    degree =degree_find_matrix_w(matrix,v_number);
    fprintf(out,"Minimal Degree : %u \n",degree[0]);
    fprintf(out,"Maximal Degree : %u \n",degree[v_number-1]);
    if(v_number%2){
        fprintf(out,"median : %u \n",degree[v_number/2]);
    }else{
        unsigned median;
        median = (degree[v_number/2] + degree[v_number/2 -1])/2;
        fprintf(out,"median : %u \n",median);
    }
    fclose(out);
    free(degree);
    double** p;
    double **size = matrix + v_number;
    for ( p = matrix; p < size; p++)
    {
        free(*p);
    }
    free(matrix);
}

void clean_PQ(PriorityQueue* pq){
    HeapNode* heap = pq->heap;
    unsigned* position_array = pq->position_array;
    free(heap);
    free(position_array);
    free(pq);
}