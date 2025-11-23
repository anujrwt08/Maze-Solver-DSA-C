#ifndef MAZE_H
#define MAZE_H

#include <stddef.h>

typedef struct {
    int width;
    int height;
    int** grid; // 0 = path, 1 = wall
} Maze;

// Graph representation derived from the grid
typedef struct {
    int width;
    int height;
    int num_nodes;       // width * height
    int** adj;           // adjacency lists: adj[node] -> dynamic array of neighbours
    int* adj_counts;     // number of neighbours per node
} Graph;

// Convert grid coordinates to node index and vice-versa
static inline int coord_to_index(int x, int y, int width) { return y * width + x; }
static inline void index_to_coord(int idx, int width, int* x, int* y) { *x = idx % width; *y = idx / width; }

// Maze creation and destruction
Maze* maze_create(int width, int height);
void maze_destroy(Maze* maze);

// Maze manipulation
void maze_set_wall(Maze* maze, int x, int y);
void maze_set_path(Maze* maze, int x, int y);
int maze_get_cell(Maze* maze, int x, int y);

// Build/free graph from a Maze
Graph* graph_create_from_maze(Maze* maze);
void graph_free(Graph* g);

#endif // MAZE_H
