#include "solver.h"
#include <stdlib.h>
#include <string.h>

// Helper to convert index path to Solution (Points)
static Solution* build_solution_from_parents(int* parents, int start, int goal, int width) {
    if (parents == NULL) return NULL;
    if (parents[goal] == -1 && start != goal) return NULL;
    
    // Reconstruct path backwards
    int cur = goal;
    int cap = 64;
    int len = 0;
    int* nodes = (int*)malloc(cap * sizeof(int));
    while (cur != -1) {
        if (len >= cap) { cap *= 2; nodes = (int*)realloc(nodes, cap * sizeof(int)); }
        nodes[len++] = cur;
        if (cur == start) break;
        cur = parents[cur];
    }
    if (len == 0) { free(nodes); return NULL; }
    
    Solution* sol = (Solution*)malloc(sizeof(Solution));
    sol->length = len;
    sol->path = (Point*)malloc(len * sizeof(Point));
    for (int i = 0; i < len; i++) {
        int idx = nodes[len - 1 - i];
        int x, y;
        index_to_coord(idx, width, &x, &y);
        sol->path[i].x = x;
        sol->path[i].y = y;
    }
    free(nodes);
    return sol;
}

Solution* solver_bfs(Graph* g, int start_idx, int goal_idx) {
    if (!g) return NULL;
    if (start_idx < 0 || start_idx >= g->num_nodes) return NULL;
    if (goal_idx < 0 || goal_idx >= g->num_nodes) return NULL;
    
    int n = g->num_nodes;
    int* visited = (int*)calloc(n, sizeof(int));
    int* parents = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) parents[i] = -1;
    
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    
    // Start only if start cell has adjacency or is the same as goal
    visited[start_idx] = 1;
    queue[rear++] = start_idx;
    
    while (front < rear) {
        int cur = queue[front++];
        if (cur == goal_idx) break;
        int cnt = g->adj_counts[cur];
        int* neighbours = g->adj[cur];
        for (int i = 0; i < cnt; i++) {
            int v = neighbours[i];
            if (!visited[v]) {
                visited[v] = 1;
                parents[v] = cur;
                queue[rear++] = v;
            }
        }
    }
    
    Solution* sol = build_solution_from_parents(parents, start_idx, goal_idx, g->width);
    free(visited);
    free(parents);
    free(queue);
    return sol;
}

Solution* solver_dfs(Graph* g, int start_idx, int goal_idx) {
    if (!g) return NULL;
    int n = g->num_nodes;
    int* visited = (int*)calloc(n, sizeof(int));
    int* parents = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) parents[i] = -1;
    
    // iterative stack
    int* stack = (int*)malloc(n * sizeof(int));
    int top = 0;
    stack[top++] = start_idx;
    visited[start_idx] = 1;
    
    while (top > 0) {
        int cur = stack[--top];
        if (cur == goal_idx) break;
        int cnt = g->adj_counts[cur];
        int* neighbours = g->adj[cur];
        for (int i = 0; i < cnt; i++) {
            int v = neighbours[i];
            if (!visited[v]) {
                visited[v] = 1;
                parents[v] = cur;
                stack[top++] = v;
            }
        }
    }
    
    Solution* sol = build_solution_from_parents(parents, start_idx, goal_idx, g->width);
    free(visited);
    free(parents);
    free(stack);
    return sol;
}

void solver_free_solution(Solution* s) {
    if (!s) return;
    free(s->path);
    free(s);
}
