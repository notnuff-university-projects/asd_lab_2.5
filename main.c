// other libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/consts_n_structures.h"
#include "src/graph_create.h"
#include "src/vec_math_lib.h"
#include "src/X_routines.h"
#include "src/graph_draw.h"
#include "src/FIFO_n_LIFO.h"
#include "src/BFS_n_DFS.h"

int n;

int main() {
    int n1 = 2, n2 = 1, n3 = 2, n4 = 5;
    srand(n1 * 1000 + n2 * 100 + n3 * 10 + n4);

    n = 10 + n3;
    double c = 1.0 - n3 * 0.01 - n4 * 0.005 - 0.15;
    double **service_mat;
    service_mat = randm(n, n);
    int **rel_mat;
    rel_mat = mat_create(n, n);
    point_t *graph;

    printf("\n");
    rel_mat = mulmr(c, service_mat, rel_mat, n, n, 1);
    printf("1. Printing relation matrix:\n");
    print_mat(rel_mat, n, n);
    graph = tri_graph_create(graph, n);

    point_t *visited_graph = tri_graph_create(visited_graph, n);
    stack_node_t *stack = NULL;
    queue_node_t *queue = NULL;
    int **bones = mat_create(n, n);
    int *visited_v = malloc(sizeof(int) * n);
    int k;
    int active = -1;
    int last_i = -1;
    init_x();//window created

    int b = 0;
    int d = 0;

    while (1) {
        XNextEvent(dis, &event);
        switch (event.type) {
            case Expose:
                if (event.xexpose.count == 0) redraw_x();
                break;
            case KeyPress:
                if (XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
                    switch (text[0]) {
                        case 'q':
                            free_mat(service_mat, n);
                            free_mat(rel_mat, n);
                            free_mat(bones, n);
                            q_clear(&queue);
                            s_clear(&stack);
                            free(visited_v);
                            free(graph);
                            free(visited_graph);
                            close_x();
                            return 0;
                            break;
                        case 'b':
                            if (b == 0) {
                                redraw_x();
                                BFS_clear(&queue, bones, visited_v, visited_graph, &k, &last_i);
                                draw_graph(graph, rel_mat, n, 1, 0);
                                draw_graph_vertices(visited_graph, n);
                                b = 1;
                                d = 0;
                                break;
                            }

                            if (last_i == -1) {
                                BFS_next_active(&queue, bones, visited_graph, &last_i, &active, visited_v);
                                draw_graph_vertices(visited_graph, n);
                                break;
                            }

                            BFS_next_visit(rel_mat, bones, &queue, visited_graph, visited_v, &last_i, &k, active);

                            if (last_i >= n) {
                                sprintf(visited_graph[active].number, "%d", active + 1);
                                last_i = -1;
                            }

                            draw_graph(visited_graph, bones, n, 1, 1);
                            draw_graph_vertices(visited_graph, n);

                            break;
                        case 'd':

                            if (d == 0) {
                                redraw_x();
                                DFS_clear(&stack, bones, visited_v, visited_graph, &k, &last_i);
                                draw_graph(visited_graph, rel_mat, n, 1, 0);
                                draw_graph_vertices(visited_graph, n);
                                d = 1;
                                b = 0;
                                break;
                            }

                            if (last_i == -1) {
                                DFS_next_active(&stack, bones, visited_graph, &last_i, &active,visited_v);
                                draw_graph_vertices(visited_graph, n);
                                break;
                            }

                            DFS_next_visit(rel_mat, bones, &stack, visited_graph, visited_v, &last_i, &k, active);

                            if (last_i >= n - 1) {
                                int this = s_pop(&stack);
                                if (this != -1) sprintf(visited_graph[this].number, "%d", this + 1);
                                last_i = -1;
                            }

                            draw_graph(visited_graph, bones, n, 1, 1);
                            draw_graph_vertices(visited_graph, n);
                            break;

                        default:
                            b = 0;
                            d = 0;
                            redraw_x();
                            draw_graph(graph, rel_mat, n, 1, 0);
                            draw_graph_vertices(graph, n);
                            break;
                    }
                    break;
                }
        }
    }
}