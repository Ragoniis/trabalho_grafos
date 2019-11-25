#include "algorithms3_matrix.h"

double** all_paths_bellman_ford_matrix(double** matrix,unsigned v_number){
    double** response;
    if((response = (double **)malloc (v_number*sizeof(double*)))==NULL){
        printf("Out of Memory Error");
        exit(1);
    }
    unsigned null_counter =0;
    for(unsigned j =0;j<v_number; j++){
        if((response[j] = bellman_ford_matrix(matrix,v_number,j)) == NULL){
                null_counter++;
        }
    }
    if(null_counter == v_number){
        return NULL;
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

unsigned* strange_bfs_matrix(char** matrix, unsigned index, unsigned v_number,char* saturation,unsigned* final){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    register const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    if((marking = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    Queue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number; i++){
        marking[i] = none;
    }
    marking[index] = explored;
    queue_push(&q,index);
    char flag = 0;
    IntNode v;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        for(unsigned w =0;w<v_number;w++){
            if(matrix[v.value][w]){
                if((marking[w]) == none){
                    marking[w] = v.value;
                    queue_push(&q,w);
                    if(saturation[w] == 0){
                        while((q.top)!= NULL){
                            queue_pop(&q);
                        }
                        saturation[w] = 1;
                        saturation[index] = 1;
                        (*final) =w;
                        return marking;
                    }
                }
            }
        }
    }
    free(marking);
    return NULL;

}



MatchingEdge* matching_matrix(BipartiteGraphMatrix* graph, unsigned v_number){
    BipartiteGraphMatrix* residual_graph;
    char** matrix = graph->graph;
    char* sets = graph->sets;
    char** residual_matrix;
    char* saturation;
    const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    if((saturation= (char* ) calloc(v_number,sizeof(char))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((residual_graph =  ( BipartiteGraphMatrix *) malloc(sizeof(BipartiteGraphMatrix))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((residual_matrix = (char ** ) calloc(v_number,sizeof(char*))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    IntNode * ll;
    for (unsigned i =0; i<v_number;i++){
        if((residual_matrix[i] = (char * ) calloc(v_number,sizeof(char))) == NULL){
            printf("Out of memory");
            exit(1);
        //return 1;
        }
        if(sets[i] == 0 ){
            for (unsigned j =0; j<v_number;j++){
              if(matrix[i][j] == 1){
                 residual_matrix[i][j] = 1; 
              }  
            }
        }         
    }
//  print_list_int(residual_list, v_number);
    unsigned number_calls =0;
    unsigned number_nulls =0;
    unsigned* parent;
    unsigned w,v;
    unsigned level =0;
    while(1){
        for  (unsigned i =0; i<v_number;i++){
            if(saturation[i] == 0 && sets[i] == 0){
                number_calls++;
                parent = strange_bfs_matrix(residual_matrix,i,v_number,saturation,&w);
                if(parent == NULL){
                    number_nulls++;
                    continue;
                }
                v =parent[w];
                while(v != explored){
                    if(residual_matrix[w][v] ==1){
                        residual_matrix[w][v]=0;
                        residual_matrix[v][w]=1;
                    }else{
                        if(residual_matrix[w][v]!=0)
                            printf("haaaaaaaaaa %u\n",residual_matrix[w][v]);
                        residual_matrix[w][v]=1;
                        residual_matrix[v][w]=0;
                    }
                    w = v;
                    v =parent[w];
                }
                free(parent);
            }
        }
        if(number_calls == number_nulls){
            break;
        }
        number_calls= 0;
        number_nulls =0;
    }
    
    MatchingEdge* response = NULL;
    for (unsigned i = 0; i<v_number; i++){
        for(unsigned j =0;j<v_number;j++){
            if(residual_matrix[i][j]){
                if(saturation[i] == 0 && sets[i] == 1){
                    //printf("MelhorFlaag1 %u \n",i);
                }
                if(saturation[i]==1 && sets[j] == 0 && sets[i] == 1 && saturation[j] ==1){
                    //printf("v1 :%u v2: %u \n",i,j);
                    response = put_medge(response,i,j);
                }
            }
        }
    } 
    for(unsigned i=0;i<v_number;i++){
        free(residual_matrix[i]);
    }
    free(residual_matrix);
    free(residual_graph);
    free(saturation);
    return response;
    
}

BipartiteGraphMatrix* check_bipartiteness_matrix(char** matrix, unsigned v_number){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo to de 4 bilh�es de vertices, isso n�o � um problema
    unsigned index = 0;
    unsigned* marking;
    char* color;
    register const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    if((marking = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    
    if((color = (char* ) malloc(v_number*sizeof(char))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    Queue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number; i++){
        marking[i] = none;
        color[i] =2;
    }
    marking[index] = explored;
    color[index] =0;
    queue_push(&q,index);
    IntNode* linked_list;
    IntNode v;
    WHILE:while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        //linked_list=list[v.value];
        for(unsigned w= 0;w<v_number;w++){
            if(matrix[v.value][w]){
                if((marking[w]) == none){
                    marking[w] = v.value;
                    color[w] = ! (color[v.value]);
                    queue_push(&q,w);
                }else if(color[v.value] == color[w]){
                    return NULL;
                }
            }
        }
    }
    for (unsigned i =0; i<v_number;i++){
        if (color[i] == 2){
            color[i] =0;
            marking[i] = explored;
            queue_push(&q,i);
            goto WHILE;
        }
            
    }
    BipartiteGraphMatrix* graph;
    if((graph = (BipartiteGraphMatrix* ) malloc(sizeof(BipartiteGraphMatrix)))== NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    graph->graph = matrix;
    graph->sets = color;
    free(marking);
    return graph;
}