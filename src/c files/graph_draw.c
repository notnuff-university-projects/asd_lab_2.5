#include "../graph_draw.h"
#include <stdio.h>

a_list_t *arrows_list = NULL;

void arrow_add(a_list_t **tar_p, double theta, int px, int py, int red) {
    a_list_t *node_p;
    node_p = malloc(sizeof (a_list_t));
    node_p->theta = theta;
    node_p->px = px;
    node_p->py = py;
    node_p->color = red;
    if (*tar_p) {
        node_p->next_arr = *tar_p;
    }
    else {
        node_p->next_arr = NULL;
    }
    *tar_p = node_p;
}

void arrows_clear (a_list_t **tar_p) {
    a_list_t *tar = *tar_p;
    if (!tar) return;
    a_list_t *next_p;
    while (tar) {
        next_p = tar->next_arr;
        free (tar);
        tar = next_p;
    }
    *tar_p = NULL;
}

void arrows_draw (a_list_t *tar) {
    a_list_t *next_p;
    while (tar) {
        next_p = tar->next_arr;
        arrow(tar->theta, tar->px, tar->py, tar->color);
        tar = next_p;
    }
}

void arrow(double theta, int px, int py, int red) {
    theta = 3.1415 * (180.0 - theta) / 180.0;
    int lx, ly, rx, ry;
    lx = px + (int) (20 + red * 5) * cos(theta + 0.3);
    rx = px + (int) (20 + red * 5) * cos(theta - 0.3);
    ly = py + (int) (20 + red * 5) * sin(theta + 0.3);
    ry = py + (int) (20 + red * 5) * sin(theta - 0.3);

    XSetForeground(dis, gc, red ? 0x0000FF : 0x212A3E);
    XSetLineAttributes(dis, gc,
                       red? 6 : 4,
                       LineSolid,
                       CapButt, JoinMiter);
    XDrawLine(dis, win, gc, lx, ly, px, py);
    XDrawLine(dis, win, gc, px, py, rx, ry);

    XSetForeground(dis, gc, red ? 0x000000 : 0xFC4F00);
    XSetLineAttributes(dis, gc,
                       2,
                       LineSolid,
                       CapButt, JoinMiter);
    XDrawLine(dis, win, gc, lx, ly, px, py);
    XDrawLine(dis, win, gc, px, py, rx, ry);
}

void draw_graph_vertices(point_t *graph, int size) {
    for (int i = 0; i < size; i++) {
        XSetForeground(dis, gc, 0xFFFFFF);
        XFillArc(dis, win, gc,
                 graph[i].x - POINT_RADIUS, graph[i].y - POINT_RADIUS,
                 2 * POINT_RADIUS, 2 * POINT_RADIUS,
                 0, 360 * 64);
    }

    XSetLineAttributes(dis, gc,
                       2,
                       LineSolid,
                       CapButt, JoinMiter);
    for (int i = 0; i < size; i++) {
        int line_size =  i / 9 + 2;
        switch (graph[i].number[0]) {
            case 'N':
                XSetForeground(dis, gc, 0x0000FF);
                break;
            case 'V':
                XSetForeground(dis, gc, 0x005500);
                break;
            case 'A':
                XSetForeground(dis, gc, 0xFF0000);
                line_size = 1;
                break;
            default:
                XSetForeground(dis, gc, 0x000000);
                line_size--;
                break;
        }

        XSetLineAttributes(dis, gc,
                           2,
                           LineSolid,
                           CapButt, JoinMiter);
        XDrawString(dis, win, gc, graph[i].x - 2, graph[i].y + 4,
                        graph[i].number, line_size);

        XDrawArc(dis, win, gc, graph[i].x - POINT_RADIUS, graph[i].y - POINT_RADIUS,
                 2 * POINT_RADIUS, 2 * POINT_RADIUS, 0, 360 * 64);

    }
}

void draw_arc(vec_4_t *vector, int offset_radius, int red) {
    vec_2_t *vec = malloc(sizeof (vec_2_t));
    vec_2_t *vec_OX = malloc(sizeof (vec_2_t));
    *vec_OX = (vec_2_t) {1, 0};

    vec->x = vector->end_x - vector->start_x;
    vec->y = vector->end_y - vector->start_y;

    int quarter = vec_quarter(vec);

    int midpoint_x = vec->x / 2;
    int midpoint_y = vec->y / 2;
    double cosB = vectors_cos(vec, vec_OX);
    double sinA = cosB;
    double cosA;
    if (quarter == 1 || quarter == 2) cosA = -sqrt(1-cosB * cosB);
    else cosA = sqrt(1-cosB * cosB);

    int offset_y = sinA * offset_radius;
    int offset_x = cosA * offset_radius;
    int center_x = vector->start_x + midpoint_x - offset_x;
    int center_y = vector->start_y + midpoint_y + offset_y;
    int rad2 = sqrt((center_x - vector->start_x) * (center_x - vector->start_x) +
                    (center_y - vector->start_y) * (center_y - vector->start_y));

    vec_2_t * center_to_end = malloc(sizeof (vec_2_t));
    center_to_end->x = vector->end_x - center_x;
    center_to_end->y = vector->end_y - center_y;

    vec_2_t * center_to_start = malloc(sizeof (vec_2_t));
    center_to_start->x = vector->start_x - center_x;
    center_to_start->y = vector->start_y - center_y;

    cosA = vectors_cos(center_to_start, vec_OX);
    int S = 64 * acos(cosA) * 180 / 3.1415;
    if (vec_quarter(center_to_start) == 4 || vec_quarter(center_to_start) == 3)
        S = 360 * 64 - S;
    cosB = vectors_cos(center_to_end, vec_OX);
    int E = 64 * acos(cosB) * 180 / 3.1415;

    if (vec_quarter(center_to_end) == 4 || vec_quarter(center_to_end) == 3)
        E = 360 * 64 - E;

    if (vec_quarter(center_to_end) == 4 && vec_quarter(center_to_start) == 1)
        S = 360 * 64 + S;

    /*XSetLineAttributes(dis, gc,
                       1,
                       LineSolid,
                       CapButt, JoinMiter);*/

    XDrawArc(dis, win, gc, center_x - rad2, center_y - rad2,
             2*rad2, 2*rad2, E, abs(S - E));

    int theta = -90 + round(acos(vectors_cos(center_to_end, vec_OX)) * 180 / 3.1415);
    if (vec_quarter(center_to_end) == 3 || vec_quarter(center_to_end) == 4)
        theta = 180 - theta;
    arrow_add(&arrows_list, theta, vector->end_x, vector->end_y, red);
    free(vec); free(vec_OX); free(center_to_end); free(center_to_start);
}

