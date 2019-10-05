#include <stdio.h>
#include <stdlib.h>
//#define Matrix(i,j) matrix[i][j-i-1]
//#define Matrix(i,j) (j>i) ? matrix[i][j-i-1] : matrix[j][i-j-1]
#include <string.h>
#include <time.h>
#include <math.h>


//Globais pro arquivo
unsigned v_number_global;
FILE *fp;
long unsigned array_number =0;
//Globais pro projeto

//Estruturas de dados
typedef struct int_node
{
    /* data */
    unsigned int value;
    struct int_node* next;

} IntNode;

typedef struct stack
{
    IntNode* top;
}Stack;

typedef struct queue
{
    IntNode* rear;
    IntNode* top;
} Queue;

//Prototipos de Funções
static inline IntNode queue_pop(Queue* q);
static inline void queue_push(Queue* q, unsigned index);
void print_queue(Queue* q);
char** readMatrix(unsigned v_number);
IntNode** read_list_int(unsigned v_number);
void print_list_int(IntNode** p);
void print_matrix(char** matrix);
static inline unsigned** bfs_list(IntNode** list, unsigned index);
unsigned** sorted_bfs_list(IntNode** list, unsigned index);
unsigned**  bfs_matrix(char** matrix, unsigned index);
unsigned shortest_path(unsigned v2,unsigned* marking);
unsigned diameter_list(IntNode** list);
unsigned pseudo_diameter_list(IntNode** list);
unsigned diameter_matrix(char** matrix);
unsigned* degree_find_matrix(char** matrix);
unsigned* degree_find_list(IntNode** list);
void free_matrix(char ** matrix);
void free_list(IntNode** list);
unsigned* dfs_list(IntNode** list, unsigned index);

