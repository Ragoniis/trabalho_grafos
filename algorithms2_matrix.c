#include "algorithms2_matrix.h"

unsigned** bfs_matrix_w(double** matrix, unsigned index,unsigned v_number){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    unsigned* level;
    const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    if((marking = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((level = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
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
        level[i] = none;
    }
    marking[index] = explored;
    level[index] =0;
    queue_push(&q,index);
    IntNode v;
    register unsigned i;
    double* row;
    while ( (q.top) != NULL)
    {
        printf("Flag!!\n");
        v = queue_pop(&q);
        i= v.value;
        row = matrix[i];
        for(unsigned j =0 ; j< v_number; j++){
            if((row[j])!= DBL_MAX){
                if(marking[j] == none){
                    marking[j] = i;
                    level[j] = level[i] +1;
                    queue_push(&q,j);
                }
            }
        }
    }

    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    array[0]=  marking;
    array[1]=  level;
    return array;

}

unsigned** dijkstra_matrix(double** matrix,unsigned v_number,unsigned s){
    const unsigned infinite = ~(0x0); //Simboliza parte desconexa 
    const unsigned no_parent = ~(0x1); // Pai do primeiro vértice
    unsigned* dist;
    unsigned* parent;
    if(!(dist = (unsigned*) malloc(sizeof(unsigned)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    if(!(parent = (unsigned*) malloc(sizeof(unsigned)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    for(unsigned i =0;i<v_number;i++){
        dist[i] = infinite;
        parent[i] = infinite;
    }
    PriorityQueue* pq;
    if(!(pq = (PriorityQueue*) malloc(sizeof(PriorityQueue)))){
        printf("Out of memory");
        exit(1);
    }
    initialize_PQ(pq,v_number);
    unsigned* position_array = pq->position_array;
    HeapNode* heap = pq->heap;
    decrease_key(pq,s,0.0);
    parent[s] = no_parent;
    HeapNode* v;
    double* row;
    unsigned heap_position;
    while((v = extract_min(pq))){
        row = matrix[v->value];
        dist[v->value] = v->key;
        for(unsigned j =0; j< v_number; j++){
            heap_position = position_array[j];
            if(heap[heap_position].key > (v->key + row[j])){
                //printf("Atualizando %u pela adj %u com o peso %lf\n",j,v->value,(v->key + pointer->weight));
                decrease_key(pq,j,(v->key + row[j]));
                parent[j] = v->value;
            }
        }
        free(v);
    }
    unsigned** response;
    if(!(response = (unsigned**) malloc(sizeof(unsigned*)*2))){
        printf("Out of memory");
        exit(1);
    }
    clean_PQ(pq);
    response[0] = dist;
    response[1] = parent;
    return response;

}

void minimum_spanning_tree_matrix(double** matrix, unsigned v_number, char* s ){
    const unsigned infinite = ~(0x0); //Simboliza sem parent 
    //const unsigned no_parent = ~(0x1);
    unsigned* parent;
    if(!(parent = (unsigned*) malloc(sizeof(unsigned)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    for(unsigned i =0;i<v_number;i++){
        parent[i] = infinite;
    }
    //Inicializa a Heap
    PriorityQueue* pq;
    if(!(pq = (PriorityQueue*) malloc(sizeof(PriorityQueue)))){
        printf("Out of memory");
        exit(1);
    }
    initialize_PQ(pq,v_number);
    unsigned* position_array = pq->position_array;
    HeapNode* heap = pq->heap;

    //Inicializa o primeiro vertice
    Edge* p = NULL;
    decrease_key(pq,0,0.0);
    parent[0] = infinite;

    HeapNode* v = extract_min(pq);
    double* row = matrix[v->value];
    unsigned heap_position;

    //Roda um while antes para não colocar na lista uma aresta lixo 
    for(unsigned j =0; j< v_number; j++){
            heap_position = position_array[j];
            if(heap[heap_position].key > (row[j])&& (j != parent[v->value])){
                //printf("Atualizando %u pela adj %u com o peso %lf\n",j,v->value,(v->key + pointer->weight));
                decrease_key(pq,j,row[j]);
                parent[j] = v->value;
            }
            
    }
    free(v);
    unsigned v1,v2;
    double edge_weight;
    double mst_weight = 0;
   
    while((v = extract_min(pq))){
        row = matrix[v->value];
        v1 = parent[v->value];
        v2 = v->value;
        edge_weight = v->key;
        mst_weight+= edge_weight;
        p = put_edge(p,v1,v2,edge_weight);
        for(unsigned j =0; j< v_number; j++){
            heap_position = position_array[j];
            if(heap[heap_position].key > (row[j])&& (j != parent[v->value])){
                //printf("Atualizando %u pela adj %u com o peso %lf\n",j,v->value,(v->key + pointer->weight));
                decrease_key(pq,j,row[j]);
                parent[j] = v->value;
            }
        }
        free(v);
    }
    FILE* out;
    Edge* helper;
    out = fopen(s,"w");
    fprintf(out,"%lf\n", mst_weight);
    while ((p != NULL))
    {
        fprintf(out,"%u %u %lf\n",p->vertex1+1,p->vertex2+1,p->weight);
        helper = p->next;
        free(p);
        p = helper;
    }
    fclose(out);
    clean_PQ(pq);

}

double eccentricity_matrix(double** matrix, unsigned v_number, unsigned vertex,unsigned status){
    unsigned** response;
    double eccentricity;
    if(!status){
        //Grafos sem peso
        response = bfs_matrix_w(matrix,v_number,vertex);
        eccentricity= especial_max_array(response[1],v_number);
        free(response[0]);
        free(response[1]);
        free(response);
        return eccentricity;
    }else if(status == 2){
        //Grafos com peso positvo
        response = dijkstra_matrix(matrix,v_number,vertex);
        eccentricity= especial_max_array(response[0],v_number);
        free(response[0]);
        free(response[1]);
        free(response);
        return eccentricity;
    }else{
        printf("Grafos com pesos negativos, não é possível calcular a Excentricidade\n");
        return -1;
    }
}