void draw_line(vec_4_t *vector, int red) {
    /*XSetLineAttributes(dis, gc,
                       1,
                       LineSolid,
                       CapButt, JoinMiter);*/
    XDrawLine(dis, win, gc, vector->start_x, vector->start_y, vector->end_x, vector->end_y);

    vec_2_t *vec = malloc(sizeof (vec_2_t));
    vec_2_t *vec_OX = malloc(sizeof (vec_2_t));
    *vec_OX = (vec_2_t) {1, 0};
    vec->x = vector->end_x - vector->start_x;
    vec->y = vector->end_y - vector->start_y;
    double cos = vectors_cos(vec, vec_OX);
    int theta = acos(cos) * 180 / 3.1415;
    if (vec_quarter(vec) == 3 || vec_quarter(vec) == 4)
        theta = 360 - theta;
    arrow_add(&arrows_list, theta, vector->end_x, vector->end_y, red);

    free (vec); free (vec_OX);
}

void draw_graph(point_t *graph, int **relation_matrix, int size, int oriented, int red) {

    int point_1 = 0;
    int point_2 = size / 3;
    int point_3 = 2 * size / 3;

    int color = 0xFFFFFF;
    int thickness = 1;

    if (red) {
        color = 0xFF0000;
        thickness = 5;
    }

    for (int i = 0; i < size; i++) {
        for (int j = oriented ? 0 : i; j < size; j++) {
            XSetForeground(dis, gc, color);
            XSetLineAttributes(dis, gc, thickness, LineSolid, CapButt, JoinMiter);

            vec_4_t *this_vec = malloc(sizeof (vec_4_t));
            *this_vec = (vec_4_t) {graph[i].x, graph[i].y,
                                   graph[j].x, graph[j].y};

            r_offset_t *offset = rad_offsetting(this_vec);

            this_vec->start_x += offset->x_offset;
            this_vec->start_y += offset->y_offset;
            this_vec->end_x -= offset->x_offset;
            this_vec->end_y -= offset->y_offset;

            if (relation_matrix[i][j]) {
                int condition = (
                        point_1 <= i && i <= point_2 && point_1 <= j && j <= point_2 ||
                        point_2 <= i && i <= point_3 && point_2 <= j && j <= point_3 ||
                        point_3 <= i && i < size && point_3 <= j && j < size ||
                        point_3 <= i && i < size &&  j == point_1 ||
                        point_3 <= j && j < size &&  i == point_1 );

                if (condition) { //на одній лінії знаходяться
                    int a = abs(i - j) % (size - 1) + abs(i - j) / (size - 1);
                    switch (a) {
                        case 0:
                            if (relation_matrix[i][i]) {
                                XDrawArc(dis, win, gc, this_vec->start_x + 0.3*POINT_RADIUS, this_vec->start_y,
                                         2 * POINT_RADIUS, 2 * POINT_RADIUS, 240*64, 240*64);
                                if (oriented)
                                    arrow_add(&arrows_list,
                                              -190, this_vec->start_x + 0.7 * POINT_RADIUS,
                                              this_vec->start_y + 1.9 * POINT_RADIUS, red);
                            }
                            break;
                        case 1:
                            if (relation_matrix[i][j]) {
                                if (relation_matrix[j][i] && oriented)
                                    draw_arc(this_vec, 500, red);
                                else
                                    draw_line(this_vec, red);
                            }
                            break;
                        default:
                            if (relation_matrix[i][j])
                                draw_arc(this_vec, 500, red);
                    }
                }
                else { //на різних лініях
                    if (relation_matrix[i][j]) {
                        if (oriented) {
                            if (relation_matrix[j][i])
                                draw_arc(this_vec, 500, red);
                            else
                                draw_line(this_vec, red);
                        }
                        else if (relation_matrix[i][j])
                            draw_line(this_vec, red);
                    }
                }
            }
            free (this_vec); free(offset);
        }
    }
    if (oriented) arrows_draw(arrows_list);
    arrows_clear(&arrows_list);
}