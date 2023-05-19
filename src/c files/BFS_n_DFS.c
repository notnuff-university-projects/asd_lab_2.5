#include "../BFS_n_DFS.h"

void DFS_clear(stack_node_t **stack, int **bones, int *visited_vertices, point_t *visited_graph, int *k, int *last_i) {
    s_clear(stack);
    for (int i = 0; i < n; i++) {
        visited_vertices[i] = 0;
        sprintf(visited_graph[i].number, "N%d", i + 1);
        for (int j = 0; j < n; j++)
            bones[i][j] = 0;
    }
    int v = 6;//n * (double) rand() / RAND_MAX;
    *k = 1;
    s_push(stack, v);
    visited_vertices[v] = *k;
    *last_i = -1;
}

void DFS_next_active(stack_node_t **stack, int **bones, point_t *visited_graph, int *last_i, int *active,
                     int *visited_vertices) {
    if (visited_graph[*active].number[0] == 'A')
        sprintf(visited_graph[*active].number, "V%d", *active + 1);

    if (s_get(stack) == -1) {
        for (int i = 0; i < n; i++) {
            if (visited_vertices[i] == 0) {
                visited_vertices[i] = 1;
                s_push(stack, i);
                break;
            }
        }
    }
    *active = s_get(stack);

    if (*active == -1) {
        DFS_done(bones, visited_vertices);
        return;
    }
    sprintf(visited_graph[*active].number, "A");
    *last_i = 0;
}

void DFS_next_visit (int **rel_mat, int **bones, stack_node_t **stack, point_t *visited_graph, int *visited_v,
                     int *last_i, int *k, int active) {
    for (int i = *last_i; i < n; i++, *last_i = *last_i + 1) {
        if (rel_mat[active][i]) {
            if (visited_v[i] == 0) {
                *k = *k + 1;
                visited_v[i] = *k;
                s_push(stack, i);
                sprintf(visited_graph[i].number, "V%d", i + 1);
                bones[active][i] = 1;
                *last_i = -1;
                return;
            }
        }
    }
}

void DFS_done(int **bones, int *visited_vertices) {
    XSetForeground(dis, gc, 0xFFFFFF);
    XDrawString(dis, win, gc, 20, 20, "Done!", 5);
    printf("Матриця обходу:\n");
    print_mat(bones, n, n);
    //toask is correct to print vertices like this
    for (int i = 0; i < n; i++) {
        printf("%i -> %i\n", i + 1, visited_vertices[i]);
    }
}

void BFS_clear(queue_node_t **queue, int **bones, int *visited_vertices, point_t *visited_graph, int *k, int *last_i) {
    q_clear(queue);
    for (int i = 0; i < n; i++) {
        visited_vertices[i] = 0;
        sprintf(visited_graph[i].number, "N%d", i + 1);
        for (int j = 0; j < n; j++)
            bones[i][j] = 0;
    }
    int v = n * (double) rand() / RAND_MAX;
    *k = 1;
    q_add(queue, v);
    visited_vertices[v] = *k;
    *last_i = -1;
}
void BFS_next_active(queue_node_t **queue, int **bones, point_t *visited_graph, int *last_i, int *active,
                     int *visited_vertices) {
    if (q_show(queue) == -1) {
        for (int i = 0; i < n; i++) {
            if (visited_vertices[i] == 0) {
                visited_vertices[i] = 1;
                q_add(queue, i);
                break;
            }
        }
    }

    *active = q_get(queue);
    if (*active == -1) {
        DFS_done(bones, visited_vertices);
        return;
    }
    sprintf(visited_graph[*active].number, "A");
    *last_i = 0;
}

void BFS_next_visit (int **rel_mat, int **bones, queue_node_t **queue, point_t *visited_graph, int *visited_v,
                     int *last_i, int *k, int active) {
    for (int i = *last_i; i < n; i++, *last_i = *last_i + 1) {
        if (rel_mat[active][i]) {
            if (visited_v[i] == 0) {
                *k = *k + 1;
                visited_v[i] = *k;
                q_add(queue, i);
                sprintf(visited_graph[i].number, "V%d", i + 1);
                bones[active][i] = 1;
                break;
            }
        }
    }
}