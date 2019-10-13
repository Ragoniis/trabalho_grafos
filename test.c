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

unsigned v_number_global;
unsigned array_number = 0;
//Estudos de Caso Lista

int main(void){
    WeightedN** list;
    char status = -1;
    list = read_list_w_int(&v_number_global,&array_number,&status,"grafo_4.txt");

    //Para testar grafo de Colaboração
    /*
    ShortestPathW sw;  
    printf("Pergunta 1 -------------------------------\n");
    sw =shortest_path_w(list,v_number_global,2721,11364,status); //Turing
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw =shortest_path_w(list,v_number_global,2721,471364,status); // Kruskal
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw =shortest_path_w(list,v_number_global,2721,5708,status);// Kleinberg
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw =shortest_path_w(list,v_number_global,2721,11385,status);// Tardos
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw =shortest_path_w(list,v_number_global,2721,343929,status); // Daniel
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    printf("-----------------------------------------\n");
    printf("Pergunta 2 -------------------------------\n");
    
    */
    
    ShortestPathW sw;    
    printf("Pergunta 1 -------------------------------\n");
    sw = shortest_path_w(list,v_number_global,0,9,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w(list,v_number_global,0,19,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w(list,v_number_global,0,29,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w(list,v_number_global,0,39,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w(list,v_number_global,0,49,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    printf("-----------------------------------------\n");
    printf("Pergunta 2 -------------------------------\n");
    
    double eccentricity[5];

    eccentricity[0] = eccentricity_list(list,v_number_global,9,status);
    eccentricity[1] =eccentricity_list(list,v_number_global,19,status);
    eccentricity[2] =eccentricity_list(list,v_number_global,29,status);
    eccentricity[3] =eccentricity_list(list,v_number_global,39,status);
    eccentricity[4] =eccentricity_list(list,v_number_global,49,status);
  
    for(unsigned i =0; i<5; i++){
        printf("excentricidade %u : %lf\n",i,eccentricity[i]);
    }
    printf("-----------------------------------------\n");


    printf("Pergunta 3 -------------------------------\n");
    unsigned value;
    clock_t start,end;
    double sum = 0.0;
    for (unsigned i = 0; i < 100; i++)
    {
        value = rand() % v_number_global;
        start = clock();
        eccentricity_list(list,v_number_global,value,status);
        end = clock();
        sum += ((double) (end - start))/CLOCKS_PER_SEC;
    } 
    printf("Tempo da excentricidade %lf \n" ,sum/100);
    printf("-----------------------------------------\n");


    printf("Pergunta 4 -------------------------------\n");
    clock_t start2,end2;
    start2 = clock();
    minimum_spanning_tree_list(list,v_number_global,"output_mst");
    end2 = clock();
    sum = ((double) (end2 - start2))/CLOCKS_PER_SEC;
    printf("Tempo da MST %lf \n" ,sum);
    
    free_w_list(list,v_number_global,array_number);
    
    return 0;
}
/*

//Estudos de Caso Matriz

int main(void){
    double** matrix;
    char status = -1;
    matrix = read_matrix_w(&v_number_global,&array_number,&status,"grafo_2.txt");
    
    ShortestPathW sw;    
    printf("Pergunta 1 -------------------------------\n");
    sw = shortest_path_w_matrix(matrix,v_number_global,0,9,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w_matrix(matrix,v_number_global,0,19,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w_matrix(matrix,v_number_global,0,29,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w_matrix(matrix,v_number_global,0,39,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    sw = shortest_path_w_matrix(matrix,v_number_global,0,49,status);
    printf("Distância: %lf \n",sw.distance);
    print_stack(&(sw.path));
    printf("-----------------------------------------\n");
    printf("Pergunta 2 -------------------------------\n");

    double eccentricity[5];
    eccentricity[0] = eccentricity_matrix(matrix,v_number_global,9,status);
    eccentricity[1] =eccentricity_matrix(matrix,v_number_global,19,status);
    eccentricity[2] =eccentricity_matrix(matrix,v_number_global,29,status);
    eccentricity[3] =eccentricity_matrix(matrix,v_number_global,39,status);
    eccentricity[4] =eccentricity_matrix(matrix,v_number_global,49,status);
    for(unsigned i =0; i<5; i++){
        printf("excentricidade %u : %lf\n",i,eccentricity[i]);
    }
    printf("-----------------------------------------\n");
    printf("Pergunta 3 -------------------------------\n");
    clock_t start,end;
    double sum =0.0;
    unsigned value;
    
    for (unsigned i = 0; i < 100; i++)
    {
        value = rand() % v_number_global;
        start = clock();
        eccentricity_matrix(matrix,v_number_global,value,status);
        end = clock();
        sum += ((double) (end - start))/CLOCKS_PER_SEC;
    }
    printf("Tempo da excentricidade %lf \n" ,sum/100);
    printf("-----------------------------------------\n");
    printf("Pergunta 4 -------------------------------\n");
    clock_t start2,end2;
    start2 = clock();
    minimum_spanning_tree_matrix(matrix,v_number_global,"output_mst");
    end2 = clock();
    sum = ((double) (end2 - start2))/CLOCKS_PER_SEC;
    printf("Tempo da MST %lf \n" ,sum);
    free_w_matrix(matrix,v_number_global,array_number);
    
}
*/