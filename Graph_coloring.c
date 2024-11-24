#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Function to check if it's safe to assign color to vertex 'v'
bool isSafe(int graph[MAX_VERTICES][MAX_VERTICES], int color[], int v, int c, int n) {
    for (int i = 0; i < n; i++) {
        // If adjacent vertex has the same color, return false
        if (graph[v][i] == 1 && color[i] == c) {
            return false;
        }
    }
    return true;
}

// Utility function to solve the graph coloring problem using backtracking
bool graphColoringUtil(int graph[MAX_VERTICES][MAX_VERTICES], int color[], int v, int m, int n) {
    // If all vertices are assigned a color, return true
    if (v == n) {
        return true;
    }

    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        // Check if assigning color c to vertex v is safe
        if (isSafe(graph, color, v, c, n)) {
            color[v] = c;

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, color, v + 1, m, n)) {
                return true;
            }

            // If assigning color c doesn't lead to a solution, backtrack
            color[v] = 0;
        }
    }

    // If no color can be assigned to vertex v, return false
    return false;
}

// Function to solve the graph coloring problem
bool graphColoring(int graph[MAX_VERTICES][MAX_VERTICES], int m, int n) {
    // Array to store the color assignments of vertices
    int color[MAX_VERTICES] = {0};

    // Call the utility function to solve the problem
    if (graphColoringUtil(graph, color, 0, m, n) == false) {
        printf("Solution does not exist\n");
        return false;
    }

    // Print the solution
    printf("Solution exists: Following are the assigned colors:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    return true;
}

int main() {
    int n, m;

    // Input number of vertices and number of colors
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of colors: ");
    scanf("%d", &m);

    // Create an adjacency matrix for the graph
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Solve the graph coloring problem
    if (!graphColoring(graph, m, n)) {
        printf("No valid coloring is possible with %d colors.\n", m);
    }

    return 0;
}
