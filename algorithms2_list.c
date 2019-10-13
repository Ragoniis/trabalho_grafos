#include "algorithms2_list.h"



//acha o caminho com u vetor de parent
void find_path(Stack* c,unsigned end, unsigned* parents){
    const unsigned no_parent = ~(0x1);
    IntNode v;
    v.value = end;
    unsigned parent;
    stack_push(c,v);
    while( (parent = parents[v.value])!= no_parent){
        v.value = parent;
        stack_push(c,v);
    }
    free(parents);
}

// Retorna a distância como unsigned e o Caminho mínimo em forma de pilha
ShortestPathW shortest_path_w(WeightedN** list,unsigned v_number, unsigned start, unsigned end, char status){
    //const unsigned infinite = ~(0x0);
    double* distance;
    unsigned* parent;
    struct shortest_path_response response;
    Stack s ={ NULL };
    if(status == 2){
        void** dijkstra;
        dijkstra = dijkstra_list(list,v_number,start);
        distance = (double*)  dijkstra[0];
        parent = (unsigned*) dijkstra[1];
        response.distance = distance[end];
        if(distance[end] == DBL_MAX){
            printf("∞\n");
        }else{
            find_path(&s,end, parent);   
        }
        free(dijkstra[0]);
        free(dijkstra);
        response.path = s;
    }else if(!(status)){
        unsigned** bfs;
        bfs = bfs_w_list(list,v_number,start);
        parent = bfs[0];
        response.distance = (double) bfs[1][end]; // Pega o vetor level que é igual a resposta
        find_path(&s,end, parent);
        free(bfs[1]);
        free(bfs);
        response.path = s;
    }else{
        printf("Grafo com pesos negativos. Não é possível calcular o menor caminho\n");
    }
    return response;
}

unsigned** bfs_w_list(WeightedN** list, unsigned v_number,unsigned index){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    unsigned* level;
    register const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    
    if((marking = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
    }
    if((level = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
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
    WeightedN* linked_list;
    IntNode v;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        linked_list=list[v.value];
        while (linked_list!= NULL){
            if((marking[linked_list->value]) == none){
                marking[linked_list->value] = v.value;
                level[linked_list->value] = level[v.value] +1;
                queue_push(&q,linked_list->value);
            }
            linked_list = linked_list->next;
        }

    }
    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    array[0]=  marking;
    array[1]=  level;
    //printf("OLha a BFS\n");
    //print_array(array[0],v_number);
    //print_array(array[1],v_number);
    return array;

}

// retorna array com o vetor dist na posição 0 e parent na 1
void** dijkstra_list(WeightedN** list,unsigned v_number,unsigned s){
    const unsigned infinite = ~(0x0); //Simboliza parte desconexa 
    const unsigned no_parent = ~(0x1); // Pai do primeiro vértice
    double* dist;
    unsigned* parent;
    if(!(dist = (double*) malloc(sizeof(double)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    if(!(parent = (unsigned*) malloc(sizeof(unsigned)*v_number))){
        printf("Out of memory");
        exit(1);
    }
    for(unsigned i =0;i<v_number;i++){
        dist[i] = DBL_MAX;
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
    WeightedN* pointer;
    unsigned heap_position;
    while((v = extract_min(pq))){
        pointer = list[v->value];
        dist[v->value] = v->key;
        while (pointer!= NULL){
            heap_position = position_array[pointer->value];
            if(heap[heap_position].key > (v->key + pointer->weight)){
                decrease_key(pq,pointer->value,(v->key + pointer->weight));
                parent[pointer->value] = v->value;
            }
            pointer = pointer->next;
        }
        free(v);
    }
    void** response;
    if(!(response = (void**) malloc(sizeof(void*)*2))){
        printf("Out of memory");
        exit(1);
    }
    clean_PQ(pq);
    response[0] = dist;
    response[1] = parent;
    return response;

}


void minimum_spanning_tree_list(WeightedN** list, unsigned v_number, char* s ){
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
    decrease_key(pq,144,0.0);
    //parent[6] = infinite;

    HeapNode* v = extract_min(pq);
    WeightedN* pointer = list[v->value];
    unsigned heap_position;
    //Roda um while antes para não colocar na lista uma aresta lixo 
    while (pointer!= NULL){
            heap_position = position_array[pointer->value];
            if(heap[heap_position].key > (pointer->weight)){
                decrease_key(pq,pointer->value,pointer->weight);
                parent[pointer->value] = v->value;
            }
            pointer = pointer->next;
    }
    free(v);
    unsigned v1,v2;
    double edge_weight;
    double mst_weight = 0;
    while((v = extract_min(pq))){
        //printHeap(pq);
        pointer = list[v->value];
        v1 = parent[v->value];
        v2 = v->value;
        edge_weight = v->key;
        mst_weight+= edge_weight;
        p = put_edge(p,v1,v2,edge_weight);
        while (pointer!= NULL){
            heap_position = position_array[pointer->value];
            if((heap[heap_position].key > (pointer->weight) && !(heap_position > pq->last_element))){
                decrease_key(pq,pointer->value,pointer->weight);
                parent[pointer->value] = v->value;
            }
            pointer = pointer->next;
        }
        free(v);
    }

    FILE* out;
    Edge* helper;
    out = fopen(s,"w");
    fprintf(out,"%lf\n", mst_weight);
    while ((p != NULL))
    {
        fprintf(out,"%u %u %lf\n",p->vertex1,p->vertex2,p->weight);
        helper = p->next;
        free(p);
        p = helper;
    }
    free(parent);
    fclose(out);
    clean_PQ(pq);

}



double eccentricity_list(WeightedN** list, unsigned v_number, unsigned vertex,unsigned status){
    
    double eccentricity;
    if(!status){
        //Grafos sem peso
        unsigned** response;
        response = bfs_w_list(list,v_number,vertex);
        eccentricity= max_array(response[1],v_number);
        free(response[0]);
        free(response[1]);
        free(response);
        return eccentricity;
    }else if(status == 2){
        void** dijkstra;
        double* dist;
        //Grafos com peso positvo
        dijkstra = dijkstra_list(list,v_number,vertex);
        dist = (double *)dijkstra[0];
        eccentricity= especial_max_array(dist,v_number);
        free(dijkstra[0]);
        free(dijkstra[1]);
        free(dijkstra);
        return eccentricity;
    }else{
        printf("Grafos com pesos negativos, não é possível calcular a Excentricidade\n");
        return -1;
    }
}