int main (int argc,char** argv ){
    const char *s;
    char state;
    s = "as_graph.txt";
    printf("%s\n",s);
    fp=fopen(s, "r");
    fscanf(fp,"%u", &v_number_global);
    printf("%u\n",v_number_global);
    int c;
    char** matrix;
    IntNode** list;
    unsigned index;
    unsigned** bfs_return;
    unsigned v;
    double bfs_list_t;
    double bfs_matrix_t;
    double diameter_list_t;
    double diameter_matrix_t;
    clock_t start,end;
    unsigned** array_pointer;

    state =1;
    index =10;
    list = read_list_int(v_number_global);
    fclose(fp);
    start = clock();
    //unsigned v2 =20;
	
    bfs_return = bfs_list(list,index);
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
    fprintf(out,"Number of Edges : %lu \n",array_number);
    unsigned* degree;
    if(state){
        start = clock();
        degree = degree_find_list(list);
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
        degree =degree_find_matrix(matrix);
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
        free_list(list);
    else
        free_matrix(matrix);
    return 0;

}


void free_matrix(char** matrix){
    char** p;
    char **size = matrix + v_number_global;
    for ( p = matrix; p < size; p++)
    {
        free(*p);
    }
    free(matrix);
}

unsigned* degree_find_matrix(char** matrix){
    unsigned* degree_array;
    unsigned degree;
    unsigned max_degree = ~(0x0);
    if((degree_array = (unsigned * )malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
    }

    for(register unsigned j = 0; j<v_number_global; j++){
        degree =0;
        for(unsigned i =0; i<v_number_global;i++){
            //printf(" linha i%d coluna j%d %d\n",j,i,matrix[j][i]);
            if(matrix[j][i]==1){
                degree++;
            }
        }
        degree_array[j] = degree;
    }
    int cmpfunc (const void * a, const void * b);
    qsort(degree_array,v_number_global,sizeof(unsigned),cmpfunc);
    //printf("max degree %d\n",max_degree);
    return degree_array;
}

unsigned* degree_find_list(IntNode** list){
    unsigned* degree_array;
    unsigned degree;
    IntNode* linked_list;
    if((degree_array = (unsigned * )malloc(sizeof(unsigned)*v_number_global)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    for(unsigned i =0; i< v_number_global; i++){
        degree =0;
        linked_list= list[i];
        while (linked_list!= NULL){
            linked_list = linked_list->next;
            degree++;
        }
        degree_array[i] =degree;
    }
    int cmpfunc (const void * a, const void * b);
    qsort(degree_array,v_number_global,sizeof(unsigned),cmpfunc);
    return degree_array;
}

int cmpfunc (const void * a, const void * b){
        unsigned ai = *( unsigned* )a;
        unsigned bi = *( unsigned* )b;
        int r;
        r = (ai<bi) ? -1 :  1;
        return r;

}

void print_matrix(char** matrix){
    for (unsigned i= 0;  i< v_number_global; i++){
        for(unsigned j = (i+1); j< v_number_global;j++ ){
            printf("linha %d coluna %d %i \n",i,j,Matrix(i,j));}
    }
}

char** readMatrix(unsigned v_number){

    //aloca Espa�o para matriz

    char** p;
    if((p = (char** ) calloc(v_number_global, sizeof(char*))) == NULL){
        printf("Fatal Error FLAG\n");
        exit(1);
    }
    for(unsigned i = 0;i<v_number;i++){
        if((p[i] = (char *) calloc(v_number_global,sizeof(char))) == NULL){
            printf("Fatal Error Out of Memory");
            exit(1);
        }
    }
    /*
    for(unsigned i = 1; i<=(v_number) ; i++){
        if((p[i-1] = (char *) calloc((v_number-i), sizeof(char))) == NULL){
            printf("Fatal Error FLAG2\n");
            exit(1);
        }
        //printf("Flag %d \n" ,p[i][1]);
    }
    */
    int a,b;
    unsigned count=0;
    unsigned count2=0;
    while((fscanf(fp,"%u %u",&a,&b)) != EOF){
        //printf("a= %d b = %d %d\n ",a,b,v_number);
        /*
        if((a) == 1 && (b) == 22){
            printf(" a %u e b %u\n",a,b);
        }
        if(a == 1){
            count++;
            if(p[a-1][b-1]== 1){
                printf("Matrix %d a %d e b %d",p[a-1][b-1],a,b);
            }
        }
        */
        p[a-1][b-1] =1;
        p[b-1][a-1] =1;
        array_number++;
    }
    return p;

}

void free_list(IntNode** list){
    IntNode* p;
    IntNode* pointer;
    IntNode** size = list+v_number_global;
    for(unsigned i =0 ;i<v_number_global;i++){
        pointer = list[i];
        while((pointer)!=NULL){
            p = pointer->next;
            free(pointer);
            pointer = p;
        }
    }
    free(list);

}

void print_list_int(IntNode** list){
    IntNode* index;
    unsigned int i;
    printf("Lista ->[\n");
    for (i =0; i<v_number_global; i++ ){
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

// Lembrar ponteiros s�o passados por valor
//Bota o ponteiro na lista
IntNode* put_inode(IntNode* p ,unsigned int value){
    IntNode* new_pointer;
    if (new_pointer = (IntNode *) malloc(sizeof(IntNode))){
        new_pointer->value = value;
        new_pointer->next = p;
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}

IntNode** read_list_int(unsigned v_number){
    IntNode** p;
    if((p = (IntNode **) calloc(v_number,sizeof(IntNode *)))== NULL){
        printf("Out of Memory");
        exit(1);

    }
    unsigned int a,b;
    while((fscanf(fp,"%u %u",&a,&b)) != EOF){
        //fprintf(out,"Fazendo a %d  e b %d %d \n",a,b,v_number);
        p[a-1] = put_inode(p[a-1],b-1);
        p[b-1] = put_inode(p[b-1],a-1);
        array_number++;
        //printf("Index %d ",a);
        //print_list_int(p[a]);
        //printf("Index %d ",b);
        //print_list_int(p[b]);
        //printf("Atualmente p[a] : %u e p[b]: %u \n", p[a]->value,p[b]->value);
    }
    return p;
}

// D� pop na pilha
static inline IntNode queue_pop(Queue* q){
    IntNode* p_v;
    IntNode vertice;
    p_v = q->top;
    q->top = p_v->next;
    vertice = *(p_v);
    free(p_v);
    return (vertice);
}

static inline void queue_push(Queue* q, unsigned index){
    
    IntNode* last = q->rear;
    IntNode* new_pointer;
    if (new_pointer = (IntNode *) malloc(sizeof(IntNode))){
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

IntNode stack_pop(Stack* stack){
    IntNode* v_p;
    IntNode v;
    v_p = stack->top;
    stack->top = v_p->next;
    v = *(v_p);
    free(v_p);
    return v;
}

void stack_push(Stack* stack, IntNode v){
    IntNode* top = stack->top;
    IntNode* new_pointer;
    if (new_pointer = (IntNode *) malloc(sizeof(IntNode))){
        new_pointer->value = v.value;
        new_pointer->next = top;
        stack->top = new_pointer;
    }
    else
    {
        printf("Fatal error Out of memory");
        exit(1);
    }
}

void print_stack(Stack* stack){
    IntNode v;
    while((stack->top) != NULL){
        v = stack_pop(stack);
        printf("%d \n",v.value);
    }
}

void print_queue(Queue* q){
    IntNode v;
    while((q->top) != NULL){
        v = queue_pop(q);
        printf("%d \n",v.value);
    };
}

//Menor caminho de v1 at� v2 pelo vetor de marca��p
unsigned shortest_path(unsigned v2,unsigned* marking){
    unsigned d=0;
    unsigned first = ~(0x1);
    unsigned none = ~(0x0);
    while (marking[v2] != first){
        if(marking[v2] == none){
            printf("There is no shortest path\n");
            return 0;
        }
        marking[v2] = marking[marking[v2]];
        d++;
    }
    printf("%u\n",d);
    return d;
}

static inline unsigned max_array(unsigned* array){
    unsigned* p ;
    register unsigned max = 0;
    unsigned* size = (array + v_number_global);
    for(p = array; p< size; p++)
        max = (*p>max) ? *p :max;
    return max;
}

static inline unsigned* max_array_pseudo(unsigned* array,unsigned* response){
    register unsigned max = 0;
    unsigned index =0;
    for(unsigned i =0; i< v_number_global; i++)
        if(array[i]>max){
            index = i;
            max = array[i];
        }
    response [0]= max;
    response [1] = index;
}

unsigned pseudo_diameter_list(IntNode** list){
    unsigned* level;
    register unsigned max_graph =0;
    unsigned max =0 ;
    unsigned k = (unsigned) sqrt(v_number_global);
    unsigned first = rand()%v_number_global;
    unsigned response[2];
    for(register unsigned i =0; i< k; i++){
        level = (bfs_list(list,first))[1];
        max_array_pseudo(level,response);
        max = response[0];
        first = response[1];
        max_graph = (max_graph<max) ? max: max_graph;
    }
    printf("pseudo diameter %d\n",max_graph);
    return max_graph;

}

unsigned diameter_list(IntNode** list){
    //unsigned none = ~(0x0);
    unsigned d = 0;
    unsigned* level;
    register unsigned max_graph =0;
    unsigned max =0 ;
    for(register unsigned i =0; i< v_number_global; i++){
        level = (bfs_list(list,i))[1];
        max = max_array(level);
        max_graph = (max_graph<max) ? max: max_graph;
    }
    printf("diameter %d\n",max_graph);
    return max_graph;
}

unsigned diameter_matrix(char** matrix){
    unsigned d = 0;
    unsigned* level;
    unsigned max_graph =0;
    unsigned max =0 ;
    for(unsigned i =0; i< v_number_global; i++){
        level = (bfs_matrix(matrix,i))[1];
        max = max_array(level);
        max_graph = (max_graph<max) ? max: max_graph;
        printf("i %d",i);
    }
    printf("diameter %d\n",max_graph);
    return max_graph;

}

//C�digo modificado retirado da Internet
void bubble_sort(IntNode* start)
{
    int swapped, i;
    unsigned temp;
    IntNode *ptr1;
    IntNode *lptr = NULL;

    if (start == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->value > ptr1->next->value)
            {
                temp = ptr1->value;
                ptr1->value = ptr1->next->value;
                ptr1->next->value = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

unsigned** sorted_bfs_list(IntNode** list, unsigned index){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    IntNode** pointer;
    for(pointer = list; pointer< (list + v_number_global);pointer++){
        bubble_sort(*pointer);
    }
    unsigned* marking;
    unsigned* level;
    register const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    if((marking = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((level = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    Queue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number_global; i++){
        marking[i] = none;
        level[i] = none;
    }
    marking[index] = explored;
    level[index] =0;
    queue_push(&q,index);
    IntNode* linked_list;
    IntNode v,w;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        linked_list=list[v.value];
        //printf("linked_list->value \n");
        while (linked_list!= NULL){
            if((marking[linked_list->value]) == none){
                marking[linked_list->value] = v.value;
                level[linked_list->value] = level[v.value] +1;
                queue_push(&q,linked_list->value);
            }
            //printf("Explorando %d ", linked_list->value);
            linked_list = linked_list->next;
        }


    }
    /*
    printf("Vetor de marca��o [ \n");
    for(unsigned i =0; i< v_number_global;i++){
        printf("index:%u marcado:%u \n", i, marking[i]);
    }
    printf("]\n");
    printf("Vetor de level [ \n");
    for(unsigned i =0; i< v_number_global;i++){
        printf("index:%u marcado:%u \n", i, level[i]);
    }
    printf("]\n");
    */
    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number_global*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }

    return array;

};

static inline unsigned** bfs_list(IntNode** list, unsigned index){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    unsigned* level;
    register const unsigned none = ~(0x0);
    const unsigned explored = ~(0x1);
    if((marking = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((level = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    Queue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number_global; i++){
        marking[i] = none;
        level[i] = none;
    }
    marking[index] = explored;
    level[index] =0;
    queue_push(&q,index);
    IntNode* linked_list;
    IntNode v,w;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        linked_list=list[v.value];
        //printf("linked_list->value \n");
        while (linked_list!= NULL){
            if((marking[linked_list->value]) == none){
                marking[linked_list->value] = v.value;
                level[linked_list->value] = level[v.value] +1;
                queue_push(&q,linked_list->value);
            }
            //printf("Explorando %d ", linked_list->value);
            linked_list = linked_list->next;
        }


    }
    /*
    printf("Vetor de marca��o [ \n");
    for(unsigned i =0; i< v_number_global;i++){
        printf("index:%u marcado:%u \n", i, marking[i]);
    }
    printf("]\n");
    printf("Vetor de level [ \n");
    for(unsigned i =0; i< v_number_global;i++){
        printf("index:%u marcado:%u \n", i, level[i]);
    }
    printf("]\n");
    */
    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number_global*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    array[0]=  marking;
    array[1]=  level;
    return array;

};

unsigned** bfs_matrix(char** matrix, unsigned index){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    unsigned* level;
    unsigned none = ~(0x0);
    unsigned explored = ~(0x1);
    if((marking = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    if((level = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
        printf("Out of memory");
        exit(1);
        //return 1;
    }
    Queue q= {
        NULL,
        NULL
    };
    for (unsigned i =0; i<v_number_global; i++){
        marking[i] = none;
        level[i] = none;
    }
    marking[index] = explored;
    level[index] =0;
    queue_push(&q,index);
    IntNode v,w;
    register unsigned j;
    char* row;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        j= v.value;
        row = matrix[j];
        for(unsigned i =0 ; i< v_number_global; i++){
            if((row[i]) == 1){
                if(marking[i] == none){
                    marking[i] = j;
                    level[i] = level[j] +1;
                    queue_push(&q,i);
                }
            }
        }
    }

    printf("Vetor de marca��o [ \n");
    for(unsigned i =0; i< v_number_global;i++)
        printf("index:%u marcado:%u \n", i, marking[i]);
    printf("]\n");
    printf("Vetor de level [ \n");
    for(unsigned i =0; i< v_number_global;i++)
        printf("index:%u marcado:%u \n", i, level[i]);
    printf("]\n");

    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number_global*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    array[0]=  marking;
    array[1]=  level;
    return array;

}

unsigned* dfs_list(IntNode** list, unsigned index){
    unsigned* marking;
    unsigned none = ~(0x0);
    unsigned explored = ~(0x1);

    if((marking = (unsigned * ) malloc(v_number_global*sizeof(unsigned))) == NULL){
    printf("Out of memory");
    exit(1);
    //return 1;
    }


    Stack s = { NULL
    };

    for (unsigned i =0; i<v_number_global; i++){
        marking[i] = none;
    }

    IntNode a ={
        index,
        NULL,
    };

    stack_push (&s,a);
    IntNode u, v;
    unsigned last_element = explored;
    IntNode* linked_list;

    while(s.top!=NULL){
        u = stack_pop (&s);
        if (marking[u.value] == none)
        {
            marking[u.value] = last_element;
            linked_list=list[u.value];
            last_element = u.value;

            while (linked_list!= NULL)
            {
                stack_push (&s, *linked_list);
                linked_list = linked_list->next;
            }
        }

    }
    return marking;
}
