#ifndef INC_2_3_CONSTS_N_STRUCTURES_H
#define INC_2_3_CONSTS_N_STRUCTURES_H

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define POINT_RADIUS 20
#define bpen 0x3200FF
#define wpen 0xFFFFFF

//virtual screen space has double values from -1 to 1
typedef struct {
    double x;
    double y;
} serv_point_t;
//actual screen space has int values from 0 to screen width (height)

typedef struct screen_space_point_t {
    int x;
    int y;
    char number[3];
} point_t;

typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} vec_4_t;

typedef struct { //it`s relative to start_x, start_y
    int x;
    int y;
} vec_2_t;

typedef struct {
    int x_offset;
    int y_offset;
} r_offset_t;

typedef struct {
    double theta;
    int px;
    int py;
    int color;
    struct arrows_list_t *next_arr;
} a_list_t;

extern int n;

#endif //INC_2_3_CONSTS_N_STRUCTURES_H
