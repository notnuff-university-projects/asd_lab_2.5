#ifndef INC_2_5_FIFO_N_LIFO_H
#define INC_2_5_FIFO_N_LIFO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct stack_node_t{
    int vertex;
    struct stack_node_t *next_node;
} stack_node_t;

typedef struct queue_node_t{
    int vertex;
    struct queue_node_t *next_node;
} queue_node_t;

void s_push (stack_node_t **stack, int vertex);
int s_pop (stack_node_t **stack);
void s_clear (stack_node_t **stack);
int s_get (stack_node_t **stack);


void q_add (queue_node_t **queue, int vertex);
void q_clear (queue_node_t **queue);
int q_get (queue_node_t **queue);
int q_show (queue_node_t **queue);

#endif //INC_2_5_FIFO_N_LIFO_H