# Maze Solver - Graph-Based Pathfinding using BFS/DFS

A C implementation of a maze solver that uses **Graph data structures** and classic **graph traversal algorithms** (BFS and DFS) to find the shortest path from start to goal.

---

## 📋 Project Overview

This project demonstrates fundamental **Data Structures and Algorithms (DSA)** concepts:
- **Graph Representation**: Converting a 2D grid maze into an adjacency list graph
- **Breadth-First Search (BFS)**: Finding the shortest path
- **Depth-First Search (DFS)**: Alternative pathfinding approach
- **Path Reconstruction**: Tracing back the solution from parent pointers

---

## 🎯 Key Features

✅ **Graph-based maze representation** with adjacency lists  
✅ **Two pathfinding algorithms**: BFS (shortest) and DFS (alternative)  
✅ **User-selectable algorithm** at runtime  
✅ **Colorful ASCII visualization** of the maze and solution path  
✅ **Efficient memory management** with proper malloc/free  
✅ **Fully documented and modular code**

---

## 📚 Data Structures & Algorithms Explained

### 1. **Maze Structure**
```c
typedef struct {
    int width;
    int height;
    int** grid;  // 0 = path, 1 = wall
} Maze;
```
- 2D grid where each cell is either a passable path (0) or wall (1)

### 2. **Graph Structure**
```c
typedef struct {
    int width, height;
    int num_nodes;       // width * height
    int** adj;           // adjacency lists
    int* adj_counts;     // neighbors per node
} Graph;
```
- **Adjacency list representation**: Each passable cell is a node
- Nodes are indexed 0 to (width×height - 1)
- `adj[i]` contains indices of adjacent passable cells (up, down, left, right)

### 3. **Solution Structure**
```c
typedef struct {
    Point* path;  // Sequence of (x, y) coordinates from start to goal
    int length;   // Number of steps in the path
} Solution;
```

---

## 🔍 Algorithm Details

### **Breadth-First Search (BFS)**
- **Purpose**: Find the *shortest* path
- **Time Complexity**: O(V + E) where V = nodes, E = edges
- **Space Complexity**: O(V) for the queue
- **How it works**:
  1. Start at source node, mark as visited
  2. Explore all neighbors level-by-level using a queue
  3. Track parent of each node for path reconstruction
  4. When goal is reached, backtrack using parents
  5. Return the path from start to goal

**Pros**: Guaranteed shortest path  
**Cons**: Uses more memory for queue

### **Depth-First Search (DFS)**
- **Purpose**: Find *a* path (may not be shortest)
- **Time Complexity**: O(V + E)
- **Space Complexity**: O(V) for the stack
- **How it works**:
  1. Start at source node, mark as visited
  2. Explore deeply along one branch using a stack
  3. Backtrack when hitting dead ends
  4. Track parent for path reconstruction
  5. Return path when goal is found

**Pros**: Sometimes faster for certain maze layouts  
**Cons**: Path may be longer than optimal

---

## 🏗️ Project Structure

```
harshit/
├── maze.h          # Maze and Graph type definitions
├── maze.c          # Maze creation, manipulation, graph building
├── solver.h        # BFS/DFS solver declarations
├── solver.c        # BFS/DFS implementations
├── graphics.h      # Rendering functions
├── graphics.c      # ASCII maze visualization with colors
├── main.c          # Main program with user interaction
├── Makefile        # Build configuration
└── README.md       # This file
```

---

## 🚀 How to Run

### **Prerequisites**
- **GCC compiler** (or any C99-compatible compiler)
- **Windows PowerShell** (or any terminal supporting ANSI colors)

### **Build the Project**

#### Option 1: Using `make` (if you have it installed)
```powershell
make clean
make
make run
```

#### Option 2: Direct GCC compilation
```powershell
gcc main.c maze.c solver.c graphics.c -std=c99 -O2 -Wall -o maze.exe
```

### **Run the Program**

```powershell
.\maze.exe
```

**Expected Output:**
```
Simple Maze Solver (graph + BFS/DFS)
Choose an algorithm to find a path from S to G.

Start: (1,1)  Goal: (23,13)
Available algorithms:
  1) BFS (shortest path)
  2) DFS (may find non-shortest path)
Enter choice (1 or 2): 
```

### **Choose an Algorithm**

Type `1` for BFS (shortest path):
```powershell
echo 1 | .\maze.exe
```

Or type `2` for DFS (alternative path):
```powershell
echo 2 | .\maze.exe
```

---

## 🎨 Output Explanation

The maze is displayed with colors and symbols:

