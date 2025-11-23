#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "maze.h"
#include "solver.h"

// Pretty ASCII rendering of maze and optional solution overlay
void graphics_render_maze_with_solution(Maze* maze, Solution* sol, Point start, Point goal);

#endif // GRAPHICS_H
