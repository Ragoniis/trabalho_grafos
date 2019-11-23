#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES


struct int_node
{
    /* data */
    unsigned int value;
    struct int_node* next;

};
typedef struct int_node IntNode;
IntNode* put_inode(IntNode* p ,unsigned int value);

typedef struct w_node{
    unsigned int value;
    struct w_node* next;
    double weight;

} WeightedN;
WeightedN* put_wnode(WeightedN* p ,unsigned int value,double weight);

struct stack
{
    IntNode* top;
};
typedef struct stack Stack;

typedef struct queue
{
    IntNode* rear;
    IntNode* top;
} Queue;

typedef struct heap_node{
    double key;
    unsigned value;
} HeapNode;

typedef struct priority_queue
{   
    HeapNode* heap;
    unsigned* position_array;
    unsigned last_element;
} PriorityQueue;

typedef struct shortest_path_response
{
    double distance;
    Stack path;
} ShortestPathW;

typedef struct bi_graph_matrix
{
    char** graph;
    char* sets;
}BipartiteGraphMatrix;

typedef struct bi_graph_list
{
    IntNode** graph;
    char* sets;
}BipartiteGraphList;

typedef struct matching_edge {
    unsigned v1;
    unsigned v2;
    struct matching_edge *next;
} MatchingEdge;

IntNode queue_pop(Queue* q);
void queue_push(Queue* q, unsigned index);

IntNode stack_pop(Stack* stack);
void stack_push(Stack* stack, IntNode v);

void initialize_PQ(PriorityQueue* pq,unsigned v_number);
HeapNode* extract_min(PriorityQueue* pq);
void decrease_key(PriorityQueue* pq,unsigned vertex, double key);

#endif
