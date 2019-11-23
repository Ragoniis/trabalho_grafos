#include "algorithms3_list.h"


double** all_paths_bellman_ford_list(WeightedN** list,unsigned v_number){
    double** response;
    WeightedN** residual_list;
    WeightedN* pointer,* p;
    if((response = (double **)malloc (v_number*sizeof(double*)))==NULL){
        printf("Out of Memory Error");
        exit(1);
    }
    if(( residual_list = (WeightedN**) calloc(v_number,sizeof(WeightedN**)) )== NULL){
        printf("Out of Memory Error");
        exit(1);
    }
    WeightedN* ll;
    for (unsigned i =0; i<v_number;i++){
        ll = *(list+ i);
        while(ll != NULL){ 
            *(residual_list+(ll->value)) = put_wnode(*(residual_list+(ll->value)) ,i,ll->weight);
            ll = ll->next;
        }         
    }
    for(unsigned i =0;i<v_number; i++){
        if((response[i] = bellman_ford_list(residual_list,v_number,i)) == NULL){
            free(response);
            for(unsigned i =0 ;i<v_number;i++){
            pointer = residual_list[i];
            while((pointer)!=NULL){
            p = pointer->next;
            free(pointer);
            pointer = p;
        }
    }
    free(residual_list);
            return NULL;
        }
    }
    for(unsigned i =0 ;i<v_number;i++){
        pointer = residual_list[i];
        while((pointer)!=NULL){
            p = pointer->next;
            free(pointer);
            pointer = p;
        }
    }
    free(residual_list);
    return response;

} 

double* bellman_ford_list(WeightedN** list,unsigned v_number,unsigned t){
    double* distance; 
    if((distance = (double *) malloc(v_number*sizeof(double))) == NULL){
        printf("Out of Memory Error");
        exit(1);
    }    
    for(unsigned i =0;i<v_number;i++){
        distance[i] = DBL_MAX;
    }
    distance[t]=0;
    double min;
    WeightedN* ll; 
    char changed=0;
    for(unsigned i =1;i<v_number;i++){
        changed =0;
        for(unsigned v=0; v<v_number; v++){
             ll = list[v];
             min = DBL_MAX;
             //printf("OPa ai o %u\n",ll->value);
             while(ll != NULL){
                 min = ((ll->weight + distance[ll->value]) < min) ?
                    (ll->weight + distance[ll->value]):
                    min;
                 ll = ll->next;
             }
            if (min<distance[v]){
                distance[v] = min;
                changed= 1;
            }
        }
        if(changed == 0){
            goto RETURN;
        }
    }
    changed =0;
    for(unsigned v=0; v<v_number; v++){
        ll = list[v];
        min = DBL_MAX;
        while(ll != NULL){
                 min = ((ll->weight + distance[ll->value]) < min) ?
                    (ll->weight + distance[ll->value]):
                    min;
                 ll = ll->next;
             }
            if (min<distance[v]){
                distance[v] = min;
                changed= 1;
            }
        }
        if(changed == 1){
            free(distance);
            return NULL;
        }
    RETURN:return distance;
}


typedef struct snode
{
    /* data */
    unsigned int value;
    struct snode* next;
    struct snode* back;

}SNode;