| Symbol | Color | Meaning |
|--------|-------|---------|
| `##` | Dark/Gray | Wall (impassable) |
| `..` | Blue | Empty path (not used in solution) |
| `**` | Green | Solution path (found route) |
| `SS` | Cyan | Start position |
| `GG` | Red | Goal position |

### Example Output:
```
+--------------------------------------------------+
|##################################################|
|##SS..########..................................##|
|##**..##........##..####........................##|
|##**..##........##..##..........................##|
|##**..##........##..##........##................##|
|##**..##....##..##..##........##................##|
|##**........##..##............##....##..........##|
|##**........##....##..........##....##..........##|
|##**........##....##....##..........##..##......##|
|##**........##....##....##..........##..##......##|
|##**........##..........##..........##..##......##|
|##**........##..........##..........##..........##|
|##**..##....##....##....##....##................##|
|##********************************************GG##|
|##################################################|
+--------------------------------------------------+

Path found! length=35
```

---

## 📖 Code Walkthrough

### **1. Creating a Maze**
```c
Maze* maze = maze_create(25, 15);  // 25 wide, 15 tall
maze_set_wall(maze, 3, 2);         // Add wall at (3, 2)
```

### **2. Building a Graph**
```c
Graph* g = graph_create_from_maze(maze);
// Converts grid to adjacency list representation
```

### **3. Solving with BFS**
```c
int start_idx = coord_to_index(1, 1, g->width);   // (1,1) → node index
int goal_idx = coord_to_index(23, 13, g->width);  // (23,13) → node index
Solution* sol = solver_bfs(g, start_idx, goal_idx);
```

### **4. Rendering the Solution**
```c
Point start = {1, 1};
Point goal = {23, 13};
graphics_render_maze_with_solution(maze, sol, start, goal);
```

### **5. Cleanup**
```c
solver_free_solution(sol);
graph_free(g);
maze_destroy(maze);
```

---

## 🔧 Customization

### **Change Maze Size**
Edit `main.c` line 24-25:
```c
int width = 25, height = 15;   // Change to your desired dimensions
```

### **Modify Maze Layout**
Edit the `walls` array in `build_sample_maze()` function in `main.c`:
```c
int walls[][2] = {
    {3,1}, {4,1}, {5,1},   // Wall at (3,1), (4,1), (5,1)
    // Add more walls...
};
```

### **Change Start/Goal**
Edit `main.c` line 30-31:
```c
Point start = {1, 1};      // New start position
Point goal = {23, 13};     // New goal position
```

---

## 💡 Learning Outcomes

After exploring this project, you'll understand:

1. **Graph Representation**: How to convert 2D grids into graph structures
2. **BFS Algorithm**: How BFS guarantees the shortest path
3. **DFS Algorithm**: How DFS explores depth-first and may find longer paths
4. **Path Reconstruction**: Using parent pointers to rebuild the solution
5. **Memory Management**: Proper allocation and deallocation in C
6. **Modular Code**: Separating concerns (maze, solver, graphics)

---

## 🧪 Testing

### Test BFS (shortest path):
```powershell
echo 1 | .\maze.exe
```
Expected: Finds optimal shortest path with `**` markers

### Test DFS (alternative path):
```powershell
echo 2 | .\maze.exe
```
Expected: May find a longer path; same start and goal

### Modify and Recompile:
```powershell
# Change maze size in main.c, then:
gcc main.c maze.c solver.c graphics.c -std=c99 -O2 -Wall -o maze.exe
.\maze.exe
```

---

## 📊 Complexity Analysis

| Operation | Time | Space |
|-----------|------|-------|
| Create Maze | O(W×H) | O(W×H) |
| Build Graph | O(W×H) | O(W×H + E) |
| BFS Search | O(V + E) | O(V) |
| DFS Search | O(V + E) | O(V) |
| Render | O(W×H) | O(W×H) |

Where: W = width, H = height, V = nodes, E = edges

---

## 🎓 Advanced Extensions

Want to enhance this project? Try:

1. **Random Maze Generator**: Use DFS to carve passages
2. **A Algorithm**: Add heuristic-based pathfinding
3. **Multiple Goals**: Find shortest path to any goal
4. **Performance Comparison**: Measure BFS vs DFS times
5. **Interactive Maze**: Allow users to set walls dynamically
6. **3D Maze**: Extend to 3D grid pathfinding

---

## 📝 License

This is an educational project. Feel free to use and modify!

---
## 👨‍💻 Author **Anuj Rawat**
## 👨‍💻 Author Notes

This project demonstrates:
- Clean C code structure
- Proper memory management
- Graph algorithm implementations
- User-friendly output formatting
- Educational DSA concepts

Perfect for learning graph theory and algorithm design! 🚀

---

**Happy Pathfinding! 🎯**


