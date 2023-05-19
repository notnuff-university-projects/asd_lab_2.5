#ifndef INC_2_5_BFS_N_DFS_H
#define INC_2_5_BFS_N_DFS_H
#include "FIFO_n_LIFO.h"
#include "consts_n_structures.h"
#include "graph_create.h"
#include "X_routines.h"
#include "graph_draw.h"
void BSF(int **rel_mat, int **bones, int *BSF_visited, int size, int *k, queue_node_t **queue, point_t *graph);

void BFS_clear(queue_node_t **queue, int **bones, int *visited_vertices, point_t *visited_graph, int *k, int *last_i);
void BFS_next_active(queue_node_t **queue, int **bones, point_t *visited_graph, int *last_i, int *active,
                     int *visited_vertices);
void BFS_next_visit (int **rel_mat, int **bones, queue_node_t **queue, point_t *visited_graph, int *visited_v,
                     int *last_i, int *k, int active);
void DFS_clear(stack_node_t **stack, int **bones, int *visited_vertices, point_t *visited_graph, int *k, int *last_i);
void DFS_next_active(stack_node_t **stack, int **bones, point_t *visited_graph, int *last_i, int *active,
                     int *visited_vertices);
void DFS_done(int **bones, int *visited_vertices);
void DFS_next_visit (int **rel_mat, int **bones, stack_node_t **stack, point_t *visited_graph, int *visited_v,
                     int *last_i, int *k, int active);

#endif //INC_2_5_BFS_N_DFS_H
