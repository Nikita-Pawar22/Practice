#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int adj[MAX][MAX];    // Adjacency matrix for the graph
int heuristic[MAX];   // Heuristic values for each node
int gCost[MAX];       // gCost: Cost from the start node to the current node
int fCost[MAX];       // fCost: gCost + heuristic
int cameFrom[MAX];    // To reconstruct the path
int openList[MAX];    // Open list
int closedList[MAX];  // Closed list
int numVertices, numEdges;

// Function to find the node with the lowest fCost in the open list
int findMinFCost() {
    int minIndex = -1, minValue = INF;
    for (int i = 0; i < numVertices; i++) {
        if (openList[i] && fCost[i] < minValue) {
            minValue = fCost[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to reconstruct the path from start to goal
void reconstructPath(int start, int goal) {
    printf("Path: ");
    int current = goal;
    while (current != start) {
        printf("%d <- ", current);
        current = cameFrom[current];
    }
    printf("%d\n", start);
}

// A* Algorithm function
void aStar(int start, int goal) {
    // Initialize costs and lists
    for (int i = 0; i < numVertices; i++) {
        gCost[i] = INF;
        fCost[i] = INF;
        openList[i] = 0;
        closedList[i] = 0;
        cameFrom[i] = -1;
    }

    gCost[start] = 0;
    fCost[start] = heuristic[start];
    openList[start] = 1;

    while (1) {
        int current = findMinFCost();

        if (current == -1) {
            printf("No path to the goal node found.\n");
            return;
        }

        if (current == goal) {
            printf("Goal node %d reached with cost %d.\n", goal, gCost[goal]);
            reconstructPath(start, goal);
            return;
        }

        openList[current] = 0;
        closedList[current] = 1;

        printf("Visited node: %d\n", current);

        // Explore neighbors
        for (int i = 0; i < numVertices; i++) {
            if (adj[current][i] > 0 && !closedList[i]) { // Edge exists and not in closed list
                int tentativeGCost = gCost[current] + adj[current][i];

                if (!openList[i]) { // If neighbor is not in the open list
                    openList[i] = 1;
                }

                if (tentativeGCost < gCost[i]) { // Better path found
                    cameFrom[i] = current;
                    gCost[i] = tentativeGCost;
                    fCost[i] = gCost[i] + heuristic[i];
                }
            }
        }
    }
}

int main() {
    int start, goal;
    int src, dest, weight;

    printf("Enter the number of nodes: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    // Initialize adjacency matrix to 0
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            adj[i][j] = 0;
        }
    }

    // Input edges
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &src, &dest, &weight);
        adj[src][dest] = weight;
        adj[dest][src] = weight; // For undirected graph
    }

    // Input heuristic values
    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < numVertices; i++) {
        scanf("%d", &heuristic[i]);
    }

    // Input start and goal nodes
    printf("Enter the start node: ");
    scanf("%d", &start);
    printf("Enter the goal node: ");
    scanf("%d", &goal);

    // Run A* algorithm
    aStar(start, goal);

    return 0;
}
