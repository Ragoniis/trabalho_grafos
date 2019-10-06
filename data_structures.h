#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

typedef struct stack
{
    IntNode* top;
}Stack;


typedef struct int_node
{
    /* data */
    unsigned int value;
    struct int_node* next;

} IntNode;

typedef struct queue
{
    IntNode* rear;
    IntNode* top;
} Queue;

IntNode queue_pop(Queue* q);
void queue_push(Queue* q, unsigned index);
void print_queue(Queue* q);

IntNode stack_pop(Stack* stack);
void stack_push(Stack* stack, IntNode v);
void print_stack(Stack* stack);

#endif
