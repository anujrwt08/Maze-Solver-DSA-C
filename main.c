#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"
#include "solver.h"
#include "graphics.h"

// Build a sample maze (simple handcrafted map). 0 = empty, 1 = wall
static void build_sample_maze(Maze* m) {
    // Clear
    for (int y = 0; y < m->height; y++) for (int x = 0; x < m->width; x++) maze_set_path(m, x, y);
    // Borders
    for (int x = 0; x < m->width; x++) { maze_set_wall(m, x, 0); maze_set_wall(m, x, m->height-1); }
    for (int y = 0; y < m->height; y++) { maze_set_wall(m, 0, y); maze_set_wall(m, m->width-1, y); }
    
    // Internal walls to create a larger, more complex maze
    int walls[][2] = {
        {3,1},{4,1},{5,1},{6,1},
        {3,2},{8,2},{10,2},{11,2},
        {3,3},{8,3},{10,3},
        {3,4},{8,4},{10,4},{15,4},
        {3,5},{6,5},{8,5},{10,5},{15,5},
        {6,6},{8,6},{15,6},{18,6},
        {6,7},{9,7},{15,7},{18,7},
        {6,8},{9,8},{12,8},{18,8},{20,8},
        {6,9},{9,9},{12,9},{18,9},{20,9},
        {6,10},{12,10},{18,10},{20,10},
        {6,11},{12,11},{18,11},
        {3,12},{6,12},{9,12},{12,12},{15,12},
    };
    int nwalls = sizeof(walls)/sizeof(walls[0]);
    for (int i = 0; i < nwalls; i++) maze_set_wall(m, walls[i][0], walls[i][1]);
}

int main(void) {
    printf("Simple Maze Solver (graph + BFS/DFS)\n");
    printf("Choose an algorithm to find a path from S to G.\n\n");
    
    int width = 25, height = 15;
    Maze* maze = maze_create(width, height);
    if (!maze) { fprintf(stderr, "Failed to allocate maze\n"); return 1; }
    build_sample_maze(maze);
    
    Point start = {1,1};
    Point goal = {23,13};
    
    Graph* g = graph_create_from_maze(maze);
    if (!g) { fprintf(stderr, "Failed to build graph\n"); maze_destroy(maze); return 1; }
    
    printf("Start: (%d,%d)  Goal: (%d,%d)\n", start.x, start.y, goal.x, goal.y);
    printf("Available algorithms:\n  1) BFS (shortest path)\n  2) DFS (may find non-shortest path)\n");
    printf("Enter choice (1 or 2): ");
    char line[16];
    if (!fgets(line, sizeof(line), stdin)) strcpy(line, "1");
    int choice = atoi(line);
    Solution* sol = NULL;
    int start_idx = coord_to_index(start.x, start.y, g->width);
    int goal_idx = coord_to_index(goal.x, goal.y, g->width);
    
    if (choice == 2) {
        printf("Running DFS...\n");
        sol = solver_dfs(g, start_idx, goal_idx);
    } else {
        printf("Running BFS...\n");
        sol = solver_bfs(g, start_idx, goal_idx);
    }
    
    if (sol) {
        printf("Path found! length=%d\n\n", sol->length);
        graphics_render_maze_with_solution(maze, sol, start, goal);
        solver_free_solution(sol);
    } else {
        printf("No path found between S and G.\n\n");
        graphics_render_maze_with_solution(maze, NULL, start, goal);
    }
    
    graph_free(g);
    maze_destroy(maze);
    return 0;
}