SNode* put_snode(SNode* p ,unsigned int value){
    SNode* new_pointer;
    if ((new_pointer = (SNode *) malloc(sizeof(SNode)))){
        new_pointer->value = value;
        new_pointer->next = p;
        new_pointer->back = NULL;
        if(p != NULL){
            p->back = new_pointer;
        }
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}
typedef struct aedge{
    unsigned ll_index;
    SNode* e_p;//edge pointer
    struct aedge* next;
}AugEdge;

AugEdge* put_aenode(AugEdge* p ,unsigned ll_index,SNode* e_p){
    AugEdge* new_pointer;
    if ((new_pointer = (AugEdge * ) malloc(sizeof(AugEdge)))){
        new_pointer->e_p = e_p;
        new_pointer->next = p;
        new_pointer-> ll_index = ll_index;
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}

void reverse_edges(SNode** list,unsigned v_number,AugEdge* llist){
    AugEdge* pointer;
    SNode* node;
    SNode* next_node;
    SNode* back_node;
    char flag= 0;
    do {
        node = llist->e_p;
        if(list[llist->ll_index] == node){
           next_node = node->next; 
           list[llist->ll_index] = next_node;
           if(next_node)
               next_node->back = NULL;
           list[node->value] = put_snode(list[node->value],llist->ll_index);
           free(node); 
        }else {
            next_node = node->next;
            back_node = node->back;
            //printf("nn:%p bn:%p n:%p l:%p\n",next_node->back,back_node,node,list[llist->ll_index]);
            if(back_node != NULL)
                back_node->next = next_node;
            if(next_node)
                next_node->back = back_node;
            list[node->value] = put_snode(list[node->value],llist->ll_index);
            free(node);
        }


    }while((llist = llist->next) != NULL);

}

typedef struct squeue
{
    SNode* rear;
    SNode* top;
} SQueue;

SNode s_queue_pop(SQueue* q){
    SNode* p_v;
    SNode vertice;
    p_v = q->top;
    q->top = p_v->next;
    vertice = *(p_v);
    free(p_v);
    return (vertice);
}


void s_queue_push(SQueue* q, unsigned index){
    
    SNode* last = q->rear;
    SNode* new_pointer;
    new_pointer = (SNode* )malloc(sizeof(SNode));
    if (new_pointer){
        if(q->top){
            new_pointer->value = index;
            new_pointer->next = NULL;
            last->next = new_pointer;
            q->rear = new_pointer;
        }else {
            new_pointer->value =index;
            new_pointer->next = NULL;
            q->rear = new_pointer;
            q->top = new_pointer;
        }
        //return new_pointer;
    }else
    {
        printf("Fatal error Out of memory");
        exit(1);
    }
}


AugEdge* strange_bfs_list(SNode** list, unsigned index, unsigned v_number,char* saturation,AugEdge** parent){
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
    SQueue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number; i++){
        marking[i] = none;
    }
    marking[index] = explored;
    s_queue_push(&q,index);
    SNode* linked_list;
    SNode v;
    AugEdge * tree = NULL;
    AugEdge* before;
    parent[index] = NULL;
    char flag = 0;
    while ( (q.top) != NULL)
    {
        v = s_queue_pop(&q);
        linked_list=list[v.value];
        while (linked_list!= NULL){
            if((marking[linked_list->value]) == none){
                marking[linked_list->value] = v.value;
                s_queue_push(&q,linked_list->value);
                before = parent[v.value];
                tree = put_aenode(before,v.value,linked_list);
                parent[linked_list->value] = tree;
                if(saturation[linked_list->value] == 0){
                    while((q.top)!= NULL){
                         s_queue_pop(&q);
                    }
                    saturation[linked_list->value] = 1;
                    saturation[index] = 1;
                    free(marking);
                    return  tree;
                }
            }
            linked_list = linked_list->next;
        }
    }
    free(marking);
    return NULL;

}


MatchingEdge* put_medge(MatchingEdge* p ,unsigned v1,unsigned v2){
    MatchingEdge* new_pointer;
    if ((new_pointer = (MatchingEdge * ) malloc(sizeof(MatchingEdge)))){
        new_pointer->v1 = v1;
        new_pointer->v2 = v2;
        new_pointer->next = p;
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}

MatchingEdge* matching_list(BipartiteGraphList* graph, unsigned v_number){
    BipartiteGraphList* residual_graph;
    IntNode** list = graph->graph;
    char* sets = graph->sets;
    SNode** residual_list;
    char* saturation;
    if((saturation= (char* ) calloc(v_number,sizeof(char))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((residual_graph =  ( BipartiteGraphList *) malloc(sizeof(BipartiteGraphList))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((residual_list = (SNode ** ) calloc(v_number,sizeof(SNode*))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    IntNode * ll;
    for (unsigned i =0; i<v_number;i++){
        ll = *(list+ i);
        if(sets[i] == 0 ){
            while(ll != NULL){ 
                *(residual_list+i) = put_snode(*(residual_list+i) , ll->value);
                ll = ll->next;
            }
        }         
    }
//  print_list_int(residual_list, v_number);
    AugEdge* tree;
    unsigned number_calls =0;
    unsigned number_nulls =0;
    AugEdge** parent;
    if((parent = (AugEdge ** ) calloc(v_number,sizeof(AugEdge*))) == NULL){
        printf("Out of memory");
        exit(1);
    }  
    while(1){
        for  (unsigned i =0; i<v_number;i++){
            if(saturation[i] == 0 && sets[i] == 0){
                number_calls++;
                tree = strange_bfs_list(residual_list,i,v_number,saturation,parent);
                if(tree == NULL){
                    //printf("hihihih");
                    number_nulls++;
                    continue;
                }
                reverse_edges(residual_list,v_number,tree);
                for (AugEdge** p  = parent; p < (parent+v_number); p++)
                {
                         free(*p);
                         (*p) = NULL;
                }
            }
        }
        if(number_calls == number_nulls){
            break;
        }
        number_calls= 0;
        number_nulls =0;
    }
    
    free(parent);
    
    MatchingEdge* response = NULL;
    for (unsigned i = 0; i<v_number; i++){
        if(saturation[i] == 0 && sets[i] == 1){
            printf("MelhorFlaag1 %u \n",i);
        }
        if(saturation[i] == 0 && sets[i] == 0){
        }
        if(sets[i]==1 && saturation[i]==1){
            //printf("v1 :%u v2: %p\n",i,(residual_list[i]));
            response = put_medge(response,i,(residual_list[i])->value);
        }
    }
    SNode* pointer;
    SNode* p;

    for(SNode** p = residual_list;p<(residual_list+v_number); p++){
        pointer = *p;
        SNode* temp;
        while (pointer)
        {
            //printf("pointer:%p np%p \n",pointer, pointer->next);
            temp = pointer;
            pointer = pointer->next;
            free(temp);
            //printf("pointer:%p np%p \n",pointer, pointer->next);
        }
        //free(pointer);
    }
    free(residual_list);
    free(residual_graph);
    free(saturation);
    return response;
    
}

BipartiteGraphList* check_bipartiteness_list(IntNode** list, unsigned v_number){
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
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        linked_list=list[v.value];
        while (linked_list!= NULL){
            if((marking[linked_list->value]) == none){
                marking[linked_list->value] = v.value;
                
                color[linked_list->value] = ! (color[v.value]);
                queue_push(&q,linked_list->value);
            }else if(color[v.value] == color[linked_list->value]){
                return NULL;
            }
            linked_list = linked_list->next;

        }
    }
    for (unsigned i =0; i<v_number;i++){
        if (color[i] == 2)
            return NULL; //Grafo nao e conexo
    }
    BipartiteGraphList* graph;
    if((graph = (BipartiteGraphList* ) malloc(sizeof(BipartiteGraphList)))== NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    graph->graph = list;
    graph->sets = color;
    free(marking);
    return graph;
}



