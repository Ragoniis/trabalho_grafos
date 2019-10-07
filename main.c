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

//Globais pro arquivo
unsigned v_number_global;
FILE *fp;

unsigned array_number =0;

int main (int argc,char** argv ){
    const char *s;
    char state;
    s = "as_graph.txt";
    printf("%s\n",s);
    fp=fopen(s, "r");
    fscanf(fp,"%u", &v_number_global);
    printf("%u\n",v_number_global);
    //int c;
    char** matrix;
    IntNode** list;
    unsigned index;
    unsigned** bfs_return;
    //unsigned v;
    //double bfs_list_t;
    double bfs_matrix_t;
    //double diameter_list_t;
    //double diameter_matrix_t;
    clock_t start,end;
    //unsigned** array_pointer;

    state =1;
    index =10;
    list = read_list_int(v_number_global,fp,&array_number);
    fclose(fp);
    start = clock();
    //unsigned v2 =20;
	
    bfs_return = bfs_list(list,index,v_number_global);
    shortest_path(30,bfs_return[0]);
	
	/*
    for (unsigned i = 0; i < 1000; i++)
    {
      array_pointer = bfs_list(list,i);
      free(array_pointer[0]);
      free(array_pointer[1]);
      free(array_pointer);
    }
	*/
	
    //sorted_bfs_list(list,index);
    //pseudo_diameter_list(list);
    end = clock();
    bfs_matrix_t = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo da bfs %f \n" ,bfs_matrix_t);


    FILE* out;
    out = fopen("output","w");
    fprintf(out,"Number of Vertices : %u \n",v_number_global);
    fprintf(out,"Number of Edges : %u \n",array_number);
    unsigned* degree;
    if(state){
        start = clock();
        degree = degree_find_list(list,v_number_global);
        end = clock();
        bfs_matrix_t = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tempo do output %f \n" ,bfs_matrix_t);
        fprintf(out,"Minimal Degree : %u \n",degree[0]);
        fprintf(out,"Maximal Degree : %u \n",degree[v_number_global-1]);
        fprintf(stdout,"Maximal Degree : %u \n",degree[v_number_global-1]);
         /*
        for ( unsigned i = 0; i < v_number_global; i++)
        {
            printf("%u ,", degree[i]);
        }
        */
         if(v_number_global%2){
             fprintf(out,"median : %u \n",degree[v_number_global/2]);
         }else{
             unsigned median;
             median = (degree[v_number_global/2] + degree[v_number_global/2 -1])/2;
             fprintf(out,"median : %u \n",median);
        }
        free(degree);

    }else{
        start = clock();
        degree =degree_find_matrix(matrix,v_number_global);
        end = clock();
        bfs_matrix_t = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tempo do output %f \n" ,bfs_matrix_t);

        fprintf(out,"Minimal Degree : %u \n",degree[0]);
        fprintf(out,"Maximal Degree : %u \n",degree[v_number_global-1]);
        if(v_number_global%2){
            fprintf(out,"median : %u \n",degree[v_number_global/2]);
        }else{
            unsigned median;
            median = (degree[v_number_global/2] + degree[v_number_global/2 -1])/2;
            fprintf(out,"median : %u \n",median);
        }
        free(degree);

    }
    fclose(out);
    if(state)
        free_list(list,v_number_global);
    else
        free_matrix(matrix,v_number_global);
    return 0;

}
