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
    struct int_node* next;
    unsigned weight;

} WeightedN;

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
    unsigned key;
    unsigned value;
} HeapNode;

typedef struct priority_queue
{   
    HeapNode* heap;
    unsigned* position_array;
    unsigned last_element;
} PriorityQueue;

IntNode queue_pop(Queue* q);
void queue_push(Queue* q, unsigned index);

IntNode stack_pop(Stack* stack);
void stack_push(Stack* stack, IntNode v);

void initialize_PQ(PriorityQueue* pq,unsigned v_number);
HeapNode extract_min(PriorityQueue* pq);
void decrease_key(PriorityQueue* pq,unsigned vertex, unsigned key);

#endif
