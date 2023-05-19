cmake_minimum_required(VERSION 3.25)
project(2_5 C)

set(CMAKE_C_STANDARD 11)

add_executable(2_5 main.c "src/c files/graph_create.c" "src/c files/graph_draw.c" "src/c files/vec_math_lib.c" "src/c files/X_routines.c" "src/c files/FIFO_n_LIFO.c" "src/c files/BFS_n_DFS.c" "src/c files/BFS_n_DFS.c")
target_link_libraries(2_5 X11)
target_link_libraries(2_5 m)
