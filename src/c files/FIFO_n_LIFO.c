#include "../FIFO_n_LIFO.h"

void s_push (stack_node_t **stack, int vertex) {
    stack_node_t *node = malloc(sizeof (stack_node_t));
    node->vertex = vertex;
    node->next_node = *stack;
    *stack = node;
}

int s_pop (stack_node_t **stack) {
    stack_node_t *this = *stack;
    if (this == NULL) return -1;
    int vertex = this->vertex;
    *stack = this->next_node;
    free(this);
    return vertex;
}

int s_get (stack_node_t **stack) {
    stack_node_t *this = *stack;
    if (this == NULL) return -1;
    return this->vertex;
}

void s_clear (stack_node_t **stack) {
    stack_node_t *this = *stack;
    if (this == NULL) return;
    stack_node_t *next;
    while (this) {
        next = this->next_node;
        free(this);
        this = next;
    }
    *stack = NULL;
}

void q_add (queue_node_t **queue, int vertex) {
    queue_node_t *node = malloc(sizeof (queue_node_t));
    node->vertex = vertex;
    node->next_node = NULL;
    if (*queue == NULL){
        *queue = node;
        return;
    }
    queue_node_t *this = *queue;
    while (this->next_node) this = this->next_node;
    this->next_node = node;

}
int q_get (queue_node_t **queue) {
    queue_node_t *this = *queue;
    if (this == NULL) return -1;
    int vertex = this->vertex;
    *queue = this->next_node;
    free(this);
    return vertex;
}

int q_show (queue_node_t **queue) {
    queue_node_t *this = *queue;
    if (this == NULL) return -1;
    return this->vertex;
}

void q_clear (queue_node_t **queue) {
    queue_node_t *this = *queue;
    if (this == NULL) return;
    queue_node_t *next;
    while (this) {
        next = this->next_node;
        free(this);
        this = next;
    }
    *queue = NULL;
}