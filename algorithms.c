#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algorithms.h"

unsigned** bfs_list(IntNode** list, unsigned index, unsigned v_number){
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
    IntNode* linked_list;
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
    return array;

}

unsigned** bfs_matrix(char** matrix, unsigned index,unsigned v_number){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    unsigned* marking;
    unsigned* level;
    unsigned none = ~(0x0);
    unsigned explored = ~(0x1);
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
    register unsigned j;
    char* row;
    while ( (q.top) != NULL)
    {
        v = queue_pop(&q);
        j= v.value;
        row = matrix[j];
        for(unsigned i =0 ; i< v_number; i++){
            if((row[i]) == 1){
                if(marking[i] == none){
                    marking[i] = j;
                    level[i] = level[j] +1;
                    queue_push(&q,i);
                }
            }
        }
    }

    printf("Vetor de marcação [ \n");
    for(unsigned i =0; i< v_number;i++)
        printf("index:%u marcado:%u \n", i, marking[i]);
    printf("]\n");
    printf("Vetor de level [ \n");
    for(unsigned i =0; i< v_number;i++)
        printf("index:%u marcado:%u \n", i, level[i]);
    printf("]\n");

    unsigned** array;
    if((array = (unsigned ** ) malloc(v_number*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }
    array[0]=  marking;
    array[1]=  level;
    return array;

}

unsigned* dfs_list(IntNode** list, unsigned index, unsigned v_number){
    unsigned* marking;
    unsigned none = ~(0x0);
    unsigned explored = ~(0x1);

    if((marking = (unsigned * ) malloc(v_number*sizeof(unsigned))) == NULL){
    printf("Out of memory");
    exit(1);
    //return 1;
    }


    Stack s = { NULL
    };

    for (unsigned i =0; i<v_number; i++){
        marking[i] = none;
    }

    IntNode a ={
        index,
        NULL,
    };

    stack_push (&s,a);
    IntNode u;
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

//Codigo modificado retirado da Internet
void bubble_sort(IntNode* start)
{
    int swapped;
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

unsigned** sorted_bfs_list(IntNode** list, unsigned index,unsigned v_number){
    //Define NULL como 2^32
    //E marcado como (2^32 -1)
    //tendo em vista que nenhum grafo tem perto de 4 bilh�es de vertices, isso n�o � um problema
    IntNode** pointer;
    for(pointer = list; pointer< (list + v_number);pointer++){
        bubble_sort(*pointer);
    }
    unsigned* marking;
    unsigned* level;
    register const unsigned none = ~(0x0);
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
    IntNode* linked_list;
    IntNode v;
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
    if((array = (unsigned ** ) malloc(v_number*sizeof(unsigned)*2)) == NULL){
        printf("Out of memory");
        exit(1);
    }

    return array;

}

unsigned diameter_matrix(char** matrix, unsigned v_number){
    //unsigned d = 0;
    unsigned* level;
    unsigned max_graph =0;
    unsigned max =0 ;
    for(unsigned i =0; i< v_number; i++){
        level = (bfs_matrix(matrix,i,v_number))[1];
        max = max_array(level,v_number);
        max_graph = (max_graph<max) ? max: max_graph;
        printf("i %d",i);
    }
    printf("diameter %d\n",max_graph);
    return max_graph;

}

unsigned diameter_list(IntNode** list, unsigned v_number){
    //unsigned none = ~(0x0);
    //unsigned d = 0;
    unsigned* level;
    register unsigned max_graph =0;
    unsigned max =0 ;
    for(register unsigned i =0; i< v_number; i++){
        level = (bfs_list(list,i,v_number))[1];
        max = max_array(level,v_number);
        max_graph = (max_graph<max) ? max: max_graph;
    }
    printf("diameter %d\n",max_graph);
    return max_graph;
}

unsigned* max_array_pseudo(unsigned* array,unsigned* response, unsigned v_number){
    register unsigned max = 0;
    unsigned index =0;
    for(unsigned i =0; i< v_number; i++)
        if(array[i]>max){
            index = i;
            max = array[i];
        }
    response [0]= max;
    response [1] = index;
    return response;
}

unsigned pseudo_diameter_list(IntNode** list, unsigned v_number){
    unsigned* level;
    register unsigned max_graph =0;
    unsigned max =0 ;
    unsigned k = (unsigned) sqrt(v_number);
    unsigned first = rand()%v_number;
    unsigned response[2];
    for(register unsigned i =0; i< k; i++){
        level = (bfs_list(list,first,v_number))[1];
        max_array_pseudo(level,response,v_number);
        max = response[0];
        first = response[1];
        max_graph = (max_graph<max) ? max: max_graph;
    }
    printf("pseudo diameter %d\n",max_graph);
    return max_graph;

}

//Menor caminho de v1 até v2 pelo vetor de marcação da BFS
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


