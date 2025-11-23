#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

// ANSI color codes
#define COLOR_WALL    "\x1b[40;97m"    // Black bg, bright white text
#define COLOR_PATH    "\x1b[44m"       // Blue bg
#define COLOR_SOL     "\x1b[42;97m"    // Green bg, bright white text
#define COLOR_START   "\x1b[46;97m"    // Cyan bg, bright white text
#define COLOR_GOAL    "\x1b[41;97m"    // Red bg, bright white text
#define COLOR_RESET   "\x1b[0m"        // Reset

// Render the maze with ANSI colors and two-character cells for readability.
void graphics_render_maze_with_solution(Maze* maze, Solution* sol, Point start, Point goal) {
    if (!maze) return;
    int w = maze->width;
    int h = maze->height;

    // Overlay map: 0 = empty, 1 = wall, 2 = solution, 3 = start, 4 = goal
    unsigned char* map = (unsigned char*)malloc(w * h);
    if (!map) return;
    for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) map[y * w + x] = maze->grid[y][x] ? 1 : 0;

    if (sol && sol->length > 0) {
        for (int i = 0; i < sol->length; i++) {
            int sx = sol->path[i].x;
            int sy = sol->path[i].y;
            if ((sx == start.x && sy == start.y) || (sx == goal.x && sy == goal.y)) continue;
            map[sy * w + sx] = 2;
        }
    }
    map[start.y * w + start.x] = 3;
    map[goal.y * w + goal.x] = 4;

    // Print top border
    printf("+");
    for (int i = 0; i < w * 2; i++) printf("-");
    printf("+\n");

    // Print rows. Use two characters per cell with colors.
    for (int y = 0; y < h; y++) {
        printf("|");
        for (int x = 0; x < w; x++) {
            unsigned char v = map[y * w + x];
            if (v == 1) {
                // wall - dark/gray with ##
                printf("%s##%s", COLOR_WALL, COLOR_RESET);
            } else if (v == 2) {
                // solution path - green with **
                printf("%s**%s", COLOR_SOL, COLOR_RESET);
            } else if (v == 3) {
                // start - cyan with SS
                printf("%sSS%s", COLOR_START, COLOR_RESET);
            } else if (v == 4) {
                // goal - red with GG
                printf("%sGG%s", COLOR_GOAL, COLOR_RESET);
            } else {
                // empty - blue with dots
                printf("%s..%s", COLOR_PATH, COLOR_RESET);
            }
        }
        printf("|\n");
    }

    // Print bottom border
    printf("+");
    for (int i = 0; i < w * 2; i++) printf("-");
    printf("+\n");

    free(map);
}
