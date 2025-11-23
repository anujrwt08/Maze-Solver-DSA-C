#ifndef SOLVER_H
#define SOLVER_H

#include "maze.h"

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point* path; // sequence from start to goal
    int length;
} Solution;

// Find path using BFS. Returns NULL if no path.
Solution* solver_bfs(Graph* g, int start_idx, int goal_idx);

// Find path using DFS (iterative). Returns NULL if no path.
Solution* solver_dfs(Graph* g, int start_idx, int goal_idx);

void solver_free_solution(Solution* s);

#endif // SOLVER_H
