#include "maze.h"
#include <stdlib.h>
#include <string.h>

// Initialize maze with given dimensions
Maze* maze_create(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    if (!maze) return NULL;
    
    maze->width = width;
    maze->height = height;
    maze->grid = (int**)malloc(height * sizeof(int*));
    if (!maze->grid) { free(maze); return NULL; }
    
    for (int y = 0; y < height; y++) {
        maze->grid[y] = (int*)malloc(width * sizeof(int));
        if (!maze->grid[y]) {
            for (int j = 0; j < y; j++) free(maze->grid[j]);
            free(maze->grid);
            free(maze);
            return NULL;
        }
        memset(maze->grid[y], 0, width * sizeof(int));
    }
    
    return maze;
}

// Free maze memory
void maze_destroy(Maze* maze) {
    if (!maze) return;
    
    for (int i = 0; i < maze->height; i++) {
        free(maze->grid[i]);
    }
    free(maze->grid);
    free(maze);
}

// Set wall at position
void maze_set_wall(Maze* maze, int x, int y) {
    if (!maze) return;
    if (x >= 0 && x < maze->width && y >= 0 && y < maze->height) {
        maze->grid[y][x] = 1;
    }
}

// Set path at position
void maze_set_path(Maze* maze, int x, int y) {
    if (!maze) return;
    if (x >= 0 && x < maze->width && y >= 0 && y < maze->height) {
        maze->grid[y][x] = 0;
    }
}

// Get cell value
int maze_get_cell(Maze* maze, int x, int y) {
    if (!maze) return -1;
    if (x >= 0 && x < maze->width && y >= 0 && y < maze->height) {
        return maze->grid[y][x];
    }
    return -1;
}

// Build adjacency lists from maze grid. Walls are not nodes.
Graph* graph_create_from_maze(Maze* maze) {
    if (!maze) return NULL;
    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (!g) return NULL;
    
    g->width = maze->width;
    g->height = maze->height;
    g->num_nodes = g->width * g->height;
    g->adj = (int**)malloc(g->num_nodes * sizeof(int*));
    g->adj_counts = (int*)malloc(g->num_nodes * sizeof(int));
    if (!g->adj || !g->adj_counts) {
        free(g->adj); free(g->adj_counts); free(g);
        return NULL;
    }
    
    // First compute neighbour counts for each node (only for passable cells)
    for (int i = 0; i < g->num_nodes; i++) {
        g->adj[i] = NULL;
        g->adj_counts[i] = 0;
    }
    
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            int idx = coord_to_index(x, y, g->width);
            if (maze->grid[y][x] == 1) continue; // wall: leave adj empty
            int count = 0;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height) {
                    if (maze->grid[ny][nx] == 0) count++;
                }
            }
            if (count > 0) {
                g->adj[idx] = (int*)malloc(count * sizeof(int));
                g->adj_counts[idx] = count;
            }
        }
    }
    
    // Fill adjacency lists
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            int idx = coord_to_index(x, y, g->width);
            if (maze->grid[y][x] == 1) continue;
            int pos = 0;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height) {
                    if (maze->grid[ny][nx] == 0) {
                        g->adj[idx][pos++] = coord_to_index(nx, ny, g->width);
                    }
                }
            }
        }
    }
    
    return g;
}

void graph_free(Graph* g) {
    if (!g) return;
    for (int i = 0; i < g->num_nodes; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g->adj_counts);
    free(g);
}
