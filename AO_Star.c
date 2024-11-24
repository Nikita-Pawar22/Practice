#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Node {
    int isSolved;
    int cost;
    int heuristic;
    int numChildren;
    int children[100];
    int isAndNode; // 1 for AND node, 0 for OR node
} Node;

Node* graph;
int N;

void initializeGraph() {
    // Initialize all nodes to unsolved and set high cost
    for (int i = 0; i < N; i++) {
        graph[i].isSolved = 0;
        graph[i].cost = INF;
        graph[i].numChildren = 0;
    }

    printf("Enter the heuristic values for each node:\n");
    for (int i = 0; i < N; i++) {
        printf("Heuristic value for node %d: ", i);
        scanf("%d", &graph[i].heuristic);
    }

    printf("Enter the number of children and each child node for each parent node:\n");
    for (int i = 0; i < N; i++) {
        printf("Number of children for node %d: ", i);
        scanf("%d", &graph[i].numChildren);
        for (int j = 0; j < graph[i].numChildren; j++) {
            printf("Child %d of node %d: ", j + 1, i);
            scanf("%d", &graph[i].children[j]);
        }
        printf("Is node %d an AND node (1 for YES, 0 for NO)? ", i);
        scanf("%d", &graph[i].isAndNode);  // Input for AND/OR node
    }
}

// AO* algorithm: Returns the minimum cost to solve the problem from the current node
int AOStar(int node) {
    if (graph[node].isSolved) {
        return graph[node].cost;
    }

    // Base case: If a node has no children, it's a leaf node (cost = 0)
    if (graph[node].numChildren == 0) {
        graph[node].isSolved = 1;
        graph[node].cost = 0;
        return 0;  // Leaf node, no further cost to explore
    }

    int totalCost = 0;

    // Handle AND nodes (sum of all children's costs)
    if (graph[node].isAndNode) {
        totalCost = 0;  // For AND nodes, cost is sum of all child costs
        for (int i = 0; i < graph[node].numChildren; i++) {
            int child = graph[node].children[i];
            int childCost = AOStar(child);  // Recursively solve for the child
            if (childCost == INF) {
                totalCost = INF;  // If any child has no solution, the parent can't be solved
                break;
            }
            totalCost += childCost;  // Sum costs for AND nodes
        }
    } 
    // Handle OR nodes (minimum cost among all child nodes)
    else {
        totalCost = INF;  // For OR nodes, we are looking for the minimum cost
        for (int i = 0; i < graph[node].numChildren; i++) {
            int child = graph[node].children[i];
            int childCost = AOStar(child);  // Recursively solve for the child
            if (childCost < totalCost) {
                totalCost = childCost;  // Minimize cost for OR nodes
            }
        }
    }

    // Add the heuristic value of the current node
    graph[node].cost = totalCost + graph[node].heuristic;

    // Mark the current node as solved
    graph[node].isSolved = 1;

    return graph[node].cost;
}

int main() {
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &N);

    graph = (Node*)malloc(N * sizeof(Node));
    initializeGraph();

    printf("Solving AO* Algorithm...\n");
    int solutionCost = AOStar(0);  // Start from the root node (node 0)

    if (solutionCost != INF) {
        printf("The minimum cost from the root to solve the problem is: %d\n", solutionCost);
    } else {
        printf("No solution found.\n");
    }

    free(graph);
    return 0;
}
